////////////////////////////////////////////////////////////////////////////////
//
//  File          : src/version.c
//  Description   : Version information for the IHT library.
//
//   Author : Thomason Zhao
//

#include "iht.h"

#define IHT_STRINGIFY(x) #x

#define IHT_VERSION_STRING_BASE "LibIHT v" \
        IHT_STRINGIFY(IHT_VERSION_MAJOR) "." \
        IHT_STRINGIFY(IHT_VERSION_MINOR) "." \
        IHT_STRINGIFY(IHT_VERSION_PATCH)

#if IHT_VERSION_IS_RELEASE
#define IHT_VERSION_STRING IHT_VERSION_STRING_BASE
#else
#define IHT_VERSION_STRING IHT_VERSION_STRING_BASE "-" IHT_VERSION_SUFFIX
#endif


unsigned int iht_version(void) {
    return IHT_VERSION_HEX;
}

const char *iht_version_string(void) {
    return IHT_VERSION_STRING;
}
