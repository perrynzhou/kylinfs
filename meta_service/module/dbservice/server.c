/*************************************************************************
    > File Name: server.C
  > Author:perrynzhou
  > Mail:perrynzhou@gmail.com
  > Created Time: Wednesday, September 09, 2020 AM08:34:22
 ************************************************************************/

#include "server.h"
#include "../drpc/drpc.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <ev.h>

static int set_non_blocking(int sockfd)
{
  if (fcntl(sockfd, F_SETFD, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK) ==
      -1)
  {
    return -1;
  }
  return 0;
}

inline static void remove_socket(const char *name)
{
  if (access(name, F_OK) == 0)
  {
    remove(name);
  }
}
server_t *server_alloc(int server_type, int id, drpc_handler_func handler, void *ctx)
{
  server_t *srv = (server_t *)calloc(1, sizeof(server_t));
  assert(srv != NULL);
  char buffer[256] = {'\0'};
  snprintf((char *)&buffer, 256, "/tmp/%s_%d.sock", server_type_names[server_type], id);
  srv->socket = strdup((char *)&buffer);
  remove_socket(srv->socket);
  struct drpc *listener = drpc_listen(srv->socket, handler);
  srv->sfd = listener->fd;
  log_info("active fd=%d,socket=%s", srv->sfd, srv->socket);
  srv->server_type = server_type;
  srv->listener = listener;
  srv->db_ctx = (kv_db_t *)ctx;
  return srv;
}

inline static int server_add_event(int epollfd, struct drpc *session_ctx, int state)
{
  struct epoll_event ev;
  ev.events = state;
  ev.data.ptr = session_ctx;
  return epoll_ctl(epollfd, EPOLL_CTL_ADD, session_ctx->fd, &ev);
}

inline static void server_modify_event(int epollfd, struct drpc *session_ctx, int state)
{
  struct epoll_event ev;
  ev.events = state;
  ev.data.ptr = session_ctx;
  epoll_ctl(epollfd, EPOLL_CTL_MOD, session_ctx->fd, &ev);
}

inline static void server_delete_event(int epollfd, struct drpc *session_ctx, int state)
{
  struct epoll_event ev;
  ev.events = state;
 ev.data.ptr = session_ctx;
  epoll_ctl(epollfd, EPOLL_CTL_DEL, session_ctx->fd, &ev);
}

static void server_handle_accept(int epollfd, struct drpc *listener)
{
  struct epoll_event event;
  struct drpc *session_ctx = drpc_accept(listener);
  if (session_ctx == NULL || session_ctx->fd == -1)
  {
    log_info("session_ctx=%p is nil,error=%s", session_ctx, strerror(errno));
    return;
  }
  event.data.ptr = session_ctx;
  event.events = EPOLLIN | EPOLLET;
  if (server_add_event(epollfd, session_ctx, EPOLLIN) == -1)
  {
    server_delete_event(epollfd, session_ctx, EPOLLIN);
    log_info("fd=%d closed", session_ctx->fd);
  }
}

static void server_handle_events(int epollfd, struct epoll_event *events, int num, struct drpc *listener, void *ctx)
{
  server_t *srv = (server_t *)ctx;
  for (int i = 0; i < num; ++i)
  {    struct drpc *session_ctx = (struct drpc *)events[i].data.ptr;
    if ((events[i].events & EPOLLERR) ||
        (events[i].events & EPOLLHUP) ||
        (!(events[i].events & EPOLLIN)))
    {
      drpc_close(session_ctx);
      server_delete_event(epollfd, session_ctx, EPOLLIN);
      continue;
    }
    
    if ((session_ctx->fd == listener->fd) && (events[i].events & EPOLLIN))
    {
      server_handle_accept(epollfd, listener);
    }
    else 
    {
      struct drpc *session_ctx = (struct drpc *)events[i].data.ptr;
      Drpc__Request *incoming;
      int result = drpc_recv_call(session_ctx, &incoming);
      Drpc__Response *resp = drpc_response_create(incoming);
      log_info("::::engine accept client fd=%d,socket=%s", session_ctx->fd,srv->socket);
      session_ctx->handler(incoming, resp, (kv_db_t *)srv->db_ctx);
      drpc_send_response(session_ctx, resp);
      drpc_response_free(resp);
      drpc_close(session_ctx);
    }
    /*
    else
    {
      // do_write(epollfd, fd, buf);
    }
    */
  }
}

void server_start(server_t *srv)
{
  int max_event = 655350;
  int listenfd = srv->listener->fd;
   set_non_blocking(listenfd);

  struct epoll_event *events = (struct epoll_event *)calloc(max_event,sizeof(struct epoll_event));
  int nfds;
  int efd = epoll_create(max_event);
  server_add_event(efd, srv->listener, EPOLLIN | EPOLLOUT | EPOLLET);
  while (1)
  {
    // 获取已经准备好的描述符事件
    nfds = epoll_wait(efd, events, max_event, -1);
    if (nfds <0) {
      log_error("::epoll_wait error=%s",strerror(errno));
      break;
    }
    server_handle_events(efd, events, nfds, srv->listener, srv);
  }
  close(efd);
  drpc_close(srv->listener);
  free(events);
}

void server_free(server_t *srv)
{
  if (srv != NULL)
  {
    if (srv->sfd != -1)
    {
      close(srv->sfd);
    }
    if (srv->socket != NULL)
    {
      free(srv->socket);
    }
    free(srv);
    srv = NULL;
  }
}
