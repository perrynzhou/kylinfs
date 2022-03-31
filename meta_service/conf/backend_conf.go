package conf

import (
	"encoding/json"
	"io/ioutil"
	"os"
)

const (
	defaultConfTemplateFile = "./conf_0.json"
)

type BackendConf struct {
	Threads int    `json:"thread_num"`
	DBName  string `json:"db_name"`
	DBPath  string `json:"db_path"`
	Port    int    `json:"server_port"`
}

func NewBackendConf(path string) (*BackendConf, error) {
	b, err := ioutil.ReadFile(path)
	if err != nil {
		return nil, err
	}
	cf := &BackendConf{}
	if err = json.Unmarshal(b, cf); err != nil {
		return nil, err
	}
	return cf, nil
}
func GenConfTemplate() error {
	cf := &BackendConf{}
	cf.Port = 50051
	cf.Threads = 2
	cf.DBPath = "/tmp"
	cf.DBName = "demo"
	b, err := json.MarshalIndent(cf, " ", " ")
	if err != nil {
		return err
	}

	return ioutil.WriteFile(defaultConfTemplateFile, b, os.ModePerm)
}
