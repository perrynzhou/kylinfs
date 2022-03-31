/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: dbservice.proto */

#ifndef PROTOBUF_C_dbservice_2eproto__INCLUDED
#define PROTOBUF_C_dbservice_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Dbservice__CreateSchemaReq Dbservice__CreateSchemaReq;
typedef struct _Dbservice__CreateSchemaResp Dbservice__CreateSchemaResp;
typedef struct _Dbservice__QuerySchemaReq Dbservice__QuerySchemaReq;
typedef struct _Dbservice__QuerySchemaResp Dbservice__QuerySchemaResp;
typedef struct _Dbservice__DropSchemaReq Dbservice__DropSchemaReq;
typedef struct _Dbservice__DropSchemaResp Dbservice__DropSchemaResp;
typedef struct _Dbservice__PutKvReq Dbservice__PutKvReq;
typedef struct _Dbservice__PutKvResp Dbservice__PutKvResp;
typedef struct _Dbservice__GetKvReq Dbservice__GetKvReq;
typedef struct _Dbservice__GetKvResp Dbservice__GetKvResp;
typedef struct _Dbservice__DelKvReq Dbservice__DelKvReq;
typedef struct _Dbservice__DelKvResp Dbservice__DelKvResp;


/* --- enums --- */


/* --- messages --- */

struct  _Dbservice__CreateSchemaReq
{
  ProtobufCMessage base;
  char *name;
};
#define DBSERVICE__CREATE_SCHEMA_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&dbservice__create_schema_req__descriptor) \
    , (char *)protobuf_c_empty_string }


struct  _Dbservice__CreateSchemaResp
{
  ProtobufCMessage base;
  char *name;
  int32_t code;
  char *msg;
};
#define DBSERVICE__CREATE_SCHEMA_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&dbservice__create_schema_resp__descriptor) \
    , (char *)protobuf_c_empty_string, 0, (char *)protobuf_c_empty_string }


struct  _Dbservice__QuerySchemaReq
{
  ProtobufCMessage base;
  char *name;
};
#define DBSERVICE__QUERY_SCHEMA_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&dbservice__query_schema_req__descriptor) \
    , (char *)protobuf_c_empty_string }


struct  _Dbservice__QuerySchemaResp
{
  ProtobufCMessage base;
  char *name;
  int32_t code;
  char *msg;
  char *meta;
};
#define DBSERVICE__QUERY_SCHEMA_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&dbservice__query_schema_resp__descriptor) \
    , (char *)protobuf_c_empty_string, 0, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string }


struct  _Dbservice__DropSchemaReq
{
  ProtobufCMessage base;
  char *name;
};
#define DBSERVICE__DROP_SCHEMA_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&dbservice__drop_schema_req__descriptor) \
    , (char *)protobuf_c_empty_string }


struct  _Dbservice__DropSchemaResp
{
  ProtobufCMessage base;
  char *name;
  int32_t code;
  char *msg;
};
#define DBSERVICE__DROP_SCHEMA_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&dbservice__drop_schema_resp__descriptor) \
    , (char *)protobuf_c_empty_string, 0, (char *)protobuf_c_empty_string }


struct  _Dbservice__PutKvReq
{
  ProtobufCMessage base;
  char *schema_name;
  char *key;
  char *value;
};
#define DBSERVICE__PUT_KV_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&dbservice__put_kv_req__descriptor) \
    , (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string }


struct  _Dbservice__PutKvResp
{
  ProtobufCMessage base;
  char *schema_name;
  int32_t code;
  char *msg;
};
#define DBSERVICE__PUT_KV_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&dbservice__put_kv_resp__descriptor) \
    , (char *)protobuf_c_empty_string, 0, (char *)protobuf_c_empty_string }


struct  _Dbservice__GetKvReq
{
  ProtobufCMessage base;
  char *schema_name;
  char *key;
};
#define DBSERVICE__GET_KV_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&dbservice__get_kv_req__descriptor) \
    , (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string }


struct  _Dbservice__GetKvResp
{
  ProtobufCMessage base;
  char *schema_name;
  char *key;
  char *value;
  int32_t code;
  char *msg;
};
#define DBSERVICE__GET_KV_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&dbservice__get_kv_resp__descriptor) \
    , (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, 0, (char *)protobuf_c_empty_string }


struct  _Dbservice__DelKvReq
{
  ProtobufCMessage base;
  char *schema_name;
  char *key;
};
#define DBSERVICE__DEL_KV_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&dbservice__del_kv_req__descriptor) \
    , (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string }


struct  _Dbservice__DelKvResp
{
  ProtobufCMessage base;
  int32_t code;
  char *msg;
  char *schema_name;
  char *key;
  char *value;
};
#define DBSERVICE__DEL_KV_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&dbservice__del_kv_resp__descriptor) \
    , 0, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string }


/* Dbservice__CreateSchemaReq methods */
void   dbservice__create_schema_req__init
                     (Dbservice__CreateSchemaReq         *message);
size_t dbservice__create_schema_req__get_packed_size
                     (const Dbservice__CreateSchemaReq   *message);
size_t dbservice__create_schema_req__pack
                     (const Dbservice__CreateSchemaReq   *message,
                      uint8_t             *out);
size_t dbservice__create_schema_req__pack_to_buffer
                     (const Dbservice__CreateSchemaReq   *message,
                      ProtobufCBuffer     *buffer);
Dbservice__CreateSchemaReq *
       dbservice__create_schema_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   dbservice__create_schema_req__free_unpacked
                     (Dbservice__CreateSchemaReq *message,
                      ProtobufCAllocator *allocator);
/* Dbservice__CreateSchemaResp methods */
void   dbservice__create_schema_resp__init
                     (Dbservice__CreateSchemaResp         *message);
size_t dbservice__create_schema_resp__get_packed_size
                     (const Dbservice__CreateSchemaResp   *message);
size_t dbservice__create_schema_resp__pack
                     (const Dbservice__CreateSchemaResp   *message,
                      uint8_t             *out);
size_t dbservice__create_schema_resp__pack_to_buffer
                     (const Dbservice__CreateSchemaResp   *message,
                      ProtobufCBuffer     *buffer);
Dbservice__CreateSchemaResp *
       dbservice__create_schema_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   dbservice__create_schema_resp__free_unpacked
                     (Dbservice__CreateSchemaResp *message,
                      ProtobufCAllocator *allocator);
/* Dbservice__QuerySchemaReq methods */
void   dbservice__query_schema_req__init
                     (Dbservice__QuerySchemaReq         *message);
size_t dbservice__query_schema_req__get_packed_size
                     (const Dbservice__QuerySchemaReq   *message);
size_t dbservice__query_schema_req__pack
                     (const Dbservice__QuerySchemaReq   *message,
                      uint8_t             *out);
size_t dbservice__query_schema_req__pack_to_buffer
                     (const Dbservice__QuerySchemaReq   *message,
                      ProtobufCBuffer     *buffer);
Dbservice__QuerySchemaReq *
       dbservice__query_schema_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   dbservice__query_schema_req__free_unpacked
                     (Dbservice__QuerySchemaReq *message,
                      ProtobufCAllocator *allocator);
/* Dbservice__QuerySchemaResp methods */
void   dbservice__query_schema_resp__init
                     (Dbservice__QuerySchemaResp         *message);
size_t dbservice__query_schema_resp__get_packed_size
                     (const Dbservice__QuerySchemaResp   *message);
size_t dbservice__query_schema_resp__pack
                     (const Dbservice__QuerySchemaResp   *message,
                      uint8_t             *out);
size_t dbservice__query_schema_resp__pack_to_buffer
                     (const Dbservice__QuerySchemaResp   *message,
                      ProtobufCBuffer     *buffer);
Dbservice__QuerySchemaResp *
       dbservice__query_schema_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   dbservice__query_schema_resp__free_unpacked
                     (Dbservice__QuerySchemaResp *message,
                      ProtobufCAllocator *allocator);
/* Dbservice__DropSchemaReq methods */
void   dbservice__drop_schema_req__init
                     (Dbservice__DropSchemaReq         *message);
size_t dbservice__drop_schema_req__get_packed_size
                     (const Dbservice__DropSchemaReq   *message);
size_t dbservice__drop_schema_req__pack
                     (const Dbservice__DropSchemaReq   *message,
                      uint8_t             *out);
size_t dbservice__drop_schema_req__pack_to_buffer
                     (const Dbservice__DropSchemaReq   *message,
                      ProtobufCBuffer     *buffer);
Dbservice__DropSchemaReq *
       dbservice__drop_schema_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   dbservice__drop_schema_req__free_unpacked
                     (Dbservice__DropSchemaReq *message,
                      ProtobufCAllocator *allocator);
/* Dbservice__DropSchemaResp methods */
void   dbservice__drop_schema_resp__init
                     (Dbservice__DropSchemaResp         *message);
size_t dbservice__drop_schema_resp__get_packed_size
                     (const Dbservice__DropSchemaResp   *message);
size_t dbservice__drop_schema_resp__pack
                     (const Dbservice__DropSchemaResp   *message,
                      uint8_t             *out);
size_t dbservice__drop_schema_resp__pack_to_buffer
                     (const Dbservice__DropSchemaResp   *message,
                      ProtobufCBuffer     *buffer);
Dbservice__DropSchemaResp *
       dbservice__drop_schema_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   dbservice__drop_schema_resp__free_unpacked
                     (Dbservice__DropSchemaResp *message,
                      ProtobufCAllocator *allocator);
/* Dbservice__PutKvReq methods */
void   dbservice__put_kv_req__init
                     (Dbservice__PutKvReq         *message);
size_t dbservice__put_kv_req__get_packed_size
                     (const Dbservice__PutKvReq   *message);
size_t dbservice__put_kv_req__pack
                     (const Dbservice__PutKvReq   *message,
                      uint8_t             *out);
size_t dbservice__put_kv_req__pack_to_buffer
                     (const Dbservice__PutKvReq   *message,
                      ProtobufCBuffer     *buffer);
Dbservice__PutKvReq *
       dbservice__put_kv_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   dbservice__put_kv_req__free_unpacked
                     (Dbservice__PutKvReq *message,
                      ProtobufCAllocator *allocator);
/* Dbservice__PutKvResp methods */
void   dbservice__put_kv_resp__init
                     (Dbservice__PutKvResp         *message);
size_t dbservice__put_kv_resp__get_packed_size
                     (const Dbservice__PutKvResp   *message);
size_t dbservice__put_kv_resp__pack
                     (const Dbservice__PutKvResp   *message,
                      uint8_t             *out);
size_t dbservice__put_kv_resp__pack_to_buffer
                     (const Dbservice__PutKvResp   *message,
                      ProtobufCBuffer     *buffer);
Dbservice__PutKvResp *
       dbservice__put_kv_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   dbservice__put_kv_resp__free_unpacked
                     (Dbservice__PutKvResp *message,
                      ProtobufCAllocator *allocator);
/* Dbservice__GetKvReq methods */
void   dbservice__get_kv_req__init
                     (Dbservice__GetKvReq         *message);
size_t dbservice__get_kv_req__get_packed_size
                     (const Dbservice__GetKvReq   *message);
size_t dbservice__get_kv_req__pack
                     (const Dbservice__GetKvReq   *message,
                      uint8_t             *out);
size_t dbservice__get_kv_req__pack_to_buffer
                     (const Dbservice__GetKvReq   *message,
                      ProtobufCBuffer     *buffer);
Dbservice__GetKvReq *
       dbservice__get_kv_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   dbservice__get_kv_req__free_unpacked
                     (Dbservice__GetKvReq *message,
                      ProtobufCAllocator *allocator);
/* Dbservice__GetKvResp methods */
void   dbservice__get_kv_resp__init
                     (Dbservice__GetKvResp         *message);
size_t dbservice__get_kv_resp__get_packed_size
                     (const Dbservice__GetKvResp   *message);
size_t dbservice__get_kv_resp__pack
                     (const Dbservice__GetKvResp   *message,
                      uint8_t             *out);
size_t dbservice__get_kv_resp__pack_to_buffer
                     (const Dbservice__GetKvResp   *message,
                      ProtobufCBuffer     *buffer);
Dbservice__GetKvResp *
       dbservice__get_kv_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   dbservice__get_kv_resp__free_unpacked
                     (Dbservice__GetKvResp *message,
                      ProtobufCAllocator *allocator);
/* Dbservice__DelKvReq methods */
void   dbservice__del_kv_req__init
                     (Dbservice__DelKvReq         *message);
size_t dbservice__del_kv_req__get_packed_size
                     (const Dbservice__DelKvReq   *message);
size_t dbservice__del_kv_req__pack
                     (const Dbservice__DelKvReq   *message,
                      uint8_t             *out);
size_t dbservice__del_kv_req__pack_to_buffer
                     (const Dbservice__DelKvReq   *message,
                      ProtobufCBuffer     *buffer);
Dbservice__DelKvReq *
       dbservice__del_kv_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   dbservice__del_kv_req__free_unpacked
                     (Dbservice__DelKvReq *message,
                      ProtobufCAllocator *allocator);
/* Dbservice__DelKvResp methods */
void   dbservice__del_kv_resp__init
                     (Dbservice__DelKvResp         *message);
size_t dbservice__del_kv_resp__get_packed_size
                     (const Dbservice__DelKvResp   *message);
size_t dbservice__del_kv_resp__pack
                     (const Dbservice__DelKvResp   *message,
                      uint8_t             *out);
size_t dbservice__del_kv_resp__pack_to_buffer
                     (const Dbservice__DelKvResp   *message,
                      ProtobufCBuffer     *buffer);
Dbservice__DelKvResp *
       dbservice__del_kv_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   dbservice__del_kv_resp__free_unpacked
                     (Dbservice__DelKvResp *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Dbservice__CreateSchemaReq_Closure)
                 (const Dbservice__CreateSchemaReq *message,
                  void *closure_data);
typedef void (*Dbservice__CreateSchemaResp_Closure)
                 (const Dbservice__CreateSchemaResp *message,
                  void *closure_data);
typedef void (*Dbservice__QuerySchemaReq_Closure)
                 (const Dbservice__QuerySchemaReq *message,
                  void *closure_data);
typedef void (*Dbservice__QuerySchemaResp_Closure)
                 (const Dbservice__QuerySchemaResp *message,
                  void *closure_data);
typedef void (*Dbservice__DropSchemaReq_Closure)
                 (const Dbservice__DropSchemaReq *message,
                  void *closure_data);
typedef void (*Dbservice__DropSchemaResp_Closure)
                 (const Dbservice__DropSchemaResp *message,
                  void *closure_data);
typedef void (*Dbservice__PutKvReq_Closure)
                 (const Dbservice__PutKvReq *message,
                  void *closure_data);
typedef void (*Dbservice__PutKvResp_Closure)
                 (const Dbservice__PutKvResp *message,
                  void *closure_data);
typedef void (*Dbservice__GetKvReq_Closure)
                 (const Dbservice__GetKvReq *message,
                  void *closure_data);
typedef void (*Dbservice__GetKvResp_Closure)
                 (const Dbservice__GetKvResp *message,
                  void *closure_data);
typedef void (*Dbservice__DelKvReq_Closure)
                 (const Dbservice__DelKvReq *message,
                  void *closure_data);
typedef void (*Dbservice__DelKvResp_Closure)
                 (const Dbservice__DelKvResp *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor dbservice__create_schema_req__descriptor;
extern const ProtobufCMessageDescriptor dbservice__create_schema_resp__descriptor;
extern const ProtobufCMessageDescriptor dbservice__query_schema_req__descriptor;
extern const ProtobufCMessageDescriptor dbservice__query_schema_resp__descriptor;
extern const ProtobufCMessageDescriptor dbservice__drop_schema_req__descriptor;
extern const ProtobufCMessageDescriptor dbservice__drop_schema_resp__descriptor;
extern const ProtobufCMessageDescriptor dbservice__put_kv_req__descriptor;
extern const ProtobufCMessageDescriptor dbservice__put_kv_resp__descriptor;
extern const ProtobufCMessageDescriptor dbservice__get_kv_req__descriptor;
extern const ProtobufCMessageDescriptor dbservice__get_kv_resp__descriptor;
extern const ProtobufCMessageDescriptor dbservice__del_kv_req__descriptor;
extern const ProtobufCMessageDescriptor dbservice__del_kv_resp__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_dbservice_2eproto__INCLUDED */