/*
 * (C) Copyright 2018-2021 Intel Corporation.
 *
 * SPDX-License-Identifier: BSD-2-Clause-Patent
 */

#include "drpc.h"
#include "drpc.pb-c.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <linux/un.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void *
daos_drpc_alloc(void *arg, size_t size)
{
	struct drpc_alloc *alloc = (struct drpc_alloc *)arg;
	void *buf;

	D_ALLOC(buf, size);
	if (!buf)
		alloc->oom = true;
	return buf;
}

void daos_drpc_free(void *allocater_data, void *pointer)
{
	D_FREE(pointer);
}

/**
 * Allocate and initialize a new dRPC call Protobuf structure for a given dRPC
 * context.
 *
 * \param	ctx	Active dRPC context
 * \param	module	Module ID for the new call
 * \param	method	Method ID for the new call
 * \param	callp	Newly allocated Drpc__Request
 *
 * \returns	On success returns 0 otherwise returns negative error condition.
 */
int drpc_call_create(struct drpc *ctx, int32_t module, int32_t method,
					 Drpc__Request **callp)
{
	Drpc__Request *call;

	if (callp)
		*callp = NULL;

	if (ctx == NULL || callp == NULL)
	{
		return -1;
	}

	D_ALLOC_PTR(call);
	if (call == NULL)
		return -1;

	drpc__request__init(call);
	call->module = module;
	call->method = method;

	*callp = call;

	return 0;
}

/**
 * Free a dRPC Call Protobuf structure.
 *
 * \param	call	dRPC call to be freed
 */
void drpc_call_free(Drpc__Request *call)
{
	struct drpc_alloc alloc = PROTO_ALLOCATOR_INIT(alloc);

	drpc__request__free_unpacked(call, &alloc.alloc);
}

/**
 * Allocate and initialize a new dRPC Response to a given dRPC call.
 *
 * \param	call	dRPC call to be responded to
 *
 * \return	Newly allocated Drpc__Response, or NULL if it couldn't be
 *			allocated.
 */
Drpc__Response *
drpc_response_create(Drpc__Request *call)
{
	Drpc__Response *resp;

	D_ALLOC_PTR(resp);
	if (resp == NULL)
		return NULL;

	drpc__response__init(resp);
	if (call == NULL)
		resp->sequence = -1;
	else
		resp->sequence = call->sequence;

	return resp;
}

/**
 * Free a dRPC Response Protobuf structure.
 *
 * \param	resp	dRPC response to be freed
 */
void drpc_response_free(Drpc__Response *resp)
{
	struct drpc_alloc alloc = PROTO_ALLOCATOR_INIT(alloc);

	drpc__response__free_unpacked(resp, &alloc.alloc);
}

static int
unixcomm_close(int fd)
{
	int ret = close(fd);
	if (ret < 0)
	{
		return -1;
	}
	return 0;
}

static int
new_unixcomm_socket(int *fd_ptr, int flags)
{
	int fd = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	if (fd < 0)
	{
		int rc = errno;
		return rc;
	}
	if (fcntl(fd, F_SETFL, flags) < 0)
	{
		int rc = errno;
		unixcomm_close(fd);
		return rc;
	}
	*fd_ptr = fd;
	return 0;
}

static void
fill_socket_address(const char *sockpath, struct sockaddr_un *address)
{
	memset(address, 0, sizeof(struct sockaddr_un));

	address->sun_family = AF_UNIX;
	strncpy(address->sun_path, sockpath, UNIX_PATH_MAX - 1);
}

static int
unixcomm_connect(char *sockaddr, int flags, int *fd_ptr)
{
	struct sockaddr_un address;
	int fd = new_unixcomm_socket(fd_ptr, flags);
	if (fd != 0)
		return fd;

	fill_socket_address(sockaddr, &address);
	errno = 0;
	if (connect(fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		int rc = errno;
		unixcomm_close(fd);
		return rc;
	}
	return 0;
}

static int
unixcomm_listen(char *sockaddr, int flags, int *fd_ptr)
{
	struct sockaddr_un address;
	int ret;

	ret = new_unixcomm_socket(fd_ptr, flags);
	if (ret != 0)
		return ret;

	fill_socket_address(sockaddr, &address);
	if (bind(*fd_ptr, (struct sockaddr *)&address, sizeof(struct sockaddr_un)) < 0)
	{
		char *msg = strerror(errno);
		fprintf(stdout, "msg=%s\n", msg);
		int rc = errno;
		unixcomm_close(*fd_ptr);
		return rc;
	}

	if (listen(*fd_ptr, SOMAXCONN) < 0)
	{
		int rc = errno;
		unixcomm_close(*fd_ptr);
		return rc;
	}
	return 0;
}

static int
unixcomm_accept(int fd)
{

	return accept(fd, NULL, NULL);
}

static int
unixcomm_send(int fd, uint8_t *buffer, size_t buflen,
			  ssize_t *sent)
{
	int ret;
	struct iovec iov[1];
	struct msghdr msg;
	ssize_t bsent;

	memset(&msg, 0, sizeof(msg));

	iov[0].iov_base = buffer;
	iov[0].iov_len = buflen;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;

	bsent = sendmsg(fd, &msg, 0);
	if (bsent < 0)
	{
		ret = -1;
	}
	else
	{
		if (sent != NULL)
			*sent = bsent;
		ret = 0;
	}
	return ret;
}

static int
unixcomm_recv(int fd, uint8_t *buffer, size_t buflen,
			  ssize_t *rcvd)
{
	int ret;
	struct iovec iov[1];
	struct msghdr msg;
	ssize_t brcvd;

	memset(&msg, 0, sizeof(msg));

	iov[0].iov_base = buffer;
	iov[0].iov_len = buflen;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;

	brcvd = recvmsg(fd, &msg, 0);
	if (brcvd < 0)
	{
		ret = errno;
	}
	else
	{
		if (rcvd != NULL)
			*rcvd = brcvd;
		ret = 0;
	}
	return ret;
}

static int
drpc_marshal_call(Drpc__Request *msg, uint8_t **bytes)
{
	int buf_len;
	uint8_t *buf;

	if (!msg)
	{
		return -1;
	}

	buf_len = drpc__request__get_packed_size(msg);

	D_ALLOC(buf, buf_len);
	if (!buf)
		return -1;

	drpc__request__pack(msg, buf);

	*bytes = buf;
	return buf_len;
}

/**
 * Issue a call over a drpc channel
 *
 * \param ctx	Context representing the connection.
 * \param flags	Flags to specify specific call behavior (SYNC/ASYNC).
 * \param msg	The drpc call structure representing the function call.
 * \param resp	The drpc response structure for the call.
 *
 * \returns	On success returns 0 otherwise returns negative error condition.
 */
int drpc_call(struct drpc *ctx, int flags, Drpc__Request *msg,
			  Drpc__Response **resp)
{
	struct drpc_alloc alloc = PROTO_ALLOCATOR_INIT(alloc);
	Drpc__Response *response = NULL;
	uint8_t *messagePb;
	uint8_t *responseBuf;
	int pbLen;
	ssize_t sent;
	ssize_t recv = 0;
	int ret;

	pbLen = drpc_marshal_call(msg, &messagePb);
	if (pbLen < 0)
		return pbLen;

	ret = unixcomm_send(ctx->fd, messagePb, pbLen, &sent);
	D_FREE(messagePb);

	if (ret < 0)
		return ret;

	if (!(flags & R_SYNC))
	{
		response = drpc_response_create(msg);
		response->status = DRPC__STATUS__SUBMITTED;
		*resp = response;
		return 0;
	}

	D_ALLOC(responseBuf, UNIXCOMM_MAXMSGSIZE);
	if (!responseBuf)
		return -1;

	ret = unixcomm_recv(ctx->fd, responseBuf, UNIXCOMM_MAXMSGSIZE, &recv);
	if (ret < 0)
	{
		D_FREE(responseBuf);
		return ret;
	}
	response = drpc__response__unpack(&alloc.alloc, recv, responseBuf);
	D_FREE(responseBuf);
	if (alloc.oom)
		return -1;
	if (!response)
		return -1;

	*resp = response;
	return 0;
}

static void
init_drpc_ctx(struct drpc *ctx, int fd, drpc_handler_func handler)
{
	ctx->fd = fd;
	ctx->handler = handler;
}

/**
 * Connect to a drpc socket server on the given path.
 *
 * \param[in]  sockaddr	Path to unix domain socket in the filesystem.
 * \param[out]    drpcp Drpc context representing the connection.
 *
 * \returns	On success returns 0 otherwise returns negative error condition.
 */
int drpc_connect(char *sockaddr, struct drpc **drpcp)
{
	struct drpc *ctx;
	int ret;

	*drpcp = NULL;

	D_ALLOC_PTR(ctx);
	if (!ctx)
		return -1;

	int fd = -1;
	ret = unixcomm_connect(sockaddr, 0, &fd);
	if (ret != 0)
	{
		D_FREE(ctx);
		return ret;
	}

	init_drpc_ctx(ctx, fd, NULL);
	*drpcp = ctx;

	return 0;
}

/**
 * Set up a drpc socket server to passively listen for connections on a given
 * path.
 *
 * \param	sockaddr	Path to unix domain socket in the filesystem
 * \param	handler		Handler for messages received on sessions for
 *					this socket.
 *
 * \return	drpc context representing the listener, or NULL if failed to
 *			create one
 */
struct drpc *
drpc_listen(char *sockaddr, drpc_handler_func handler)
{
	struct drpc *ctx;
	struct unixcomm *comm;
	int rc;

	if (sockaddr == NULL || handler == NULL)
	{
		return NULL;
	}

	D_ALLOC_PTR(ctx);
	if (ctx == NULL)
		return NULL;

	int fd = -1;
	rc = unixcomm_listen(sockaddr, O_NONBLOCK, &fd);
	if (rc != 0)
	{
		D_FREE(ctx);
		return NULL;
	}

	init_drpc_ctx(ctx, fd, handler);

	return ctx;
}

/**
 * Determines if the drpc ctx is set up as a listener.
 *
 * \param	ctx	Active drpc context
 *
 * \return	True if a valid listener, false otherwise
 */
bool drpc_is_valid_listener(struct drpc *ctx)
{
	/*
	 * Listener needs a handler or else it's pretty useless
	 */
	return (ctx != NULL) && (ctx->fd != -1) && (ctx->handler != NULL);
}

/**
 * Wait for a client to connect to a listening drpc context, and return the
 * context for the client's session.
 *
 * \param	ctx	drpc context created by drpc_listen()
 *
 * \return	new drpc context for the accepted client session, or
 *			NULL if failed to get one
 */
struct drpc *
drpc_accept(struct drpc *listener_ctx)
{
	struct drpc *session_ctx;

	if (!drpc_is_valid_listener(listener_ctx))
	{
		fprintf(stdout, ".....drpc_is_valid_listener.....\n");
		return NULL;
	}

	D_ALLOC_PTR(session_ctx);
	if (session_ctx == NULL)
	{
		fprintf(stdout, ".....D_ALLOC_PTR.....\n");
		return NULL;
	}
	int fd = unixcomm_accept(listener_ctx->fd);
	if (fd <= 0)
	{
		fprintf(stdout, ".....unixcomm_accept.....:%s\n", strerror(errno));
		return NULL;
	}
	init_drpc_ctx(session_ctx, fd, listener_ctx->handler);
	return session_ctx;
}
struct drpc *drpc_alloc(int fd)
{
	struct drpc *session_ctx;
	D_ALLOC_PTR(session_ctx);
	if (session_ctx == NULL)
	{
		return NULL;
	}
	session_ctx->fd = fd;
	session_ctx->handler = NULL;
	return session_ctx;
}

static int
send_response(struct drpc *ctx, Drpc__Response *response)
{
	int rc;
	size_t buffer_len;
	uint8_t *buffer;
	assert(response != NULL);
	buffer_len = drpc__response__get_packed_size(response);

	D_ALLOC(buffer, buffer_len);
	if (buffer == NULL)
		return -1;

	drpc__response__pack(response, buffer);
	rc = unixcomm_send(ctx->fd, buffer, buffer_len, NULL);

	D_FREE(buffer);
	return rc;
}

static int
get_incoming_call(struct drpc *ctx, Drpc__Request **call)
{
	struct drpc_alloc alloc = PROTO_ALLOCATOR_INIT(alloc);
	int rc;
	uint8_t *buffer;
	size_t buffer_size = UNIXCOMM_MAXMSGSIZE;
	ssize_t message_len = 0;

	D_ALLOC(buffer, buffer_size);
	if (buffer == NULL)
		return -1;

	rc = unixcomm_recv(ctx->fd, buffer, buffer_size,
					   &message_len);
	if (rc != 0)
	{
		D_FREE(buffer);
		return rc;
	}

	*call = drpc__request__unpack(&alloc.alloc, message_len, buffer);
	D_FREE(buffer);
	if (alloc.oom || *call == NULL)
	{
		return -1;
	}
	return 0;
}

/**
 * Listen for a client message on a dRPC session and return the Drpc__Request
 * received.
 *
 * \param[in]	session_ctx	Valid dRPC session context
 * \param[out]	call		Newly allocated Drpc__Request
 *
 * \return	0		Successfully got a message
 *		-DER_INVAL	Invalid input
 *		-DER_NOMEM	Out of memory
 *		-DER_AGAIN	Listener socket is nonblocking and there was no
 *				pending message on the pipe
 *		-DER_PROTO	Badly-formed incoming message
 */
int drpc_recv_call(struct drpc *session_ctx, Drpc__Request **call)
{
	if (call == NULL)
	{
		return -1;
	}

	if (!drpc_is_valid_listener(session_ctx))
	{
		return -1;
	}

	return get_incoming_call(session_ctx, call);
}

/**
 * Send a given Drpc__Response to the client on a dRPC session.
 *
 * \param[in]	ctx	Valid dRPC session context
 * \param[in]	resp	Response to be sent
 *
 * \return	0		Successfully sent message
 *		-DER_INVAL	Invalid input
 *		-DER_NOMEM	Out of memory
 *		-DER_NO_PERM	Bad socket permissions
 *		-DER_NO_HDL	Invalid socket fd in ctx
 *		-DER_AGAIN	Operation blocked, try again
 *		-DER_MISC	Miscellaneous error sending response
 */
int drpc_send_response(struct drpc *session_ctx, Drpc__Response *resp)
{
	if (resp == NULL)
	{
		return -1;
	}

	if (!drpc_is_valid_listener(session_ctx))
	{
		return -1;
	}
	int ret = send_response(session_ctx, resp);
	D_FREE(resp->body.data);
	return ret;
}

/**
 * Close the existing drpc connection.
 *
 * If there are multiple references to the context, the ref count will be
 * decremented. Otherwise the context will be freed.
 *
 * \param ctx	The drpc context representing the connection (will be freed if
 *		last reference is removed)
 *
 * \returns	Whether the underlying close on the socket was successful.
 */
int drpc_close(struct drpc *ctx)
{
	int ret;
	uint32_t new_count;

	if (!ctx || ctx->fd <= 0)
	{
		return -1;
	}

	ret = unixcomm_close(ctx->fd);
	D_FREE(ctx);

	return ret;
}
