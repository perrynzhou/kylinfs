//
// (C) Copyright 2019-2021 Intel Corporation.
//
// SPDX-License-Identifier: BSD-2-Clause-Patent
//

package utils

import (
	"errors"
	"kylinfs/pb"
	"net"
	"sync"

	log "github.com/sirupsen/logrus"
	"google.golang.org/protobuf/proto"
)

const (
	MaxMsgSize = 1 << 17
)

// DomainSocketClient is the interface to a dRPC client communicating over a
// Unix Domain Socket
type DomainSocketClient interface {
	sync.Locker
	IsConnected() bool
	Connect() error
	Close() error
}

// ClientConnection represents a client connection to a dRPC server
type ClientConnection struct {
	sync.Mutex
	socketPath string        // Filesystem location of dRPC socket
	addr       *net.UnixAddr // Interface to connect to the socket
	conn       net.Conn      // Connection to socket
	sequence   int64         // Increment each time we send
}

// IsConnected indicates whether the client connection is currently active
func (c *ClientConnection) IsConnected() bool {
	return c.conn != nil
}

func (c *ClientConnection) sendCall(msg *pb.Request) error {
	// increment sequence every call, always nonzero
	c.sequence++
	msg.Sequence = c.sequence

	callBytes, err := proto.Marshal(msg)
	if err != nil {
		return err
	}

	if _, err := c.conn.Write(callBytes); err != nil {
		return err
	}

	return nil
}

func (c *ClientConnection) recvResponse() (*pb.Response, error) {
	respBytes := make([]byte, MaxMsgSize)
	numBytes, err := c.conn.Read(respBytes)
	if err != nil {
		return nil, err
	}

	resp := &pb.Response{}
	err = proto.Unmarshal(respBytes[:numBytes], resp)
	if err != nil {
		return nil, err
	}

	return resp, nil
}

// SendMsg sends a message to the connected dRPC server, and returns the
// response to the caller.
func (c *ClientConnection) SendMsg(msg *pb.Request) (*pb.Response, error) {
	if !c.IsConnected() {
		return nil, errors.New("dRPC not connected")
	}

	if msg == nil {
		return nil, errors.New("invalid dRPC call")
	}

	err := c.sendCall(msg)
	if err != nil {
		return nil, err
	}

	return c.recvResponse()
}

// Connect opens a connection to the internal Unix Domain Socket path
func (c *ClientConnection) Connect() error {
	if c.IsConnected() {
		// Nothing to do
		return nil
	}

	conn, err := net.DialUnix("unixpacket", nil, c.addr)
	if err != nil {
		log.Error("happed error:", err)
		return errors.New("dRPC connect")
	}
	c.conn = conn
	return nil
}

// Close shuts down the connection to the Unix Domain Socket
func (c *ClientConnection) Close() error {
	if !c.IsConnected() {
		// Nothing to do
		return nil
	}

	err := c.conn.Close()
	if err != nil {
		return err
	}

	return nil
}

// GetSocketPath returns client dRPC socket file path.
func (c *ClientConnection) GetSocketPath() string {
	return c.socketPath
}

// NewClientConnection creates a new dRPC client
func NewClientConnection(socket string) *ClientConnection {

	addr := &net.UnixAddr{
		//Net:  "unixpacket",
		Net:  "unix",
		Name: socket,
	}

	return &ClientConnection{
		socketPath: socket,
		addr:       addr,
		conn:       nil,
	}
}

func (c *ClientConnection) IssueCall(call *pb.Request) (*pb.Response, error) {

	resp, err := c.SendMsg(call)
	if err != nil {
		return nil, err
	}
	return resp, nil
}

/*
func (c *ClientConnection) IssueCall_Template() error {
	reqCall := pb.Request{}
	// requestCall.Method = 传递方法名称
	// requestCall.Body = 具体rpc服务的请求
	// requestCall.Module =请求的模块

	reqCall.Method = 201
	reqJoinNodeReq := pb.JoinNodeReq{
		Hosts:  "127.0.0.1",
		Port:   rand.Int31n(6000),
		Weight: rand.Int31n(10),
		State:  "new",
	}
	callBytes, err := proto.Marshal(&reqJoinNodeReq)
	if err != nil {
		return err
	}
	reqCall.Body = callBytes
	rspCall, err := c.SendMsg(&reqCall)
	if err != nil {
		return err
	}
	resp := &pb.JoinNodeResp{}

	if err := proto.Unmarshal(rspCall.Body, resp); err != nil {
		return err
	}
	respBytes, err := json.Marshal(resp)
	if err != nil {
		return err
	}
	log.Info("resp=", string(respBytes))
	return nil
}

func main() {
	flag.Parse()
	sigs := make(chan os.Signal, 1)

	signal.Notify(sigs, os.Interrupt, syscall.SIGTERM, syscall.SIGINT)

	c := NewClientConnection(*sockFile)
	c.Connect()
	tickerIntervalSecond := *timerSecond
	ticker := time.NewTicker(time.Second * tickerIntervalSecond)

	defer ticker.Stop()
MainExit:
	for {
		select {
		case <-ticker.C:
			log.Info(c.IssueCall())
			log.Info(".....sleep 3.....")
		case <-sigs:
			log.Info("stop kiwi_manager server....")
			break MainExit
		}

	}

}
*/
