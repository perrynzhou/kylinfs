all:
	rm -rf test*
	gcc -g -std=gnu11  -w -O0 ../drpc/drpc.pb-c.h ../drpc/drpc.pb-c.c ../drpc/drpc.h ../drpc/drpc.c \
	 hashfn.h hashfn.c dict.h dict.c kv_db.h kv_db.c  dbservice.pb-c.h dbservice.pb-c.c \
	log.h log.c util.h util.c dbservice_help.h dbservice_help.c  dbservice.h dbservice.c  schmea_meta.h schmea_meta.c conf.h conf.c server.h server.c main.c -o engine -lwiredtiger -lprotobuf-c -lev -lpthread -ljansson

