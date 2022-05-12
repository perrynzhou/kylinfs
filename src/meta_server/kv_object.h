/*************************************************************************
    > File Name: kv_object.h
  > Author:perrynzhou
  > Mail:perrynzhou@gmail.com
  > Created Time: Thu 12 May 2022 01:29:54 PM UTC
 ************************************************************************/

#ifndef _KV_OBJECT_H
#define _KV_OBJECT_H

#include <stdint.h>
/*
    dir:   /        1
    dir:   1/a      2
    file:  2/c.txt  {chunk_3,offset,size}
*/
typedef struct item_key
{
  uint64_t parent_uid;
  char object_name[0];
} item_key;

typedef union item_val
{
  typedef struct dir_obj
  {
    uint64_t obj_id;
  } dir_obj;
  typedef struct file_obj
  {
    uint64_t chunk_id;
    uint64_t offset;
  } file_obj;

} item_val;
#endif
