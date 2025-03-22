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
    device_fd = open("/proc/" DEVICE_NAME, O_RDWR);
    if (device_fd < 0) {
        perror("Failed to open the device...");
        return IHT__ERR(IHT_EIOCTL_DEVICE_NOT_FOUND);
    }
    return 0;
}

int iht__ioctl(xioctl_request_t* req) {
    if (ioctl(device_fd, LIBIHT_LKM_IOCTL_BASE, req)) {
        perror("Failed to perform ioctl operation...");
        return IHT__ERR(IHT_EIOCTL_INVALID);
    }
}