////////////////////////////////////////////////////////////////////////////////
//
//  File          : src/iht-common.h
//  Description   : Common functions used across both windows and linux
//                  platforms.
//
//   Author : Thomason Zhao
//

#ifndef _IHT_COMMON_H_
#define _IHT_COMMON_H_
#pragma once

#include "iht-ioctl.h"
#include "iht.h"

/* Allocator prototypes */
char *iht__strdup(const char *s);
char *iht__strndup(const char *s, size_t n);
void *iht__malloc(size_t size);
void *iht__realloc(void *ptr, size_t size);
void *iht__calloc(size_t count, size_t size);
void iht__free(void *ptr);

int iht__ioctl_init(void);
int iht__ioctl_close(void);
int iht__ioctl(xioctl_request_t *req);

int iht__lbr_dump(iht_trace_t *trace);
int iht__bts_dump(iht_trace_t *trace);

#endif /* _IHT_COMMON_H_ */