/*
 * (C) Copyright 2018-2021 Intel Corporation.
 *
 * SPDX-License-Identifier: BSD-2-Clause-Patent
 */

#ifndef __DAOS_DRPC_H__
#define __DAOS_DRPC_H__

#include "drpc.pb-c.h"
#include <stdbool.h>
#include <stdlib.h>
#define D_ALLOC_CORE(ptr, size, count)					\
	do {								\
		(ptr) = (__typeof__(ptr))calloc((count), (size));	\
	} while (0)
#define D_ALLOC(ptr, size) D_ALLOC_CORE(ptr, size, 1)
#define D_FREE(ptr)   \
	do                \
	{                 \
		free(ptr);  \
		(ptr) = NULL; \
	} while (0)

#define D_ALLOC_PTR(ptr) D_ALLOC(ptr, sizeof(*ptr))


#define UNIXCOMM_MAXMSGSIZE (1 << 17)

typedef void (*drpc_handler_func)(Drpc__Request *, Drpc__Response *,void *);

struct drpc_handler
{
  int module_id;
  drpc_handler_func handler;
};


struct drpc_alloc
{
	ProtobufCAllocator alloc;
	bool oom;
};

void *
daos_drpc_alloc(void *arg, size_t size);

void daos_drpc_free(void *allocater_data, void *pointer);

#define PROTO_ALLOCATOR_INIT(self)      \
	{                                   \
		.alloc.alloc = daos_drpc_alloc, \
		.alloc.free = daos_drpc_free,   \
		.alloc.allocator_data = &self   \
	}

/**
 * dRPC connection context. This includes all details needed to communicate
 * on the dRPC channel.
 */
struct drpc
{
	int fd;	   /** File descriptor of the unix domain socket */
	int flags; /** Flags set on unix domain socket */
	/**
	 * Handler for messages received by a listening drpc context.
	 * For client contexts, this is NULL.
	 */
	drpc_handler_func handler;
};

enum rpcflags
{
	R_SYNC = 1
};

int drpc_call_create(struct drpc *ctx, int32_t module, int32_t method,
					 Drpc__Request **callp);
void drpc_call_free(Drpc__Request *call);

Drpc__Response *drpc_response_create(Drpc__Request *call);
void drpc_response_free(Drpc__Response *resp);

int drpc_call(struct drpc *ctx, int flags, Drpc__Request *msg,
			  Drpc__Response **resp);
int drpc_connect(char *sockaddr, struct drpc **);
struct drpc *drpc_listen(char *sockaddr, drpc_handler_func handler);
bool drpc_is_valid_listener(struct drpc *ctx);
struct drpc *drpc_accept(struct drpc *listener_ctx);
struct drpc *drpc_alloc(int fd);
int drpc_recv_call(struct drpc *ctx, Drpc__Request **call);
int drpc_send_response(struct drpc *ctx, Drpc__Response *resp);
int drpc_close(struct drpc *ctx);

int drpc_add_ref(struct drpc *ctx);

#endif /* __DAOS_DRPC_H__ */
