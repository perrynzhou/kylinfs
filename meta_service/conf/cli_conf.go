package conf

import (
	"encoding/json"
	"io/ioutil"
)


type CliConf struct {
	BackendAddr string `json:"backend_addr"`
	BackendPort int    `json:"backend_port"`
}

func NewCliConf(path string) (*CliConf, error) {
	cliConf := &CliConf{}
	b, err := ioutil.ReadFile(path)
	if err != nil {
		return nil, err
	}
	if err = json.Unmarshal(b, cliConf); err != nil {
		return nil, err
	}
	return cliConf, nil
}
