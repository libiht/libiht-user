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

    /* Set up the IOCTL request */
    xioctl_request_t req;
    memset(&req, 0, sizeof(req));
    req.body.bts.bts_config.pid = trace->pid;
    req.body.bts.bts_config.bts_buffer_size = bts_buffer_size;
    req.body.bts.bts_config.bts_config = bts_filters;
    req.cmd = LIBIHT_IOCTL_CONFIG_BTS;
    int ret = iht__ioctl(&req);
    if (ret != 0)
        return ret;
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

    /* Set up the IOCTL request */
    xioctl_request_t req;
    memset(&req, 0, sizeof(req));
    req.body.bts.bts_config.pid = trace->pid;
    req.cmd = LIBIHT_IOCTL_DISABLE_BTS;
    int ret = iht__ioctl(&req);
    if (ret != 0)
        return ret;

    trace->state = IHT_TRACE_STATE_UNINIT;
    return IHT_SUCCESS;
}

int iht__bts_dump(iht_trace_t *trace) {
    int ret;
    /* Set up the IOCTL request */
    xioctl_request_t req;
    memset(&req, 0, sizeof(req));

    /* Set up BTS buffer */
    req.body.bts.buffer = (bts_data_t *)iht__malloc(sizeof(bts_data_t));
    if (req.body.bts.buffer == NULL) {
        ret = IHT__ERR(IHT_EALLOC);
        goto no_cleanup;
    }
    req.body.bts.buffer->bts_buffer_base = (bts_record_t *)iht__malloc(trace->config.bts_buffer_size);
    if (req.body.bts.buffer->bts_buffer_base == NULL) {
        ret = IHT__ERR(IHT_EALLOC);
        goto buf_cleanup;
    }

    req.body.bts.bts_config.pid = trace->pid;
    req.cmd = LIBIHT_IOCTL_DUMP_BTS;
    ret = iht__ioctl(&req);
    if (ret != 0)
        goto req_cleanup;
    
    /* Dump the BTS to trace session */
    trace->entry_size = trace->config.bts_buffer_size / sizeof(bts_record_t);
    trace->entry_data = (iht_data_entry_t *)iht__malloc(sizeof(iht_data_entry_t) * trace->entry_size);
    if (trace->entry_data == NULL) {
        ret = IHT__ERR(IHT_EALLOC);
        goto req_cleanup;
    }

    int bts_tos = (req.body.bts.buffer->bts_index - req.body.bts.buffer->bts_buffer_base) / sizeof(bts_record_t);
    int idx = bts_tos;
    for (size_t i = 0; i < trace->entry_size; i++) {
        idx = (idx + 1) % trace->entry_size;

        if (req.body.bts.buffer->bts_buffer_base[i].from == 0)
            continue;
        trace->entry_data[i].src_ip = req.body.bts.buffer->bts_buffer_base[i].from;
        trace->entry_data[i].dst_ip = req.body.bts.buffer->bts_buffer_base[i].to;

        if (idx == bts_tos)
            break;
    }

req_cleanup:
    iht__free(req.body.bts.buffer->bts_buffer_base);
buf_cleanup:
    iht__free(req.body.bts.buffer);
no_cleanup:
    return ret;
}