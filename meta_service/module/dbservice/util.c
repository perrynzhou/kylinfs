/*************************************************************************
  > File Name: util.c
  > Author:perrynzhou 
  > Mail:perrynzhou@gmail.com 
  > Created Time: Thu 30 Dec 2021 04:52:50 PM CST
 ************************************************************************/

#include "util.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>
static const char *const hex = "0123456789abcdef";

int set_process_open_file_limit() 
{
  struct rlimit max_file_limit = {999999,1000000};
  return setrlimit(RLIMIT_NOFILE, &max_file_limit);
}
int setnonblock(int fd)
{
    int flags;

    flags = fcntl(fd, F_GETFL);
    flags |= O_NONBLOCK;
    return fcntl(fd, F_SETFL, flags);
}
char *safe_utoa(int _base, uint64_t val, char *buf)
{
  uint32_t base = (uint32_t)_base;
  *buf-- = 0;
  do
  {
    *buf-- = hex[val % base];
  } while ((val /= base) != 0);
  return buf + 1;
}

char *safe_itoa(int base, int64_t val, char *buf)
{
  char *orig_buf = buf;
  const int32_t is_neg = (val < 0);
  *buf-- = 0;

  if (is_neg)
  {
    val = -val;
  }
  if (is_neg && base == 16)
  {
    int ix;
    val -= 1;
    for (ix = 0; ix < 16; ++ix)
      buf[-ix] = '0';
  }

  do
  {
    *buf-- = hex[val % base];
  } while ((val /= base) != 0);

  if (is_neg && base == 10)
  {
    *buf-- = '-';
  }

  if (is_neg && base == 16)
  {
    int ix;
    buf = orig_buf - 1;
    for (ix = 0; ix < 16; ++ix, --buf)
    {
      /* *INDENT-OFF* */
      switch (*buf)
      {
      case '0':
        *buf = 'f';
        break;
      case '1':
        *buf = 'e';
        break;
      case '2':
        *buf = 'd';
        break;
      case '3':
        *buf = 'c';
        break;
      case '4':
        *buf = 'b';
        break;
      case '5':
        *buf = 'a';
        break;
      case '6':
        *buf = '9';
        break;
      case '7':
        *buf = '8';
        break;
      case '8':
        *buf = '7';
        break;
      case '9':
        *buf = '6';
        break;
      case 'a':
        *buf = '5';
        break;
      case 'b':
        *buf = '4';
        break;
      case 'c':
        *buf = '3';
        break;
      case 'd':
        *buf = '2';
        break;
      case 'e':
        *buf = '1';
        break;
      case 'f':
        *buf = '0';
        break;
      }
    }
  }
  return buf + 1;
}

uint8_t *
safe_strchr(uint8_t *p, uint8_t *last, uint8_t c)
{
    while (p < last) {
        if (*p == c) {
            return p;
        }
        p++;
    }

    return NULL;
}

uint8_t *safe_strrchr(uint8_t *p, uint8_t *start, uint8_t c)
{
    while (p >= start) {
        if (*p == c) {
            return p;
        }
        p--;
    }

    return NULL;
}