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

    /* Set up the IOCTL request */
    xioctl_request_t req;
    memset(&req, 0, sizeof(req));
    req.body.lbr.lbr_config.pid = trace->pid;
    req.body.lbr.lbr_config.lbr_select = lbr_filters;
    req.cmd = LIBIHT_IOCTL_ENABLE_LBR;
    int ret = iht__ioctl(&req);
    if (ret != 0)
        return ret;
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

    /* Set up the IOCTL request */
    xioctl_request_t req;
    memset(&req, 0, sizeof(req));
    req.body.lbr.lbr_config.pid = trace->pid;
    req.cmd = LIBIHT_IOCTL_DISABLE_LBR;
    int ret = iht__ioctl(&req);
    if (ret != 0)
        return ret;
    trace->state = IHT_TRACE_STATE_UNINIT;
    return IHT_SUCCESS;
}

int iht__lbr_dump(iht_trace_t *trace) {
    int ret;
    /* Set up the IOCTL request */
    xioctl_request_t req;
    memset(&req, 0, sizeof(req));

    /* Set up LBR Buffer */
    req.body.lbr.buffer = (lbr_data_t *)iht__malloc(sizeof(lbr_data_t));
    if (req.body.lbr.buffer == NULL) {
        ret = IHT__ERR(IHT_EALLOC);
        goto no_cleanup;
    }
    req.body.lbr.buffer->entries =
        (lbr_stack_entry_t *)iht__malloc(sizeof(lbr_stack_entry_t) *
                                         LIBIHT_MAX_LBR_ENTRIES);
    if (req.body.lbr.buffer->entries == NULL) {
        ret = IHT__ERR(IHT_EALLOC);
        goto buf_cleanup;
    }
    memset(req.body.lbr.buffer->entries, 0,
           sizeof(lbr_stack_entry_t) * LIBIHT_MAX_LBR_ENTRIES);

    req.body.lbr.lbr_config.pid = trace->pid;
    req.cmd = LIBIHT_IOCTL_DUMP_LBR;
    ret = iht__ioctl(&req);
    if (ret != 0)
        goto req_cleanup;

    /* Dump LBR to trace session */
    trace->entry_size = LIBIHT_MAX_LBR_ENTRIES;
    trace->entry_data = (iht_data_entry_t *)iht__malloc(sizeof(iht_data_entry_t) * trace->entry_size);
    if (trace->entry_data == NULL) {
        ret = IHT__ERR(IHT_EALLOC);
        goto req_cleanup;
    }

    int lbr_tos = req.body.lbr.buffer->lbr_tos;
    int idx = lbr_tos;
    for (size_t i = 0; i < trace->entry_size; i++) {
        idx = (idx + 1) % trace->entry_size;

        if (req.body.lbr.buffer->entries[idx].from == 0)
            continue;
        trace->entry_data[i].src_ip = req.body.lbr.buffer->entries[idx].from;
        trace->entry_data[i].dst_ip = req.body.lbr.buffer->entries[idx].to;

        if (idx == lbr_tos)
            break;
    }
    ret = IHT_SUCCESS;

req_cleanup:
    iht__free(req.body.lbr.buffer->entries);
buf_cleanup:
    iht__free(req.body.lbr.buffer);
no_cleanup:
    return ret;
}
