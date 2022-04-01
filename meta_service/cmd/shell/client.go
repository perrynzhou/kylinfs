package main

import (
	"context"
	"fmt"
	log "github.com/sirupsen/logrus"
	"github.com/urfave/cli"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
	"google.golang.org/protobuf/proto"
	"kylinfs/meta_service/conf"
	"kylinfs/pb"
	"os"
	"time"
)

const (
	DRPC_METHOD_CREATE_SCHEMA = 201
	DRPC_METHOD_DROP_SCHEMA   = 202
	DRPC_METHOD_QUERY_SCHEMA  = 203

	DRPC_METHOD_PUT_KV = 301
	DRPC_METHOD_GET_KV = 302
	DRPC_METHOD_DEL_KV = 303
)

const (
	defaultCliConfFile = "./.cli_conf.json"
)

func querySchmea(c pb.DrpcServiceClient, ctx context.Context, schemaName string) (*pb.QuerySchemaResp, error) {
	queryRequest := &pb.QuerySchemaReq{
		Name: schemaName,
	}
	// createRequest
	body, _ := proto.Marshal(queryRequest)
	request := &pb.Request{
		Method: DRPC_METHOD_QUERY_SCHEMA,
		Body:   body,
	}
	response, err := c.DrpcFunc(ctx, request)
	if err != nil {
		return nil, err
	}
	queryResp := &pb.QuerySchemaResp{}

	if err := proto.Unmarshal(response.Body, queryResp); err != nil {
		return nil, err
	}
	return queryResp, nil
}
func createSchmea(c pb.DrpcServiceClient, ctx context.Context, schemaName string) (*pb.CreateSchemaResp, error) {

	createRequest := &pb.CreateSchemaReq{
		Name: schemaName,
	}
	// createRequest
	body, _ := proto.Marshal(createRequest)
	request := &pb.Request{
		Method: DRPC_METHOD_CREATE_SCHEMA,
		Body:   body,
	}
	response, err := c.DrpcFunc(ctx, request)
	if err != nil {
		return nil, err
	}
	createResp := &pb.CreateSchemaResp{}
	if err = proto.Unmarshal(response.Body, createResp); err != nil {
		return nil, err
	}
	// log.Info(createResp)
	return createResp, nil
}
func dropSchmea(c pb.DrpcServiceClient, ctx context.Context, schemaName string) (*pb.DropSchemaResp, error) {
	dropRequest := &pb.DropSchemaReq{
		Name: schemaName,
	}
	// createRequest
	body, _ := proto.Marshal(dropRequest)
	request := &pb.Request{
		Method: DRPC_METHOD_DROP_SCHEMA,
		Body:   body,
	}
	response, err := c.DrpcFunc(ctx, request)
	if err != nil {
		log.Fatalf("could call DrpcFunc: %v", err)
	}
	dropResp := &pb.DropSchemaResp{}
	if err = proto.Unmarshal(response.Body, dropResp); err != nil {
		return nil, err
	}
	//log.Info(dropResp)
	return dropResp, nil
}
func putKv(c pb.DrpcServiceClient, ctx context.Context, schemaName, key, value string) (*pb.PutKvResp, error) {

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
	response, err := c.DrpcFunc(ctx, request)
	if err != nil {
		return nil, err
	}
	putKvResp := &pb.PutKvResp{}
	if err = proto.Unmarshal(response.Body, putKvResp); err != nil {
		return nil, err
	}
	//log.Info(putKvResp)
	return putKvResp, nil
}
func getKv(c pb.DrpcServiceClient, ctx context.Context, schemaName, key string) (*pb.GetKvResp, error) {

	getKvRequest := &pb.GetKvReq{
		SchemaName: schemaName,
		Key:        key,
	}
	// createRequest
	body, _ := proto.Marshal(getKvRequest)
	request := &pb.Request{
		Method: DRPC_METHOD_GET_KV,
		Body:   body,
	}
	response, err := c.DrpcFunc(ctx, request)
	if err != nil {
		return nil, err
	}
	getKvResp := &pb.GetKvResp{}
	if err = proto.Unmarshal(response.Body, getKvResp); err != nil {
		return nil, err
	}
	//log.Info(getKvResp)
	return getKvResp, nil
}
func delKv(c pb.DrpcServiceClient, ctx context.Context, schemaName, key string) (*pb.DelKvResp, error) {

	delKvRequest := &pb.DelKvReq{
		SchemaName: schemaName,
		Key:        key,
	}
	// createRequest
	body, _ := proto.Marshal(delKvRequest)
	request := &pb.Request{
		Method: DRPC_METHOD_DEL_KV,
		Body:   body,
	}
	response, err := c.DrpcFunc(ctx, request)
	if err != nil {
		return nil, err
	}
	delKvResp := &pb.DelKvResp{}
	if err = proto.Unmarshal(response.Body, delKvResp); err != nil {
		return nil, err
	}
	return delKvResp, nil
}

func main() {

	cliConf, err := conf.NewCliConf(defaultCliConfFile)
	if err != nil {
		log.Fatal(err)
	}
	conn, err := grpc.Dial(fmt.Sprintf("%s:%d", cliConf.BackendAddr, cliConf.BackendPort), grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		log.Fatalf("did not connect: %v", err)
	}
	defer conn.Close()
	rpcClient := pb.NewDrpcServiceClient(conn)

	// Contact the server and print out its response.
	ctx, cancel := context.WithTimeout(context.Background(), time.Second*1000)
	defer cancel()
	app := cli.NewApp()
	app.Commands = []cli.Command{
		{
			Name:     "schema",
			Usage:    "options for fundb schmea opetaion",
			Category: "schema",
			Subcommands: []cli.Command{
				{
					Name:  "add",
					Usage: "schema add {schema_name}",
					Action: func(c *cli.Context) error {
						resp, err := createSchmea(rpcClient, ctx, c.Args().First())
						if err != nil {
							log.Error(err)
							return err
						}
						log.Info(resp)
						return nil
					},
				},
				{
					Name:  "del",
					Usage: "schema del {schema_name}",
					Action: func(c *cli.Context) error {
						resp, err := dropSchmea(rpcClient, ctx, c.Args().First())
						if err != nil {
							log.Error(err)
							return err
						}
						log.Info(resp)
						return nil
					},
				},
				{
					Name:  "fetch",
					Usage: "schema fetch {schema_name}",
					Action: func(c *cli.Context) error {
						resp, err := querySchmea(rpcClient, ctx, c.Args().First())
						if err != nil {
							log.Error(err)
							return err
						}
						log.Info(resp)
						return nil
					},
				},
			},
		},

		{
			Name:     "kv",
			Aliases:  []string{"t", "tmpl"},
			Usage:    "options for task templates",
			Category: "kv",
			Subcommands: []cli.Command{
				{
					Name:  "add",
					Usage: "kv add {schema_name} {key} {value}",
					Action: func(c *cli.Context) error {
						schmeaName := c.Args().Get(0)
						Key := c.Args().Get(1)
						Value := c.Args().Get(2)
						resp, err := putKv(rpcClient, ctx, schmeaName, Key, Value)
						if err != nil {
							log.Error(err)
							return err
						}
						log.Info(resp)
						return nil
					},
				},
				{
					Name:  "del",
					Usage: "kv del {schema_name} {key}",
					Action: func(c *cli.Context) error {
						schmeaName := c.Args().Get(0)
						Key := c.Args().Get(1)
						resp, err := delKv(rpcClient, ctx, schmeaName, Key)
						if err != nil {
							log.Error(err)
							return err
						}
						log.Info(resp)
						return nil

					},
				},
				{
					Name:  "get",
					Usage: "kv get {schema_name} {key}",
					Action: func(c *cli.Context) error {
						schmeaName := c.Args().Get(0)
						Key := c.Args().Get(1)
						resp, err := getKv(rpcClient, ctx, schmeaName, Key)
						if err != nil {
							log.Error(err)
							return err
						}
						log.Info(resp)
						return nil
					},
				},
			},
		},
	}

	app.Name = "dbcli"
	app.Usage = ""
	app.Description = "fundb_cli for fundbserver"
	app.Version = "v1.0.1"
	err = app.Run(os.Args)
	if err != nil {
		log.Fatal(err)
	}
}
