////////////////////////////////////////////////////////////////////////////////
//
//  File          : src/iht-common.c
//  Description   : Common functions used across both windows and linux
//                  platforms.
//
//   Author : Thomason Zhao
//

#include "iht-common.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iht.h"

typedef struct {
    iht_malloc_func malloc;
    iht_realloc_func realloc;
    iht_calloc_func calloc;
    iht_free_func free;
} iht__allocator_t;

static iht__allocator_t iht__allocator = {
    malloc,
    realloc,
    calloc,
    free};

char *iht__strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *dup = iht__malloc(len);
    if (dup == NULL) {
        return NULL;
    }

    return (char *)memcpy(dup, s, len);
}

char *iht__strndup(const char *s, size_t n) {
    size_t len = strnlen(s, n);
    if (n < len) {
        len = n;
    }

    char *dup = iht__malloc(len + 1);
    if (dup == NULL) {
        return NULL;
    }

    dup[len] = '\0';
    return (char *)memcpy(dup, s, len);
}

void *iht__malloc(size_t size) {
    return iht__allocator.malloc(size);
}

void *iht__realloc(void *ptr, size_t size) {
    return iht__allocator.realloc(ptr, size);
}

void *iht__calloc(size_t count, size_t size) {
    return iht__allocator.calloc(count, size);
}

void iht__free(void *ptr) {
    iht__allocator.free(ptr);
}

int iht_set_allocator(iht_malloc_func malloc, iht_realloc_func realloc, iht_calloc_func calloc, iht_free_func free) {
    if (malloc == NULL || realloc == NULL || calloc == NULL || free == NULL) {
        return -1;
    }

    iht__allocator.malloc = malloc;
    iht__allocator.realloc = realloc;
    iht__allocator.calloc = calloc;
    iht__allocator.free = free;
    return 0;
}
