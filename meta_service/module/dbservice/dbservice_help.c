/*************************************************************************
    > File Name: dbservice_help.c
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Thu 17 Mar 2022 01:54:59 AM UTC
 ************************************************************************/

#include <stdio.h>
#include "dbservice_help.h"

// dbservice__create_schema_resp__pack
void *dbervice_request_alloc(Drpc__Request *drpc_req, void *alloc)
{
  void *req = NULL;
  ProtobufCAllocator *allocator = (ProtobufCAllocator *)alloc;

  switch (drpc_req->method)
  {
    {
    case DRPC_METHOD_CREATE_SCHEMA:
      req = dbservice__create_schema_req__unpack(allocator, drpc_req->body.len, drpc_req->body.data);
      break;
    case DRPC_METHOD_DROP_SCHEMA:
      req = dbservice__drop_schema_req__unpack(allocator, drpc_req->body.len, drpc_req->body.data);
      break;
    case DRPC_METHOD_PUT_KV:
      req = dbservice__put_kv_req__unpack(allocator, drpc_req->body.len, drpc_req->body.data);
      break;
    case DRPC_METHOD_GET_KV:
      req = dbservice__get_kv_req__unpack(allocator, drpc_req->body.len, drpc_req->body.data);
      break;
    case DRPC_METHOD_DEL_KV:
      req = dbservice__del_kv_req__unpack(allocator, drpc_req->body.len, drpc_req->body.data);
      break;
    case DRPC_METHOD_QUERY_SCHEMA:
      req = dbservice__query_schema_req__unpack(allocator, drpc_req->body.len, drpc_req->body.data);
      break;
    default:
      break;
    }
  }
  return req;
}

inline static void dbservice_response_pack(Drpc__Request *drpc_req, void *resp, void *buf)
{
  switch (drpc_req->method)
  {
    {
    case DRPC_METHOD_CREATE_SCHEMA:
      dbservice__create_schema_resp__pack((Dbservice__CreateSchemaResp *)resp, (uint8_t *)buf);
      break;
    case DRPC_METHOD_DROP_SCHEMA:
      dbservice__drop_schema_resp__pack((Dbservice__DropSchemaResp *)resp, (uint8_t *)buf);
      break;
    case DRPC_METHOD_PUT_KV:
      dbservice__put_kv_resp__pack((Dbservice__PutKvResp *)resp, (uint8_t *)buf);
      break;
    case DRPC_METHOD_GET_KV:
      dbservice__get_kv_resp__pack((Dbservice__GetKvResp *)resp, (uint8_t *)buf);
      break;
    case DRPC_METHOD_DEL_KV:
      dbservice__del_kv_resp__pack((Dbservice__DelKvResp *)resp, (uint8_t *)buf);
      break;
    case DRPC_METHOD_QUERY_SCHEMA:
      dbservice__query_schema_resp__pack((Dbservice__QuerySchemaResp *)resp, (uint8_t *)buf);
      break;
    default:
      break;
    }
  }
}
inline static void dbservice_request_free_unpacked(Drpc__Request *drpc_req, void *request, void *alloc)
{

  ProtobufCAllocator *allocator = (ProtobufCAllocator *)alloc;
  switch (drpc_req->method)

  {
  case DRPC_METHOD_CREATE_SCHEMA:
    dbservice__create_schema_req__free_unpacked((Dbservice__CreateSchemaReq *)request, allocator);
    break;
  case DRPC_METHOD_DROP_SCHEMA:
    dbservice__drop_schema_req__free_unpacked((Dbservice__DropSchemaReq *)request, allocator);
    break;
  case DRPC_METHOD_PUT_KV:
    dbservice__put_kv_req__free_unpacked((Dbservice__PutKvReq *)request, allocator);
    break;
  case DRPC_METHOD_GET_KV:
    dbservice__get_kv_req__free_unpacked((Dbservice__GetKvReq *)request, allocator);
    break;
    case DRPC_METHOD_DEL_KV:
    dbservice__del_kv_req__free_unpacked((Dbservice__DelKvReq *)request, allocator);
    break;
    case DRPC_METHOD_QUERY_SCHEMA:
      dbservice__query_schema_req__free_unpacked((Dbservice__QuerySchemaReq *)request, allocator);
      break;
  default:
    break;
  }
}
inline static size_t dbservice_response_get_packed_size(Drpc__Request *drpc_req, void *ctx)
{
  size_t resp_len = 0;
  switch (drpc_req->method)
  {
    {
    case DRPC_METHOD_CREATE_SCHEMA:
      resp_len = dbservice__create_schema_resp__get_packed_size((Dbservice__CreateSchemaResp *)ctx);
      break;
    case DRPC_METHOD_DROP_SCHEMA:
      resp_len = dbservice__drop_schema_resp__get_packed_size((Dbservice__DropSchemaResp *)ctx);
      break;
    case DRPC_METHOD_PUT_KV:
      resp_len = dbservice__put_kv_resp__get_packed_size((Dbservice__PutKvResp *)ctx);
      break;
    case DRPC_METHOD_GET_KV:
      resp_len = dbservice__get_kv_resp__get_packed_size((Dbservice__GetKvResp *)ctx);
      break;
    case DRPC_METHOD_DEL_KV:
      resp_len = dbservice__del_kv_resp__get_packed_size((Dbservice__DelKvResp *)ctx);
      break;
    case DRPC_METHOD_QUERY_SCHEMA:
      resp_len =dbservice__query_schema_resp__get_packed_size((Dbservice__QuerySchemaResp *)ctx);
      break;
    default:
      break;
    }
  }
      return resp_len;
}

void dbservice_finish_response(Drpc__Request *drpc_req, Drpc__Response *drpc_resp, void *request, void *response, void *alloc)
{
  size_t resp_len = dbservice_response_get_packed_size(drpc_req, response);
  uint8_t *buf;
  D_ALLOC(buf, resp_len);
  if (buf != NULL)
  {
    dbservice_response_pack(drpc_req, response, buf);
    drpc_resp->body.len = resp_len;
    drpc_resp->body.data = buf;
  }
  dbservice_request_free_unpacked(drpc_req, request, alloc);
}