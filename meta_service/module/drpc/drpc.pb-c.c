/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: drpc.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "drpc.pb-c.h"
void   drpc__request__init
                     (Drpc__Request         *message)
{
  static const Drpc__Request init_value = DRPC__REQUEST__INIT;
  *message = init_value;
}
size_t drpc__request__get_packed_size
                     (const Drpc__Request *message)
{
  assert(message->base.descriptor == &drpc__request__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t drpc__request__pack
                     (const Drpc__Request *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &drpc__request__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t drpc__request__pack_to_buffer
                     (const Drpc__Request *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &drpc__request__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Drpc__Request *
       drpc__request__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Drpc__Request *)
     protobuf_c_message_unpack (&drpc__request__descriptor,
                                allocator, len, data);
}
void   drpc__request__free_unpacked
                     (Drpc__Request *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &drpc__request__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   drpc__response__init
                     (Drpc__Response         *message)
{
  static const Drpc__Response init_value = DRPC__RESPONSE__INIT;
  *message = init_value;
}
size_t drpc__response__get_packed_size
                     (const Drpc__Response *message)
{
 assert(message->base.descriptor == &drpc__response__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t drpc__response__pack
                     (const Drpc__Response *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &drpc__response__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t drpc__response__pack_to_buffer
                     (const Drpc__Response *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &drpc__response__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Drpc__Response *
       drpc__response__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Drpc__Response *)
     protobuf_c_message_unpack (&drpc__response__descriptor,
                                allocator, len, data);
}
void   drpc__response__free_unpacked
                     (Drpc__Response *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &drpc__response__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor drpc__request__field_descriptors[4] =
{
  {
    "module",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Drpc__Request, module),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "method",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Drpc__Request, method),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "sequence",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT64,
    0,   /* quantifier_offset */
    offsetof(Drpc__Request, sequence),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "body",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BYTES,
    0,   /* quantifier_offset */
    offsetof(Drpc__Request, body),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned drpc__request__field_indices_by_name[] = {
  3,   /* field[3] = body */
  1,   /* field[1] = method */
  0,   /* field[0] = module */
  2,   /* field[2] = sequence */
};
static const ProtobufCIntRange drpc__request__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor drpc__request__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "drpc.Request",
  "Request",
  "Drpc__Request",
  "drpc",
  sizeof(Drpc__Request),
  4,
  drpc__request__field_descriptors,
  drpc__request__field_indices_by_name,
  1,  drpc__request__number_ranges,
  (ProtobufCMessageInit) drpc__request__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor drpc__response__field_descriptors[3] =
{
  {
    "sequence",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT64,
    0,   /* quantifier_offset */
    offsetof(Drpc__Response, sequence),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "status",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Drpc__Response, status),
    &drpc__status__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "body",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BYTES,
    0,   /* quantifier_offset */
    offsetof(Drpc__Response, body),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned drpc__response__field_indices_by_name[] = {
  2,   /* field[2] = body */
  0,   /* field[0] = sequence */
  1,   /* field[1] = status */
};
static const ProtobufCIntRange drpc__response__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor drpc__response__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "drpc.Response",
  "Response",
  "Drpc__Response",
  "drpc",
  sizeof(Drpc__Response),
  3,
  drpc__response__field_descriptors,
  drpc__response__field_indices_by_name,
  1,  drpc__response__number_ranges,
  (ProtobufCMessageInit) drpc__response__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue drpc__status__enum_values_by_number[8] =
{
  { "SUCCESS", "DRPC__STATUS__SUCCESS", 0 },
  { "SUBMITTED", "DRPC__STATUS__SUBMITTED", 1 },
  { "FAILURE", "DRPC__STATUS__FAILURE", 2 },
  { "UNKNOWN_MODULE", "DRPC__STATUS__UNKNOWN_MODULE", 3 },
  { "UNKNOWN_METHOD", "DRPC__STATUS__UNKNOWN_METHOD", 4 },
  { "FAILED_UNMARSHAL_CALL", "DRPC__STATUS__FAILED_UNMARSHAL_CALL", 5 },
  { "FAILED_UNMARSHAL_PAYLOAD", "DRPC__STATUS__FAILED_UNMARSHAL_PAYLOAD", 6 },
  { "FAILED_MARSHAL", "DRPC__STATUS__FAILED_MARSHAL", 7 },
};
static const ProtobufCIntRange drpc__status__value_ranges[] = {
{0, 0},{0, 8}
};
static const ProtobufCEnumValueIndex drpc__status__enum_values_by_name[8] =
{
  { "FAILED_MARSHAL", 7 },
  { "FAILED_UNMARSHAL_CALL", 5 },
  { "FAILED_UNMARSHAL_PAYLOAD", 6 },
  { "FAILURE", 2 },
  { "SUBMITTED", 1 },
  { "SUCCESS", 0 },
  { "UNKNOWN_METHOD", 4 },
  { "UNKNOWN_MODULE", 3 },
};
const ProtobufCEnumDescriptor drpc__status__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "drpc.Status",
  "Status",
  "Drpc__Status",
  "drpc",
  8,
  drpc__status__enum_values_by_number,
  8,
  drpc__status__enum_values_by_name,
  1,
  drpc__status__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCMethodDescriptor drpc__drpc_service__method_descriptors[1] =
{
  { "DrpcFunc", &drpc__request__descriptor, &drpc__response__descriptor },
};
const unsigned drpc__drpc_service__method_indices_by_name[] = {
  0         /* DrpcFunc */
};
const ProtobufCServiceDescriptor drpc__drpc_service__descriptor =
{
  PROTOBUF_C__SERVICE_DESCRIPTOR_MAGIC,
  "drpc.DrpcService",
  "DrpcService",
  "Drpc__DrpcService",
  "drpc",
  1,
  drpc__drpc_service__method_descriptors,
  drpc__drpc_service__method_indices_by_name
};
void drpc__drpc_service__drpc_func(ProtobufCService *service,
                                   const Drpc__Request *input,
                                   Drpc__Response_Closure closure,
                                   void *closure_data)
{
  assert(service->descriptor == &drpc__drpc_service__descriptor);
  service->invoke(service, 0, (const ProtobufCMessage *) input, (ProtobufCClosure) closure, closure_data);
}
void drpc__drpc_service__init (Drpc__DrpcService_Service *service,
                               Drpc__DrpcService_ServiceDestroy destroy)
{
  protobuf_c_service_generated_init (&service->base,
                                     &drpc__drpc_service__descriptor,
                                     (ProtobufCServiceDestroy) destroy);
}