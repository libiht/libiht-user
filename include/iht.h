////////////////////////////////////////////////////////////////////////////////
//
//  File          : include/iht.h
//  Description   : This is the header file for Intel Hardware Trace library
//                  (LibIHT) that provides the interface to the kernel component
//                  that manages the hardware trace capabilities of the Intel
//                  processors.
//
//   Author : Thomason Zhao, Uzen Huang
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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "iht/errno.h"
#include "iht/version.h"

#if defined(_WIN32)
#include "iht/win.h"
#else
#include "iht/linux.h"
#endif

typedef enum {
    IHT_TRACE_STATE_UNINIT = 0,
    IHT_TRACE_STATE_LBR, /* Last Branch Record tracing */
    IHT_TRACE_STATE_BTS, /* Branch Trace Store tracing */
} iht_trace_state_t;

typedef struct iht_trace_s iht_trace_t;
typedef struct iht_data_entry_s iht_data_entry_t;

struct iht_trace_s {
    pid_t pid;
    iht_trace_state_t state;

    union {
        struct {
            uint64_t lbr_filters;
        };
        struct {
            uint64_t bts_filters;
            uint64_t bts_buffer_size;
        };
    } config;

    size_t data_size;
    iht_data_entry_t* data;
};

static const iht_trace_t aa;
struct iht_data_entry_s {
    uint64_t src_ip;
    uint64_t dst_ip;
    uint64_t info;
    // TODO: Add more fields about the more infor about trace data
    // is_kernel? is_user? is_interrupt? is_exception? etc.
};

/* Allocator APIs */
typedef void* (*iht_malloc_func)(size_t size);
typedef void* (*iht_realloc_func)(void* ptr, size_t size);
typedef void* (*iht_calloc_func)(size_t count, size_t size);
typedef void (*iht_free_func)(void* ptr);

IHT_EXTERN int iht_set_allocator(iht_malloc_func malloc_func,
                                 iht_realloc_func realloc_func,
                                 iht_calloc_func calloc_func,
                                 iht_free_func free_func);

/* Trace APIs */
IHT_EXTERN iht_trace_t* iht_trace_init(pid_t pid);
IHT_EXTERN void iht_trace_close(iht_trace_t* trace);
IHT_EXTERN int iht_trace_dump(iht_trace_t* trace);

/* LBR (Last Branch Record) APIs */
IHT_EXTERN int iht_lbr_start(iht_trace_t* trace,
                             uint64_t lbr_filters);
IHT_EXTERN int iht_lbr_stop(iht_trace_t* trace);

/* BTS (Branch Trace Store) APIs */
IHT_EXTERN int iht_bts_start(iht_trace_t* trace,
                             uint64_t bts_filters,
                             uint64_t bts_buffer_size);
IHT_EXTERN int iht_bts_stop(iht_trace_t* trace);

#ifdef __cplusplus
}
#endif

#endif /* _IHT_H_ */