////////////////////////////////////////////////////////////////////////////////
//
//  File          : include/iht/errno.h
//  Description   : Error codes for the IHT library.
//
//   Author : Thomason Zhao
//

#ifndef _IHT_ERRNO_H_
#define _IHT_ERRNO_H_

/* TODO: Error Codes */
#include <errno.h>

#if EDOM > 0
#define IHT__ERR(x) (-(x))
#else
#define IHT__ERR(x) (x)
#endif

enum IHT_ERROR_CODES {
    IHT_SUCCESS = 0,  // No error
    IHT_EGENERAL,     // General error
    IHT_ENOTIMPL,     // Not implemented

    IHT_ETRACE_INVALID = 128,    // Invalid trace
    IHT_ETRACE_STATE_INVALID,    // Invalid trace state
    IHT_ETRACE_PID_INVALID,      // Invalid trace PID
    IHT_ETRACE_ALREADY_RUNNING,  // Trace already running
    IHT_ETRACE_ALREADY_STOPPED,  // Trace already stopped

    IHT_EIOCTL_INVALID = 256,        // Invalid ioctl
    IHT_EIOCTL_UNINIT,               // Ioctl uninitialized
    IHT_EIOCTL_ALREADY_INIT,         // Ioctl already initialized
    IHT_EIOCTL_DEVICE_OPEN_FAILED,   // Device open failed
    IHT_EIOCTL_DEVICE_CLOSE_FAILED,  // Device close failed
};

#endif /* _IHT_ERRNO_H_ */