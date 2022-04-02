// Code generated by protoc-gen-go. DO NOT EDIT.
// versions:
// 	protoc-gen-go v1.27.1
// 	protoc        v3.19.4
// source: meta.proto

package pb

import (
	protoreflect "google.golang.org/protobuf/reflect/protoreflect"
	protoimpl "google.golang.org/protobuf/runtime/protoimpl"
	reflect "reflect"
	sync "sync"
)

const (
	// Verify that this generated code is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(20 - protoimpl.MinVersion)
	// Verify that runtime/protoimpl is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(protoimpl.MaxVersion - 20)
)

type ChunkServerHealReq struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Id          string `protobuf:"bytes,1,opt,name=id,proto3" json:"id,omitempty"`
	Ip          string `protobuf:"bytes,2,opt,name=ip,proto3" json:"ip,omitempty"`
	Port        string `protobuf:"bytes,3,opt,name=port,proto3" json:"port,omitempty"`
	BlockMbSize int32  `protobuf:"varint,4,opt,name=block_mb_size,json=blockMbSize,proto3" json:"block_mb_size,omitempty"`
	TotalMbSize int64  `protobuf:"varint,5,opt,name=total_mb_size,json=totalMbSize,proto3" json:"total_mb_size,omitempty"`
	IsInit      bool   `protobuf:"varint,6,opt,name=is_init,json=isInit,proto3" json:"is_init,omitempty"`
}

func (x *ChunkServerHealReq) Reset() {
	*x = ChunkServerHealReq{}
	if protoimpl.UnsafeEnabled {
		mi := &file_meta_proto_msgTypes[0]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *ChunkServerHealReq) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*ChunkServerHealReq) ProtoMessage() {}

func (x *ChunkServerHealReq) ProtoReflect() protoreflect.Message {
	mi := &file_meta_proto_msgTypes[0]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use ChunkServerHealReq.ProtoReflect.Descriptor instead.
func (*ChunkServerHealReq) Descriptor() ([]byte, []int) {
	return file_meta_proto_rawDescGZIP(), []int{0}
}

func (x *ChunkServerHealReq) GetId() string {
	if x != nil {
		return x.Id
	}
	return ""
}

func (x *ChunkServerHealReq) GetIp() string {
	if x != nil {
		return x.Ip
	}
	return ""
}

func (x *ChunkServerHealReq) GetPort() string {
	if x != nil {
		return x.Port
	}
	return ""
}

func (x *ChunkServerHealReq) GetBlockMbSize() int32 {
	if x != nil {
		return x.BlockMbSize
	}
	return 0
}

func (x *ChunkServerHealReq) GetTotalMbSize() int64 {
	if x != nil {
		return x.TotalMbSize
	}
	return 0
}

func (x *ChunkServerHealReq) GetIsInit() bool {
	if x != nil {
		return x.IsInit
	}
	return false
}

type ChunkServerHealResp struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Code int32  `protobuf:"varint,2,opt,name=code,proto3" json:"code,omitempty"`
	Msg  string `protobuf:"bytes,3,opt,name=msg,proto3" json:"msg,omitempty"`
}

func (x *ChunkServerHealResp) Reset() {
	*x = ChunkServerHealResp{}
	if protoimpl.UnsafeEnabled {
		mi := &file_meta_proto_msgTypes[1]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *ChunkServerHealResp) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*ChunkServerHealResp) ProtoMessage() {}

func (x *ChunkServerHealResp) ProtoReflect() protoreflect.Message {
	mi := &file_meta_proto_msgTypes[1]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use ChunkServerHealResp.ProtoReflect.Descriptor instead.
func (*ChunkServerHealResp) Descriptor() ([]byte, []int) {
	return file_meta_proto_rawDescGZIP(), []int{1}
}

func (x *ChunkServerHealResp) GetCode() int32 {
	if x != nil {
		return x.Code
	}
	return 0
}

func (x *ChunkServerHealResp) GetMsg() string {
	if x != nil {
		return x.Msg
	}
	return ""
}

var File_meta_proto protoreflect.FileDescriptor

var file_meta_proto_rawDesc = []byte{
	0x0a, 0x0a, 0x6d, 0x65, 0x74, 0x61, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x12, 0x09, 0x64, 0x62,
	0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x22, 0xa9, 0x01, 0x0a, 0x12, 0x43, 0x68, 0x75, 0x6e,
	0x6b, 0x53, 0x65, 0x72, 0x76, 0x65, 0x72, 0x48, 0x65, 0x61, 0x6c, 0x52, 0x65, 0x71, 0x12, 0x0e,
	0x0a, 0x02, 0x69, 0x64, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x02, 0x69, 0x64, 0x12, 0x0e,
	0x0a, 0x02, 0x69, 0x70, 0x18, 0x02, 0x20, 0x01, 0x28, 0x09, 0x52, 0x02, 0x69, 0x70, 0x12, 0x12,
	0x0a, 0x04, 0x70, 0x6f, 0x72, 0x74, 0x18, 0x03, 0x20, 0x01, 0x28, 0x09, 0x52, 0x04, 0x70, 0x6f,
	0x72, 0x74, 0x12, 0x22, 0x0a, 0x0d, 0x62, 0x6c, 0x6f, 0x63, 0x6b, 0x5f, 0x6d, 0x62, 0x5f, 0x73,
	0x69, 0x7a, 0x65, 0x18, 0x04, 0x20, 0x01, 0x28, 0x05, 0x52, 0x0b, 0x62, 0x6c, 0x6f, 0x63, 0x6b,
	0x4d, 0x62, 0x53, 0x69, 0x7a, 0x65, 0x12, 0x22, 0x0a, 0x0d, 0x74, 0x6f, 0x74, 0x61, 0x6c, 0x5f,
	0x6d, 0x62, 0x5f, 0x73, 0x69, 0x7a, 0x65, 0x18, 0x05, 0x20, 0x01, 0x28, 0x03, 0x52, 0x0b, 0x74,
	0x6f, 0x74, 0x61, 0x6c, 0x4d, 0x62, 0x53, 0x69, 0x7a, 0x65, 0x12, 0x17, 0x0a, 0x07, 0x69, 0x73,
	0x5f, 0x69, 0x6e, 0x69, 0x74, 0x18, 0x06, 0x20, 0x01, 0x28, 0x08, 0x52, 0x06, 0x69, 0x73, 0x49,
	0x6e, 0x69, 0x74, 0x22, 0x3b, 0x0a, 0x13, 0x43, 0x68, 0x75, 0x6e, 0x6b, 0x53, 0x65, 0x72, 0x76,
	0x65, 0x72, 0x48, 0x65, 0x61, 0x6c, 0x52, 0x65, 0x73, 0x70, 0x12, 0x12, 0x0a, 0x04, 0x63, 0x6f,
	0x64, 0x65, 0x18, 0x02, 0x20, 0x01, 0x28, 0x05, 0x52, 0x04, 0x63, 0x6f, 0x64, 0x65, 0x12, 0x10,
	0x0a, 0x03, 0x6d, 0x73, 0x67, 0x18, 0x03, 0x20, 0x01, 0x28, 0x09, 0x52, 0x03, 0x6d, 0x73, 0x67,
	0x32, 0x63, 0x0a, 0x07, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x12, 0x58, 0x0a, 0x15, 0x4d,
	0x6f, 0x64, 0x69, 0x66, 0x79, 0x43, 0x68, 0x75, 0x6e, 0x6b, 0x53, 0x65, 0x72, 0x76, 0x65, 0x72,
	0x4d, 0x65, 0x74, 0x61, 0x12, 0x1d, 0x2e, 0x64, 0x62, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65,
	0x2e, 0x43, 0x68, 0x75, 0x6e, 0x6b, 0x53, 0x65, 0x72, 0x76, 0x65, 0x72, 0x48, 0x65, 0x61, 0x6c,
	0x52, 0x65, 0x71, 0x1a, 0x1e, 0x2e, 0x64, 0x62, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x2e,
	0x43, 0x68, 0x75, 0x6e, 0x6b, 0x53, 0x65, 0x72, 0x76, 0x65, 0x72, 0x48, 0x65, 0x61, 0x6c, 0x52,
	0x65, 0x73, 0x70, 0x22, 0x00, 0x42, 0x07, 0x5a, 0x05, 0x2e, 0x2e, 0x2f, 0x70, 0x62, 0x62, 0x06,
	0x70, 0x72, 0x6f, 0x74, 0x6f, 0x33,
}

var (
	file_meta_proto_rawDescOnce sync.Once
	file_meta_proto_rawDescData = file_meta_proto_rawDesc
)

func file_meta_proto_rawDescGZIP() []byte {
	file_meta_proto_rawDescOnce.Do(func() {
		file_meta_proto_rawDescData = protoimpl.X.CompressGZIP(file_meta_proto_rawDescData)
	})
	return file_meta_proto_rawDescData
}

var file_meta_proto_msgTypes = make([]protoimpl.MessageInfo, 2)
var file_meta_proto_goTypes = []interface{}{
	(*ChunkServerHealReq)(nil),  // 0: dbservice.ChunkServerHealReq
	(*ChunkServerHealResp)(nil), // 1: dbservice.ChunkServerHealResp
}
var file_meta_proto_depIdxs = []int32{
	0, // 0: dbservice.Service.ModifyChunkServerMeta:input_type -> dbservice.ChunkServerHealReq
	1, // 1: dbservice.Service.ModifyChunkServerMeta:output_type -> dbservice.ChunkServerHealResp
	1, // [1:2] is the sub-list for method output_type
	0, // [0:1] is the sub-list for method input_type
	0, // [0:0] is the sub-list for extension type_name
	0, // [0:0] is the sub-list for extension extendee
	0, // [0:0] is the sub-list for field type_name
}

func init() { file_meta_proto_init() }
func file_meta_proto_init() {
	if File_meta_proto != nil {
		return
	}
	if !protoimpl.UnsafeEnabled {
		file_meta_proto_msgTypes[0].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*ChunkServerHealReq); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_meta_proto_msgTypes[1].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*ChunkServerHealResp); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
	}
	type x struct{}
	out := protoimpl.TypeBuilder{
		File: protoimpl.DescBuilder{
			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
			RawDescriptor: file_meta_proto_rawDesc,
			NumEnums:      0,
			NumMessages:   2,
			NumExtensions: 0,
			NumServices:   1,
		},
		GoTypes:           file_meta_proto_goTypes,
		DependencyIndexes: file_meta_proto_depIdxs,
		MessageInfos:      file_meta_proto_msgTypes,
	}.Build()
	File_meta_proto = out.File
	file_meta_proto_rawDesc = nil
	file_meta_proto_goTypes = nil
	file_meta_proto_depIdxs = nil
}