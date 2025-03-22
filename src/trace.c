////////////////////////////////////////////////////////////////////////////////
//
//  File          : src/trace.c
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

iht_trace_t *iht_trace_init(pid_t pid) {
    iht_trace_t *trace = (iht_trace_t *)iht__calloc(1, sizeof(iht_trace_t));
    if (trace == NULL)
        return NULL;

    trace->pid = pid == 0 ? getpid() : pid;
    return trace;
}

void iht_trace_close(iht_trace_t *trace) {
    if (trace == NULL)
        return;

    if (trace->data != NULL) {
        iht__free(trace->data);
        trace->data = NULL;
    }
    iht__free(trace);
}

int iht_trace_dump(iht_trace_t *trace) {
    if (trace == NULL)
        return IHT_ETRACE_INVALID;
    /* User should not modify the data_size field */
    if (trace->data_size != 0)
        return IHT_ETRACE_INVALID;
    
    if (trace->state == IHT_TRACE_STATE_LBR) {
        return iht__lbr_dump(trace);
    }
    else if (trace->state == IHT_TRACE_STATE_BTS) {
        return iht__bts_dump(trace);
    }
    else {
        return IHT_ETRACE_ALREADY_STOPPED;
    }
}