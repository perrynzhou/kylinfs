package main

import (
	"flag"
	"fmt"
	"kylinfs/meta_service/conf"
	"kylinfs/meta_service/drpc/dbservice"
	"kylinfs/meta_service/drpc/pb"
	"kylinfs/meta_service/util"
	"net"
	"os"
	"os/signal"
	"syscall"

	log "github.com/sirupsen/logrus"
	"google.golang.org/grpc"
)

const (
	defaultConfFile = "./conf.json"
)

var (
	confFile = flag.String("c", defaultConfFile, "The server port")
)

func init() {
	logHook := util.NewHook()
	logHook.Field = "line"
	log.AddHook(logHook)
	conf.GenConfTemplate()
}

func main() {
	flag.Parse()
	cf, err := conf.NewBackendConf(*confFile)
	if err != nil {
		return
	}

	sigs := make(chan os.Signal, 1)
	signal.Notify(sigs, os.Interrupt, syscall.SIGTERM, syscall.SIGINT)

	lis, err := net.Listen("tcp", fmt.Sprintf(":%d", cf.Port))
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}
	s := grpc.NewServer()

	confService := dbservice.NewDbService(cf.Threads)
	pb.RegisterDrpcServiceServer(s, confService)
	log.Printf("server listening at %v", lis.Addr())
	go func() {
		if err := s.Serve(lis); err != nil {
			log.Fatalf("failed to serve: %v", err)
		}
	}()

	for {
		select {
		case <-sigs:
			log.Info("stop meta server....")
			return
		}
	}
}
