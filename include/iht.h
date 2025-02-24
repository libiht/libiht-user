////////////////////////////////////////////////////////////////////////////////
//
//  File          : include/iht.h
//  Description   : This is the header file for Intel Hardware Trace library 
//                  (LibIHT) that provides the interface to the kernel component
//                  that manages the hardware trace capabilities of the Intel
//                  processors.
//
//   Author : Thomason Zhao
//

#ifndef _IHT_H_
#define _IHT_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BUILDING_IHT_SHARED) && defined(USING_IHT_SHARED)
#error "Either BUILDING_IHT_SHARED or USING_IHT_SHARED can be defined"
#endif

#ifndef IHT_EXTERN
#ifdef _WIN32
/* Windows - set up dll import/export decorators. */
#ifdef BUILDING_IHT_SHARED
/* Building shared library. */
#define IHT_EXTERN __declspec(dllexport)
#else
/* Using shared library. */
#define IHT_EXTERN __declspec(dllimport)
#endif /* BUILDING_IHT_SHARED */
#else
/* Linux - set up equivalent for visibility. */
#define IHT_EXTERN __attribute__((visibility("default")))
#endif /* _WIN32 */
#endif /* IHT_EXTERN */

// TODO: IHT error codes

// TODO: IHT types and structures

// IHT API functions

// TODO: LBR (Last Branch Record) API
IHT_EXTERN int iht_lbr_init(void);
IHT_EXTERN int iht_lbr_start(void);
IHT_EXTERN int iht_lbr_stop(void);
IHT_EXTERN int iht_lbr_dump(void);
IHT_EXTERN int iht_lbr_config(void);

// TODO: BTS (Branch Trace Store) API
IHT_EXTERN int iht_bts_init(void);
IHT_EXTERN int iht_bts_start(void);
IHT_EXTERN int iht_bts_stop(void);
IHT_EXTERN int iht_bts_dump(void);
IHT_EXTERN int iht_bts_config(void);


#ifdef __cplusplus
}
#endif

#endif /* _IHT_H_ */