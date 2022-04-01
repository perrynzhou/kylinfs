package service

import (
	"errors"
	"sync"
)

const (
	drpcHeartBeatSockName = "heart_beat_drpc"
)
const (
	DRPC_METHOD_HEARTBEAT_SCHEMA = 401
)

type HealService struct {
	DB *DbService
	wg *sync.WaitGroup
}

func NewHealService(DB *DbService) (*HealService, error) {
	if DB != nil {
		return &HealService{DB, &sync.WaitGroup{}}, nil
	}
	return nil, errors.New("db context is nil")
}

// func (cs *DbService) DrpcFunc(ctx context.Context, Req *pb.Request) (*pb.Response, error) {
func (h *HealService) HealFunc(ctx context.Context, req *pb.ChunkServerHealReq) (*pb.ChunkServerHealResp, error) {
	return nil, nil
}
