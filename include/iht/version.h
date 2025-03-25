////////////////////////////////////////////////////////////////////////////////
//
//  File          : include/iht/version.h
//  Description   : Version information for the IHT library.
//
//   Author : Thomason Zhao
//

#ifndef _IHT_VERSION_H_
#define _IHT_VERSION_H_

/*
 * Versions with the same major number are ABI stable. API is allowed to
 * evolve between minor releases, but only in a backwards compatible way.
 */
#define IHT_VERSION_MAJOR 0
#define IHT_VERSION_MINOR 1
#define IHT_VERSION_PATCH 0
#define IHT_VERSION_ISRELEASE 0
#define IHT_VERSION_SUFFIX "dev"

#define IHT_VERSION_HEX ((IHT_VERSION_MAJOR << 16) | \
                         (IHT_VERSION_MINOR << 8) |  \
                         (IHT_VERSION_PATCH))

#endif /* _IHT_VERSION_H_ */