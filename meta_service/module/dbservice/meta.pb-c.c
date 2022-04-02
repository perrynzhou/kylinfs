/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: meta.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "meta.pb-c.h"
void   dbservice__chunk_server_heal_req__init
                     (Dbservice__ChunkServerHealReq         *message)
{
  static const Dbservice__ChunkServerHealReq init_value = DBSERVICE__CHUNK_SERVER_HEAL_REQ__INIT;
  *message = init_value;
}
size_t dbservice__chunk_server_heal_req__get_packed_size
                     (const Dbservice__ChunkServerHealReq *message)
{
  assert(message->base.descriptor == &dbservice__chunk_server_heal_req__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t dbservice__chunk_server_heal_req__pack
                     (const Dbservice__ChunkServerHealReq *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &dbservice__chunk_server_heal_req__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t dbservice__chunk_server_heal_req__pack_to_buffer
                     (const Dbservice__ChunkServerHealReq *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &dbservice__chunk_server_heal_req__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Dbservice__ChunkServerHealReq *
       dbservice__chunk_server_heal_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Dbservice__ChunkServerHealReq *)
     protobuf_c_message_unpack (&dbservice__chunk_server_heal_req__descriptor,
                                allocator, len, data);
}
void   dbservice__chunk_server_heal_req__free_unpacked
                     (Dbservice__ChunkServerHealReq *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &dbservice__chunk_server_heal_req__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   dbservice__chunk_server_heal_resp__init
                     (Dbservice__ChunkServerHealResp         *message)
{
  static const Dbservice__ChunkServerHealResp init_value = DBSERVICE__CHUNK_SERVER_HEAL_RESP__INIT;
  *message = init_value;
}
size_t dbservice__chunk_server_heal_resp__get_packed_size
                     (const Dbservice__ChunkServerHealResp *message)
{
  assert(message->base.descriptor == &dbservice__chunk_server_heal_resp__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t dbservice__chunk_server_heal_resp__pack
                     (const Dbservice__ChunkServerHealResp *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &dbservice__chunk_server_heal_resp__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t dbservice__chunk_server_heal_resp__pack_to_buffer
                     (const Dbservice__ChunkServerHealResp *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &dbservice__chunk_server_heal_resp__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Dbservice__ChunkServerHealResp *
       dbservice__chunk_server_heal_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Dbservice__ChunkServerHealResp *)
     protobuf_c_message_unpack (&dbservice__chunk_server_heal_resp__descriptor,
                                allocator, len, data);
}
void   dbservice__chunk_server_heal_resp__free_unpacked
                     (Dbservice__ChunkServerHealResp *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &dbservice__chunk_server_heal_resp__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor dbservice__chunk_server_heal_req__field_descriptors[6] =
{
  {
    "id",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Dbservice__ChunkServerHealReq, id),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ip",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Dbservice__ChunkServerHealReq, ip),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "port",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Dbservice__ChunkServerHealReq, port),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "block_mb_size",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Dbservice__ChunkServerHealReq, block_mb_size),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "total_mb_size",
    5,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT64,
    0,   /* quantifier_offset */
    offsetof(Dbservice__ChunkServerHealReq, total_mb_size),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "is_init",
    6,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(Dbservice__ChunkServerHealReq, is_init),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned dbservice__chunk_server_heal_req__field_indices_by_name[] = {
  3,   /* field[3] = block_mb_size */
  0,   /* field[0] = id */
  1,   /* field[1] = ip */
  5,   /* field[5] = is_init */
  2,   /* field[2] = port */
  4,   /* field[4] = total_mb_size */
};
static const ProtobufCIntRange dbservice__chunk_server_heal_req__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 6 }
};
const ProtobufCMessageDescriptor dbservice__chunk_server_heal_req__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "dbservice.ChunkServerHealReq",
  "ChunkServerHealReq",
  "Dbservice__ChunkServerHealReq",
  "dbservice",
  sizeof(Dbservice__ChunkServerHealReq),
  6,
  dbservice__chunk_server_heal_req__field_descriptors,
  dbservice__chunk_server_heal_req__field_indices_by_name,
  1,  dbservice__chunk_server_heal_req__number_ranges,
  (ProtobufCMessageInit) dbservice__chunk_server_heal_req__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor dbservice__chunk_server_heal_resp__field_descriptors[2] =
{
  {
    "code",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Dbservice__ChunkServerHealResp, code),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "msg",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Dbservice__ChunkServerHealResp, msg),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned dbservice__chunk_server_heal_resp__field_indices_by_name[] = {
  0,   /* field[0] = code */
  1,   /* field[1] = msg */
};
static const ProtobufCIntRange dbservice__chunk_server_heal_resp__number_ranges[1 + 1] =
{
  { 2, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor dbservice__chunk_server_heal_resp__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "dbservice.ChunkServerHealResp",
  "ChunkServerHealResp",
  "Dbservice__ChunkServerHealResp",
  "dbservice",
  sizeof(Dbservice__ChunkServerHealResp),
  2,
  dbservice__chunk_server_heal_resp__field_descriptors,
  dbservice__chunk_server_heal_resp__field_indices_by_name,
  1,  dbservice__chunk_server_heal_resp__number_ranges,
  (ProtobufCMessageInit) dbservice__chunk_server_heal_resp__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCMethodDescriptor dbservice__service__method_descriptors[1] =
{
  { "HealFunc", &dbservice__chunk_server_heal_req__descriptor, &dbservice__chunk_server_heal_resp__descriptor },
};
const unsigned dbservice__service__method_indices_by_name[] = {
  0         /* HealFunc */
};
const ProtobufCServiceDescriptor dbservice__service__descriptor =
{
  PROTOBUF_C__SERVICE_DESCRIPTOR_MAGIC,
  "dbservice.Service",
  "Service",
  "Dbservice__Service",
  "dbservice",
  1,
  dbservice__service__method_descriptors,
  dbservice__service__method_indices_by_name
};
void dbservice__service__heal_func(ProtobufCService *service,
                                   const Dbservice__ChunkServerHealReq *input,
                                   Dbservice__ChunkServerHealResp_Closure closure,
                                   void *closure_data)
{
  assert(service->descriptor == &dbservice__service__descriptor);
  service->invoke(service, 0, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void dbservice__service__init (Dbservice__Service_Service *service,
                               Dbservice__Service_ServiceDestroy destroy)
{
  protobuf_c_service_generated_init (&service->base,
                                     &dbservice__service__descriptor,
                                     (ProtobufCServiceDestroy) destroy);
}