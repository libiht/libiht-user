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

#include "iht-ioctl.h"

// Device name
#define DEVICE_NAME "libiht-info"

// I/O control macros
#define LIBIHT_LKM_IOCTL_MAGIC 'l'
#define LIBIHT_LKM_IOCTL_BASE       _IO(LIBIHT_LKM_IOCTL_MAGIC, 0)

// TODO: Consider what api should define for this
int iht__ioctl(xioctl_request_t *request) {
    int fd = open("/proc/" DEVICE_NAME, O_RDWR);
    return ioctl(fd, LIBIHT_LKM_IOCTL_BASE, request);
}