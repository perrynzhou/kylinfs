/*************************************************************************
    > File Name: item_object.h
  > Author:perrynzhou
  > Mail:perrynzhou@gmail.com
  > Created Time: Thu 12 May 2022 01:29:54 PM UTC
 ************************************************************************/

#ifndef _ITEM_H
#define _ITEM_H
#include <stdio.h>
#include <stdint.h>
/*
    dir:   /        1
    dir:   1/a      2
    file:  2/c.txt  {chunk_3,offset,size}
*/
typedef struct item_key
{
  size_t  size;
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
    uint32_t  size;
  } file_obj;

} item_val;
#endif
