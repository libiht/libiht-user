////////////////////////////////////////////////////////////////////////////////
//
//  File          : src/lbr.c
//  Description   : This is the LBR trace implementation for the IHT.
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

int iht_lbr_start(iht_trace_t *trace, uint64_t lbr_filters) {
    if (trace == NULL)
        return IHT_ETRACE_INVALID;
    if (trace->state == IHT_TRACE_STATE_LBR)
        return IHT_ETRACE_ALREADY_RUNNING;
    else if (trace->state == IHT_TRACE_STATE_BTS)
        return IHT_ETRACE_STATE_INVALID;

    /* PID shouldn't be 0 */
    if (trace->pid <= 0)
        return IHT_ETRACE_PID_INVALID;

    trace->config.lbr_filters = lbr_filters;
    // TODO: start LBR trace with IOCTL

    trace->state = IHT_TRACE_STATE_LBR;
    return IHT_SUCCESS;
}

int iht_lbr_stop(iht_trace_t *trace) {
    if (trace == NULL)
        return IHT_ETRACE_INVALID;
    if (trace->state == IHT_TRACE_STATE_UNINIT)
        return IHT_ETRACE_ALREADY_STOPPED;
    else if (trace->state == IHT_TRACE_STATE_BTS)
        return IHT_ETRACE_STATE_INVALID;
    
    /* PID shouldn't be 0 */
    if (trace->pid <= 0)
        return IHT_ETRACE_PID_INVALID;
    
    // TODO: stop LBR trace with IOCTL

    trace->state = IHT_TRACE_STATE_UNINIT;
    return IHT_SUCCESS;
}

int iht__lbr_dump(iht_trace_t *trace) {
    // TOOD: dump LBR trace
    return IHT_ENOTIMPL;
}
