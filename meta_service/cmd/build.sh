go env -w GOPROXY=https://mirrors.aliyun.com/goproxy/      
export GOPROXY=https://mirrors.aliyun.com/goproxy/  
go build -o  meta_server service/meta_service.go
#go build -o  dbclient  client/client.go
#go build -o  dbench  bench/bench.go
#go build -o dbclient_thin  thin-client/client.go

#go build -o dbcli  shell/client.go