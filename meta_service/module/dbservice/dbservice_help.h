/*************************************************************************
  > File Name: dbservice_help.h
  > Author:perrynzhou
  > Mail:perrynzhou@gmail.com
  > Created Time: Thu 17 Mar 2022 01:54:40 AM UTC
 ************************************************************************/

#ifndef _DBSERVICE_HELP_H
#define _DBSERVICE_HELP_H
#include "../drpc/drpc.pb-c.h"
#include "dbservice.pb-c.h"
#include "../drpc/drpc.h"
enum drpc_method
{
  DRPC_METHOD_CREATE_SCHEMA = 201,
  DRPC_METHOD_DROP_SCHEMA = 202,
  DRPC_METHOD_QUERY_SCHEMA = 203,

  DRPC_METHOD_PUT_KV = 301,
  DRPC_METHOD_GET_KV = 302,
  DRPC_METHOD_DEL_KV = 303,
};
void dbservice_finish_response(Drpc__Request *drpc_req, Drpc__Response *drpc_resp, void *request, void *response, void *alloc);
void *dbervice_request_alloc(Drpc__Request *drpc_req, void *alloc);
#endif
