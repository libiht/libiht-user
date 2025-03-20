////////////////////////////////////////////////////////////////////////////////
//
//  File          : src/iht-ioctl.h
//  Description   : IOCTL definitions for the IHT kernel component.
//
//   Author : Thomason Zhao
//

#ifndef _IHT_IOCTL_H_
#define _IHT_IOCTL_H_

#include "iht.h"

enum IOCTL {
    LIBIHT_IOCTL_BASE,  // Placeholder

    // LBR
    LIBIHT_IOCTL_ENABLE_LBR,
    LIBIHT_IOCTL_DISABLE_LBR,
    LIBIHT_IOCTL_DUMP_LBR,
    LIBIHT_IOCTL_CONFIG_LBR,
    LIBIHT_IOCTL_LBR_END,  // End of LBR

    // BTS
    LIBIHT_IOCTL_ENABLE_BTS,
    LIBIHT_IOCTL_DISABLE_BTS,
    LIBIHT_IOCTL_DUMP_BTS,
    LIBIHT_IOCTL_CONFIG_BTS,
    LIBIHT_IOCTL_BTS_END,  // End of BTS
};

//
// LBR Type definitions

// Define LBR stack entry
struct lbr_stack_entry {
    uint64_t from;  // Retrieve from MSR_LBR_NHM_FROM + offset
    uint64_t to;    // Retrieve from MSR_LBR_NHM_TO + offset
};
typedef struct lbr_stack_entry lbr_stack_entry_t;

// Define LBR configuration
struct lbr_config {
    uint32_t pid;         // Process ID
    uint64_t lbr_select;  // MSR_LBR_SELECT
};
typedef struct lbr_config lbr_config_t;

// Define LBR data
struct lbr_data {
    uint64_t lbr_tos;                 // MSR_LBR_TOS
    lbr_stack_entry_t *entries;  // LBR stack entries
};
typedef struct lbr_data lbr_data_t;

// Define the lbr IOCTL structure
struct lbr_ioctl_request {
    lbr_config_t lbr_config;
    lbr_data_t *buffer;
};
typedef struct lbr_ioctl_request lbr_ioctl_request_t;

//
// BTS Type definitions

// Define BTS record
struct bts_record {
    uint64_t from;  // branch from
    uint64_t to;    // branch to
    uint64_t misc;  // misc information
};
typedef struct bts_record bts_record_t;

// Define BTS configuration
struct bts_config {
    uint64_t pid;              // Process ID
    uint64_t bts_config;       // MSR_IA32_DEBUGCTLMSR
    uint64_t bts_buffer_size;  // BTS buffer size
};
typedef struct bts_config bts_config_t;

// Define BTS data
// TODO: pay attention when using this struct in dump bts
struct bts_data {
    bts_record_t *bts_buffer_base;  // BTS buffer base
    bts_record_t *bts_index;        // BTS current index
    uint64_t bts_interrupt_threshold;         // BTS interrupt threshold
};
typedef struct bts_data bts_data_t;

// Define the bts IOCTL structure
struct bts_ioctl_request {
    bts_config_t bts_config;
    bts_data_t *buffer;
};
typedef struct bts_ioctl_request bts_ioctl_request_t;

//
// xIOCTL Type definitions

// Define the xIOCTL structure
struct xioctl_request {
    enum IOCTL cmd;
    union {
        lbr_ioctl_request_t lbr;
        bts_ioctl_request_t bts;
    } body;
};
typedef struct xioctl_request xioctl_request_t;

#endif /* _IHT_IOCTL_H_ */
