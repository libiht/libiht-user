////////////////////////////////////////////////////////////////////////////////
//
//  File          : include/iht.h
//  Description   : This is the header file for Intel Hardware Trace library
//                  (LibIHT) that provides the interface to the kernel component
//                  that manages the hardware trace capabilities of the Intel
//                  processors.
//
//   Author : Thomason Zhao
//

#ifndef _IHT_H_
#define _IHT_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BUILDING_IHT_SHARED) && defined(USING_IHT_SHARED)
#error "Either BUILDING_IHT_SHARED or USING_IHT_SHARED can be defined"
#endif

#ifndef IHT_EXTERN
#ifdef _WIN32
/* Windows - set up dll import/export decorators. */
#ifdef BUILDING_IHT_SHARED
/* Building shared library. */
#define IHT_EXTERN __declspec(dllexport)
#else
/* Using shared library. */
#define IHT_EXTERN __declspec(dllimport)
#endif /* BUILDING_IHT_SHARED */
#else
/* Linux - set up equivalent for visibility. */
#define IHT_EXTERN __attribute__((visibility("default")))
#endif /* _WIN32 */
#endif /* IHT_EXTERN */

#include "iht/errno.h"
#include "iht/version.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32)
#include "iht/win.h"
#else
#include "iht/linux.h"
#endif

typedef void* (*iht_malloc_func)(size_t size);
typedef void* (*iht_realloc_func)(void* ptr, size_t size);
typedef void* (*iht_calloc_func)(size_t count, size_t size);
typedef void (*iht_free_func)(void* ptr);

// TODO: IHT types and structures

// IHT API functions

IHT_EXTERN int iht_set_allocator(iht_malloc_func malloc_func,
                                 iht_realloc_func realloc_func,
                                 iht_calloc_func calloc_func,
                                 iht_free_func free_func);

// TODO: LBR (Last Branch Record) API
IHT_EXTERN int iht_lbr_init(void);
IHT_EXTERN int iht_lbr_start(void);
IHT_EXTERN int iht_lbr_stop(void);
IHT_EXTERN int iht_lbr_dump(void);
IHT_EXTERN int iht_lbr_config(void);

// TODO: BTS (Branch Trace Store) API
IHT_EXTERN int iht_bts_init(void);
IHT_EXTERN int iht_bts_start(void);
IHT_EXTERN int iht_bts_stop(void);
IHT_EXTERN int iht_bts_dump(void);
IHT_EXTERN int iht_bts_config(void);

#ifdef __cplusplus
}
#endif

#endif /* _IHT_H_ */