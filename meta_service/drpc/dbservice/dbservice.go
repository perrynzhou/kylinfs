package dbservice

import (
	"context"
	"errors"
	"fmt"
	"kylinfs/meta_service/drpc/pb"
	"sync/atomic"

	log "github.com/sirupsen/logrus"
)

const (
	drpcSockName = "drpc"
)
const (
	DRPC_METHOD_CREATE_SCHEMA = 201
	DRPC_METHOD_DROP_SCHEMA   = 202
	DRPC_METHOD_QUERY_SCHEMA  = 203

	DRPC_METHOD_PUT_KV = 301
	DRPC_METHOD_GET_KV = 302
	DRPC_METHOD_DEL_KV = 303
)

var (
	opMap = map[int]string{
		DRPC_METHOD_CREATE_SCHEMA: "create_schema",
		DRPC_METHOD_DROP_SCHEMA:   "drop_schema",
		DRPC_METHOD_QUERY_SCHEMA:  "query_schema",
		DRPC_METHOD_PUT_KV:        "put_kv",
		DRPC_METHOD_GET_KV:        "get_kv",
		DRPC_METHOD_DEL_KV:        "del_kv",
	}
)

type DbService struct {
	pb.UnimplementedDrpcServiceServer
	drpcSockets []string
	count       uint64
}

func NewDbService(threadNum int) *DbService {
	dbService := &DbService{
		drpcSockets: make([]string, 0),
	}
	for i := 0; i < threadNum; i++ {
		drpcSocket := fmt.Sprintf("/tmp/%s_%d.sock", drpcSockName, i)
		dbService.drpcSockets = append(dbService.drpcSockets, drpcSocket)
		log.Info("run sock:", drpcSocket)
	}
	return dbService
}

func (cs *DbService) DrpcFunc(ctx context.Context, Req *pb.Request) (*pb.Response, error) {

	index := int(cs.count % uint64(len(cs.drpcSockets)))
	atomic.AddUint64(&cs.count, 1)
	c := NewClientConnection(cs.drpcSockets[index])
	if c == nil {
		return &pb.Response{}, errors.New("init connection failed")
	}
	if err := c.Connect(); err != nil {
		return &pb.Response{}, err

	}
	defer c.Close()
	log.Info("********recv request*******")
	log.Info("request method=", Req.Method, " op=", opMap[int(Req.Method)], ",socket=", cs.drpcSockets[index])
	response, err := c.IssueCall(Req)

	if err != nil {
		response = &pb.Response{
			Body: []byte(err.Error()),
		}
	}
	return response, err
}
