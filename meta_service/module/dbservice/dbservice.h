/*************************************************************************
  > File Name: dbservice.h
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: 二  3/ 8 11:10:56 2022
 ************************************************************************/

#ifndef _DBSERVICE_H
#define _DBSERVICE_H
#include <stdio.h>
#include <stdbool.h>
#include "../drpc/drpc.pb-c.h"
#include "../drpc/drpc.h"
#include "log.h"
void process_drpc_request(Drpc__Request *drpc_req, Drpc__Response *drpc_resp,void *ctx);

 static struct drpc_handler dbservice_drpc_handlers[] = {
    {.module_id = 0,
     .handler = process_drpc_request}};
#endif
