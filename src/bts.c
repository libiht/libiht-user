////////////////////////////////////////////////////////////////////////////////
//
//  File          : src/bts.c
//  Description   : This is the BTS trace implementation for the IHT.
//
//   Author : Thomason Zhao, Uzen Huang
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "iht-common.h"
#include "iht.h"

int iht_bts_start(iht_trace_t *trace,
                  uint64_t bts_filters,
                  uint64_t bts_buffer_size) {
    if (trace == NULL)
        return IHT_ETRACE_INVALID;
    if (trace->state == IHT_TRACE_STATE_BTS)
        return IHT_ETRACE_ALREADY_RUNNING;
    else if (trace->state == IHT_TRACE_STATE_LBR)
        return IHT_ETRACE_STATE_INVALID;

    /* PID shouldn't be 0 */
    if (trace->pid <= 0)
        return IHT_ETRACE_PID_INVALID;

    trace->config.bts_filters = bts_filters;
    trace->config.bts_buffer_size = bts_buffer_size;
    // TODO: start BTS trace with IOCTL

    trace->state = IHT_TRACE_STATE_BTS;
    return IHT_SUCCESS;
}

int iht_bts_stop(iht_trace_t *trace) {
    if (trace == NULL)
        return IHT_ETRACE_INVALID;
    if (trace->state == IHT_TRACE_STATE_UNINIT)
        return IHT_ETRACE_ALREADY_STOPPED;
    else if (trace->state == IHT_TRACE_STATE_LBR)
        return IHT_ETRACE_STATE_INVALID;

    /* PID shouldn't be 0 */
    if (trace->pid <= 0)
        return IHT_ETRACE_PID_INVALID;

    // TODO: stop BTS trace with IOCTL

    trace->state = IHT_TRACE_STATE_UNINIT;
    return IHT_SUCCESS;
}

int iht__bts_dump(iht_trace_t *trace) {
    // TOOD: dump BTS trace
    return IHT_ENOTIMPL;
}