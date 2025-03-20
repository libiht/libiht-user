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

#include "iht.h"

/* Allocator prototypes */
char *iht__strdup(const char *s);
char *iht__strndup(const char *s, size_t n);
void *iht__malloc(size_t size);
void *iht__realloc(void *ptr, size_t size);
void *iht__calloc(size_t count, size_t size);
void iht__free(void *ptr);

#endif /* _IHT_COMMON_H_ */