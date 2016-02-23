#ifndef _INCLUDE_EXTENSION_VERSIONLIB_H_
#define _INCLUDE_EXTENSION_VERSIONLIB_H_

#if !defined(MODULE_USE_VERSIONLIB)
// These get defined in module_version.h since
// versionlib does not use versionlib.
    #undef EXTENSION_LOCAL_REV
    #undef EXTENSION_CSET
    #undef EXTENSION_VERSION
    #undef EXTENSION_BUILD_TIME
#endif

#ifdef __cplusplus
    #define EXTERN_C extern "C"
#else
    #define EXTERN_C extern
#endif

EXTERN_C const char *EXTENSION_LOCAL_REV;
EXTERN_C const char *EXTENSION_SHA;
EXTERN_C const char *EXTENSION_VERSION;
EXTERN_C const char *EXTENSION_BUILD_TIME;

#endif // _INCLUDE_EXTENSION_VERSIONLIB_H_
