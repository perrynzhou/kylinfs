package conf

import (
	"encoding/json"
	"io/ioutil"
)

type ChunkServerConf struct {
	MetaServerAddr          string `json:"meta_server_add"`
	BlockSize               int    `json:"block_mb_size"`
	Port                    int    `json:"port"`
	KeepHeartBeatMillSecond int    `json:"keep_heartbeat_millseconds"`
}

func NewChunkServerConf(path string) (*ChunkServerConf, error) {
	b, err := ioutil.ReadFile(path)
	if err != nil {
		return nil, err
	}
	serverConf := &ChunkServerConf{}
	if err = json.Unmarshal(b, serverConf); err != nil {
		return nil, err
	}
	return nil, err
}
