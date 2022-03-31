/*************************************************************************
  > File Name: store.c
  > Author:perrynzhou
  > Mail:perrynzhou@gmail.com
  > Created Time: 二  3/ 8 11:11:03 2022
 ************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "../drpc/drpc.pb-c.h"
#include "log.h"
#include "dbservice.h"
#include "kv_db.h"
#include "schmea_meta.h"
#include "dbservice.pb-c.h"
#include "dbservice_help.h"

static void dbservice_get_kv(Drpc__Request *drpc_req, Drpc__Response *drpc_resp, void *ctx)
{
  kv_db_t *db = (kv_db_t *)ctx;
  struct drpc_alloc alloc = PROTO_ALLOCATOR_INIT(alloc);
  Dbservice__GetKvReq *req = (Dbservice__GetKvReq *)dbervice_request_alloc(drpc_req, &alloc.alloc);
  Dbservice__GetKvResp resp = DBSERVICE__GET_KV_RESP__INIT;
  char msg_buf[2048] = {'\0'};
  resp.code = -1;
  resp.msg = (char *)&msg_buf;
  schema_meta_rec_t *meta = (schema_meta_rec_t *)dict_get(db->schmea_meta_cache, req->schema_name);
  if (meta != NULL)
  {
    size_t key_size = strlen(req->key);
    char *value = (char *)kv_db_get(db, req->schema_name, req->key, key_size, NULL);
    if (value == NULL)
    {
      snprintf((char *)&msg_buf, 2048, "failed: key %s not found", req->key);
      goto out;
    }
    resp.schema_name = req->schema_name;
    resp.key = req->key;
    resp.value = value;
    resp.code = 0;
    goto out;
  }
  snprintf((char *)&msg_buf, 2048, "failed: schema %s not found", req->schema_name);
out:
  dbservice_finish_response(drpc_req, drpc_resp, req, &resp, &alloc);
}

static void dbservice_del_kv(Drpc__Request *drpc_req, Drpc__Response *drpc_resp, void *ctx)
{
  kv_db_t *db = (kv_db_t *)ctx;
  struct drpc_alloc alloc = PROTO_ALLOCATOR_INIT(alloc);
  Dbservice__DelKvReq *req = (Dbservice__DelKvReq *)dbervice_request_alloc(drpc_req, &alloc.alloc);
  Dbservice__DelKvResp resp = DBSERVICE__DEL_KV_RESP__INIT;
  char msg_buf[2048] = {'\0'};
  resp.code = -1;
  size_t key_size = strlen(req->key);
  schema_meta_rec_t *last_meta = NULL;
  size_t value_size = -1;
  schema_meta_rec_t *meta = (schema_meta_rec_t *)dict_get(db->schmea_meta_cache, req->schema_name);
  if (meta == NULL)
  {

    snprintf((char *)&msg_buf, 2048, "failed: schema %s not found", req->schema_name);
    goto out;
  }

  if (kv_db_search(db, req->schema_name, req->key, key_size) != 0)
  {
    snprintf((char *)&msg_buf, 2048, "failed: key %s  not found", req->key);
    goto out;
  }
  last_meta = schmea_meta_rec_fetch(SYS_SCHEMA_META_TABLE_NAME, req->schema_name, db);
  kv_db_get(db, req->schema_name, req->key, key_size, &value_size);
  __sync_fetch_and_sub(&last_meta->kv_count, 1);
  __sync_fetch_and_sub(&last_meta->bytes, value_size + key_size);
  {
    pthread_mutex_lock(&db->lock);
    schmea_meta_rec_swap(meta, last_meta);
    pthread_mutex_unlock(&db->lock);

    schmea_meta_rec_save(SYS_SCHEMA_META_TABLE_NAME, req->schema_name, last_meta, sizeof(*last_meta), db);
    resp.code = kv_db_del(db, req->schema_name, req->key, key_size);
  }
  resp.code = 0;
  snprintf((char *)&msg_buf, 2048, "succ: del key %s  ok,value size=%ld", req->key, value_size);
out:
  resp.msg = (char *)&msg_buf;
  log_info("******dbservice_del_kv: schmea=%s,ret=%d,msg=%s*********", req->schema_name, resp.code, resp.msg);
  log_info("******dbservice_del_kv: key=%s,value_size=%d*********", req->key, value_size);
  dbservice_finish_response(drpc_req, drpc_resp, req, &resp, &alloc.alloc);
}

static void dbservice_put_kv(Drpc__Request *drpc_req, Drpc__Response *drpc_resp, void *ctx)
{
  kv_db_t *db = (kv_db_t *)ctx;
  struct drpc_alloc alloc = PROTO_ALLOCATOR_INIT(alloc);
  Dbservice__PutKvReq *req = (Dbservice__PutKvReq *)dbervice_request_alloc(drpc_req, &alloc.alloc);
  Dbservice__PutKvResp resp = DBSERVICE__PUT_KV_RESP__INIT;
  char msg_buf[2048] = {'\0'};
  schema_meta_rec_t *meta = (schema_meta_rec_t *)dict_get(db->schmea_meta_cache, req->schema_name);
  resp.code = -1;

  size_t bytes = 0;
  schema_meta_rec_t *last_meta = NULL;
  size_t key_size = strlen(req->key);
  size_t value_size = strlen(req->value);
  if (meta == NULL)
  {
    snprintf((char *)&msg_buf, 2048, "failed: schema %s not found", req->schema_name);
    goto out;
  }

  if (kv_db_search(db, req->schema_name, req->key, key_size) == 0)
  {
    snprintf((char *)&msg_buf, 2048, "failed: key %s  exists", req->key);
    goto out;
  }

  bytes = strlen(req->key) + strlen(req->value);
  last_meta = schmea_meta_rec_fetch(SYS_SCHEMA_META_TABLE_NAME, req->schema_name, db);
  __sync_fetch_and_add(&last_meta->kv_count, 1);
  __sync_fetch_and_add(&last_meta->bytes, bytes);
  {
    pthread_mutex_lock(&db->lock);
    if (kv_db_set(db, req->schema_name, req->key, key_size, req->value, value_size) != -1)
    {
      schmea_meta_rec_swap(meta, last_meta);
      schmea_meta_rec_save(SYS_SCHEMA_META_TABLE_NAME, req->schema_name, last_meta, sizeof(*last_meta), db);
    }
    pthread_mutex_unlock(&db->lock);
  }
  resp.code = 0;
  snprintf((char *)&msg_buf, 2048, "succ: %s put key %s  ok", req->schema_name, req->key);
out:
  resp.msg = (char *)&msg_buf;
  log_info("******dbservice_put_kv: schmea=%s,ret=%d,msg=%s*********", req->schema_name, resp.code, resp.msg);
  log_info("******dbservice_put_kv: key=%s,value=%s*********", req->key, req->value);
  dbservice_finish_response(drpc_req, drpc_resp, req, &resp, &alloc.alloc);
}

static void dbservice_create_schema(Drpc__Request *drpc_req, Drpc__Response *drpc_resp, void *ctx)
{
  kv_db_t *db = (kv_db_t *)ctx;
  struct drpc_alloc alloc = PROTO_ALLOCATOR_INIT(alloc);
  Dbservice__CreateSchemaReq *req = (Dbservice__CreateSchemaReq *)dbervice_request_alloc(drpc_req, &alloc.alloc);
  Dbservice__CreateSchemaResp resp = DBSERVICE__CREATE_SCHEMA_RESP__INIT;
  log_info("request schmea_name=%s", req->name);
  char msg_buf[2048] = {'\0'};
  schema_meta_rec_t *meta = (schema_meta_rec_t *)dict_get(db->schmea_meta_cache, req->name);
  kv_schema_t *schema = NULL;
  schema_meta_rec_t *cur_meta = NULL;
  resp.code = -1;

  if (meta != NULL)
  {
    snprintf((char *)&msg_buf, 2048, "failed: schema %s  exists", req->name);
    goto out;
  }

  schema = kv_schema_alloc(req->name, db, false);
  assert(schema != NULL);
  cur_meta = (schema_meta_rec_t *)calloc(1, sizeof(*cur_meta));
  assert(cur_meta != NULL);
  {
    pthread_mutex_lock(&db->lock);
    schmea_meta_rec_assign(cur_meta, 0, true, 0);
    schmea_cache_add(db->schmea_meta_cache, db, SYS_SCHEMA_META_TABLE_NAME, req->name, cur_meta, sizeof(*cur_meta));
    pthread_mutex_unlock(&db->lock);
  }

  if (schema != NULL)
  {
    resp.code = 0;
    snprintf((char *)&msg_buf, 2048, "succ: new schema %s  ok", req->name);
    goto out;
  }
  snprintf((char *)&msg_buf, 2048, "failed:init schema  %s ctx", req->name);
out:
  resp.msg = (char *)&msg_buf;
  log_info("******dbservice_create_schema: schmea=%s,ret=%d,msg=%s*********", req->name, resp.code, resp.msg);
  dbservice_finish_response(drpc_req, drpc_resp, req, &resp, &alloc.alloc);
}

static void dbservice_drop_schema(Drpc__Request *drpc_req, Drpc__Response *drpc_resp, void *ctx)
{
  kv_db_t *db = (kv_db_t *)ctx;
  struct drpc_alloc alloc = PROTO_ALLOCATOR_INIT(alloc);
  Dbservice__DropSchemaReq *req = (Dbservice__DropSchemaReq *)dbervice_request_alloc(drpc_req, &alloc.alloc);
  Dbservice__DropSchemaResp resp = DBSERVICE__DROP_SCHEMA_RESP__INIT;
  schema_meta_rec_t *meta = (schema_meta_rec_t *)dict_get(db->schmea_meta_cache, req->name);
  char msg_buf[2048] = {'\0'};
  resp.code = -1;
  if (meta == NULL)
  {
    snprintf((char *)&msg_buf, 2048, "failed: schema %s not found", req->name);
    goto out;
  }

  {
    pthread_mutex_lock(&db->lock);
    kv_schema_t *schema = kv_db_fetch_schema(db, req->name);
    kv_schema_destroy(schema);
    schmea_cache_del(db->schmea_meta_cache, db, SYS_SCHEMA_META_TABLE_NAME, req->name);
    pthread_mutex_unlock(&db->lock);
  }

  resp.code = 0;
  snprintf((char *)&msg_buf, 2048, "succ: drop schema %s ok", req->name);
  resp.name = req->name;
out:
  resp.msg = (char *)&msg_buf;
  log_info("******dbservice_drop_schema: schmea=%s,ret=%d,msg=%s*********", req->name, resp.code, resp.msg);
  dbservice_finish_response(drpc_req, drpc_resp, req, &resp, &alloc);
}

static void dbservice_query_schema_meta(Drpc__Request *drpc_req, Drpc__Response *drpc_resp, void *ctx)
{
  kv_db_t *db = (kv_db_t *)ctx;
  struct drpc_alloc alloc = PROTO_ALLOCATOR_INIT(alloc);
  Dbservice__QuerySchemaReq *req = (Dbservice__QuerySchemaReq *)dbervice_request_alloc(drpc_req, &alloc.alloc);
  Dbservice__QuerySchemaResp resp = DBSERVICE__QUERY_SCHEMA_RESP__INIT;
  schema_meta_rec_t *meta = (schema_meta_rec_t *)dict_get(db->schmea_meta_cache, req->name);
  char msg_buf[2048] = {'\0'};
  resp.code = -1;
  if (meta != NULL)
  {
    resp.code = 0;
    snprintf((char *)&msg_buf, 2048, "succ: %s", req->name);
    resp.meta = schmea_meta_rec_dump(meta);
    goto out;
  }
  meta = schmea_meta_rec_fetch(SYS_SCHEMA_META_TABLE_NAME, req->name, db);
  if (meta == NULL)
  {
    snprintf((char *)&msg_buf, 2048, "failed: %s not found in meta table", req->name);
    goto out;
  }
  resp.code = 0;
  snprintf((char *)&msg_buf, 2048, "succ: query %s ok", req->name);
  resp.name = req->name;
  resp.meta = schmea_meta_rec_dump(meta);
out:
  resp.msg = (char *)&msg_buf;
  log_info("******dbservice_query_schema_meta: schmea=%s,ret=%d,msg=%s*********", req->name, resp.code, resp.msg);
  if (meta != NULL)
  {
    log_info("******dbservice_query_schema_meta: key_count=%d,bytes=%ld,is_active=%d*********", meta->kv_count, meta->bytes, meta->is_active);
  }
  dbservice_finish_response(drpc_req, drpc_resp, req, &resp, &alloc);
}
void process_drpc_request(Drpc__Request *drpc_req, Drpc__Response *drpc_resp, void *ctx)
{
  switch (drpc_req->method)
  {
  case DRPC_METHOD_CREATE_SCHEMA:
    dbservice_create_schema(drpc_req, drpc_resp, ctx);
    break;
  case DRPC_METHOD_DROP_SCHEMA:
    dbservice_drop_schema(drpc_req, drpc_resp, ctx);
    break;
  case DRPC_METHOD_PUT_KV:
    dbservice_put_kv(drpc_req, drpc_resp, ctx);
    break;
  case DRPC_METHOD_GET_KV:
    dbservice_get_kv(drpc_req, drpc_resp, ctx);
    break;
  case DRPC_METHOD_DEL_KV:
    dbservice_del_kv(drpc_req, drpc_resp, ctx);
    break;
  case DRPC_METHOD_QUERY_SCHEMA:
    dbservice_query_schema_meta(drpc_req, drpc_resp, ctx);
    break;
  default:
    break;
  }
}