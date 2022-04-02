package service

import (
	"context"
	"errors"
	"google.golang.org/protobuf/proto"
	"kylinfs/pb"
	"kylinfs/utils"
)

const (
	DRPC_METHOD_HEAL_MODIFY = 401
)

type MetaService struct {
	DB           *DbService
	chunkServers map[string]*utils.ChunkServer
}

func NewMetaService(DB *DbService) (*MetaService, error) {
	if DB != nil {
		return &MetaService{
			DB:           DB,
			chunkServers: make(map[string]*utils.ChunkServer),
		}, nil
	}
	return nil, errors.New("db context is nil")
}

// func (cs *DbService) DrpcFunc(ctx context.Context, Req *pb.Request) (*pb.Response, error) {
func (h *MetaService) ModifyChunkServerMeta(ctx context.Context, req *pb.ChunkServerHealReq) (*pb.ChunkServerHealResp, error) {
	body, err := proto.Marshal(req)
	if err != nil {
		return nil, err
	}
	if _, ok := h.chunkServers[req.Ip]; !ok {
		h.chunkServers[req.Id] = &utils.ChunkServer{
			Id:          req.Id,
			ChunkAddr:   req.Ip,
			ChunkPort:   req.Port,
			BlockMbSize: int(req.BlockMbSize),
			TotalMbSize: uint64(req.TotalMbSize),
			FreeMbSize:  uint64(req.TotalMbSize),
		}
	} else {
		h.chunkServers[req.Id].Id = req.Id
		h.chunkServers[req.Id].ChunkAddr = req.Ip
		h.chunkServers[req.Id].ChunkPort = req.Port
		h.chunkServers[req.Id].BlockMbSize = int(req.BlockMbSize)
		h.chunkServers[req.Id].TotalMbSize = uint64(req.TotalMbSize)
		h.chunkServers[req.Id].FreeMbSize = uint64(req.TotalMbSize)
	}
	request := &pb.Request{
		Body:   body,
		Method: DRPC_METHOD_HEAL_MODIFY,
	}
	h.DB.DrpcFunc(ctx, request)
	return nil, nil
}
