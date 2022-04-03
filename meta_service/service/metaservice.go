package service

import (
	"context"
	"encoding/json"
	"errors"
	"google.golang.org/protobuf/proto"
	"kylinfs/pb"
	"kylinfs/utils"
)

const (
	defaultChunkServerSchema    = "chunk_server_meta"
	defaultChunkServerBlkSchema = "chunk_server_blk_meta"
)

type MetaService struct {
	DB                   *DbService
	chunkServers         map[string]*utils.ChunkServer
	chunkBlkInfo         map[string]*utils.ChunkBlkInfo
	chunkServerSchema    string
	chunkServerBlkSchema string
}

func NewMetaService(DB *DbService) (*MetaService, error) {

	if DB != nil {
		if err := initSchema(DB, defaultChunkServerSchema); err != nil {
			return nil, err
		}
		if err := initSchema(DB, defaultChunkServerBlkSchema); err != nil {
			return nil, err
		}
		return &MetaService{
			DB:                   DB,
			chunkServers:         make(map[string]*utils.ChunkServer),
			chunkBlkInfo:         make(map[string]*utils.ChunkBlkInfo),
			chunkServerSchema:    defaultChunkServerSchema,
			chunkServerBlkSchema: defaultChunkServerBlkSchema,
		}, nil
	}
	return nil, errors.New("db context is nil")
}

// func (cs *DbService) DrpcFunc(ctx context.Context, Req *pb.Request) (*pb.Response, error) {
func (metaService *MetaService) ModifyChunkServerMeta(ctx context.Context, req *pb.ChunkServerHealReq) (*pb.ChunkServerHealResp, error) {
	body, err := proto.Marshal(req)
	if err != nil {
		return nil, err
	}
	chunkS1 := DecodeChunkServer(req)
	blkCount := req.TotalMbSize / req.BlockMbSize
	req.IsInit = false
	var targetChunkServer *utils.ChunkServer
	if _, ok := metaService.chunkServers[req.Ip]; !ok {
		req.IsInit = true
		metaService.chunkServers[req.Id] = chunkS1
		chunkBlkInfo := &utils.ChunkBlkInfo{
			ServerId: req.Id,
			BlkInfo:  make(map[uint64]*utils.ChunkBlkMeta),
			BlkVec:   make([]*utils.ChunkBlkMeta, 0),
		}
		metaService.chunkBlkInfo[req.Id] = chunkBlkInfo
		var i uint64
		for i = 0; i < uint64(blkCount); i++ {
			chunkBlkMeta := &utils.ChunkBlkMeta{
				BlkId:   i,
				BlkSize: req.BlockMbSize,
			}
			chunkBlkInfo.BlkVec = append(chunkBlkInfo.BlkVec, chunkBlkMeta)
			chunkBlkInfo.BlkInfo[i] = chunkBlkMeta
		}
	} else {
		targetChunkServer = metaService.chunkServers[req.Id]
		if CompareChunkServerCap(chunkS1, targetChunkServer) {
			return &pb.ChunkServerHealResp{Code: 0, Msg: "succ"}, nil
		}
	}
	body, err = json.Marshal(targetChunkServer)
	if err != nil {
		return &pb.ChunkServerHealResp{Code: -1, Msg: err.Error()}, err
	}
	if err := setSchemaKv(metaService.DB, metaService.chunkServerSchema, req.Id, string(body)); err != nil {
		return &pb.ChunkServerHealResp{Code: -1, Msg: err.Error()}, err
	}
	return &pb.ChunkServerHealResp{Code: 0, Msg: err.Error()}, err
}
