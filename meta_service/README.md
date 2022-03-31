## kylinfs/meta_service设计与实现


### kylinfs/meta_service 设计
- kylinfs/meta_service的实现是基于wiretiger，目前设计采用主从架构。参考了部分daos的框架代码，服务端上层采用go语言开发，数据库服务层是采用c来写。`fundb`是`just for fun`的意思。设计的主要目的是提供kv的服务，灵活的操作kv数据库。目前完成了`dbservice`的服务，包括`create schema/delete schema/query schema meta/set kv/get kv/del kv`的功能。如果想要存储服务的配置服务，可以基于这个二次开发。

- 如果是kylinfs/meta_service的架构，所有来自客户端的请求都路由到go服务端的grpc服务，然后采用多线程和本地套接字的方式的转发到`dbservice`层，请求由`dbservice`处理完成后在给go的服务层，最终转发给客户端。

![](./doc/kylinfs/meta_service-design.png)

### wiretiger 编译和安装

```
$ wget https://github.com/wiredtiger/wiredtiger/archive/refs/tags/10.0.0.tar.gz
$ tar zxvf 10.0.0.tar.gz && cd wiredtiger-10.0.0/
$ env CFLAGS="-ggdb3 -O0" ./configure 

$ make CFLAGS="-ggdb3 -O0" && make install
```
### 编译drpc服务端和客户端

```
$ git clone git@github.com:perrynzhou/kylinfs/meta_service.git
$ cd kylinfs/meta_service/ && ./build.sh

```

### 编译存储enngine服务

```
$ cd kylinfs/meta_service/module/dbservice && ./build.sh
// demo 是配置服务的存储服务，/tmp是数据库存储路径,4代表线程数
$ ./engine conf.json
```

### 启动dbserver服务

```
// 启动kv 的存储服务，接受哦来自drpc服务端的请求
$ cd cmd && dbserver -c conf.json
```
### 客户端请求示例
```
// 请求创建创建schema
$ cd cmd && dbclient -n 3
//删除schema
$ ./dbclient  -t drop_schema -n 10
// put kv
$ dbclient -t put_kv -n 3
// get kv
$ dbclient -t get_kv -n 3

```
## kylinfs/meta_service项目进度
![](./doc/kylinfs/meta_service.png)