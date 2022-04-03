package service

import (
	"context"
	"errors"
	"google.golang.org/protobuf/proto"
	"kylinfs/pb"
	"kylinfs/utils"
	"time"
)

func DecodeChunkServer(req *pb.ChunkServerHealReq) *utils.ChunkServer {
	return &utils.ChunkServer{
		Id:          req.Id,
		ChunkAddr:   req.Ip,
		ChunkPort:   req.Port,
		BlockMbSize: req.BlockMbSize,
		TotalMbSize: req.TotalMbSize,
		FreeMbSize:  req.TotalMbSize,
	}
}
func CompareChunkServerCap(chunkS1, chunkS2 *utils.ChunkServer) bool {
	if chunkS1.FreeMbSize != chunkS2.FreeMbSize {
		return false
	}
	if chunkS1.TotalMbSize != chunkS2.TotalMbSize {
		return false
	}
	if chunkS1.BlockMbSize != chunkS2.BlockMbSize {
		return false
	}
	return true
}
func initSchema(db *DbService, name string) error {
	schemaReq := &pb.CreateSchemaReq{
		Name: name,
	}
	body, _ := proto.Marshal(schemaReq)
	drpcReq := &pb.Request{
		Method: DRPC_METHOD_CREATE_SCHEMA,
		Body:   body,
	}
	ctx, cancel := context.WithTimeout(context.Background(), time.Second*1000)
	defer cancel()
	_, err := db.DrpcFunc(ctx, drpcReq)
	if err != nil {
		return nil
	}
	return nil
}

func setSchemaKv(db *DbService, schemaName string, key, value string) error {
	putKvRequest := &pb.PutKvReq{
		SchemaName: schemaName,
		Key:        key,
		Value:      value,
	}
	// createRequest
	body, _ := proto.Marshal(putKvRequest)
	request := &pb.Request{
		Method: DRPC_METHOD_PUT_KV,
		Body:   body,
	}
	ctx, cancel := context.WithTimeout(context.Background(), time.Second*1000)
	defer cancel()
	response, err := db.DrpcFunc(ctx, request)
	if err != nil {
		return err
	}

	putKvResp := &pb.PutKvResp{}
	if err = proto.Unmarshal(response.Body, putKvResp); err != nil {
		return err
	}
	if putKvResp.Code != 0 {
		return errors.New(putKvResp.Msg)
	}
	//log.Info(putKvResp)
	return nil
}

/*
func modifyChunkServerMeta(db *DbService, req *pb.Request) error {
	schemaReq := &pb.CreateSchemaReq{
		Name: name,
	}
	body, _ := proto.Marshal(schemaReq)
	drpcReq := &pb.Request{
		Method: DRPC_METHOD_CREATE_SCHEMA,
		Body:   body,
	}
	ctx, cancel := context.WithTimeout(context.Background(), time.Second*1000)
	defer cancel()
	_, err := db.DrpcFunc(ctx, drpcReq)
	if err != nil {
		return nil
	}
	return nil
}

*/
