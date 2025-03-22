////////////////////////////////////////////////////////////////////////////////
//
//  File          : src/linux/ioctl.c
//  Description   : The ioctl operations for the linux driver.
//
//   Author : Thomason Zhao
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "iht-common.h"
#include "iht-ioctl.h"

// Device name
#define DEVICE_NAME "libiht-info"

// I/O control macros
#define LIBIHT_LKM_IOCTL_MAGIC 'l'
#define LIBIHT_LKM_IOCTL_BASE _IO(LIBIHT_LKM_IOCTL_MAGIC, 0)

static int device_fd = -1;

int iht__ioctl_init(void) {
    if (device_fd >= 0) {
        perror("Device already opened...");
        return IHT__ERR(IHT_EIOCTL_ALREADY_INIT);
    }

    device_fd = open("/proc/" DEVICE_NAME, O_RDWR);
    if (device_fd < 0) {
        perror("Failed to open the device...");
        return IHT__ERR(IHT_EIOCTL_DEVICE_OPEN_FAILED);
    }
    return IHT_SUCCESS;
}

int iht__ioctl_close(void) {
    if (device_fd < 0) {
        perror("Device not opened...");
        return IHT__ERR(IHT_EIOCTL_UNINIT);
    }

    if (close(device_fd) < 0) {
        perror("Failed to close the device...");
        return IHT__ERR(IHT_EIOCTL_DEVICE_CLOSE_FAILED);
    }
    return IHT_SUCCESS;
}

int iht__ioctl(xioctl_request_t* req) {
    if (device_fd < 0) {
        perror("Device not opened...");
        return IHT__ERR(IHT_EIOCTL_UNINIT);
    }

    if (ioctl(device_fd, LIBIHT_LKM_IOCTL_BASE, req)) {
        perror("Failed to perform ioctl operation...");
        return IHT__ERR(IHT_EIOCTL_INVALID);
    }
    return IHT_SUCCESS;
}