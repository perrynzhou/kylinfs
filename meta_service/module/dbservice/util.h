/*************************************************************************
  > File Name: util.h
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Thu 30 Dec 2021 04:52:45 PM CST
 ************************************************************************/

#ifndef _UTIL_H
#define _UTIL_H
#include <stdint.h>
int setnonblock(int fd);
char *safe_itoa(int base, int64_t val, char *buf);
char *safe_utoa(int _base, uint64_t val, char *buf);
uint8_t *safe_strrchr(uint8_t *p, uint8_t *start, uint8_t c);
uint8_t *safe_strchr(uint8_t *p, uint8_t *last, uint8_t c);
int set_process_open_file_limit();
#endif
