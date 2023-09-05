/*
 * Information on macros controlling some features.
 *
 * Files and line numbers come from a Linux system.  They may not be the same
 * on MacOS
 */
#ifdef __GLIBC_USE // /usr/include/features.h:27: #define __GLIBC_USE(F) __GLIBC_USE_ ## F
    // /usr/include/bits/libc-header-start.h:{40,42}: #define __GLIBC_USE_LIB_EXT2 {1, 0}
    // depends on __USE_GNU, __STDC_WANT_LIB_EXT2__
    printf("__GLIBC_USE(LIB_EXT2) = %d\n", __GLIBC_USE(LIB_EXT2));
#else
    isndefed(__GLIBC_USE);
#endif

#ifdef __GLIBC_USE
#if (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8	\
     || __GLIBC_USE (LIB_EXT2)) // /usr/include/string.h:164
    printf("The condition of the '#if' from string.h that controls whether strdup gets declared is TRUE\n");
#else
    printf("The condition of the '#if' from string.h that controls whether strdup gets declared is FALSE\n");
#endif
#endif

#ifdef _POSIX_C_SOURCE // /usr/include/features.h:{265-279}
    isdefed(_POSIX_C_SOURCE);
    printvall(_POSIX_C_SOURCE);
#else
    isndefed(_POSIX_C_SOURCE);
#endif
#ifdef _POSIX_SOURCE // /usr/include/features.h:{263-292}
    isdefed(_POSIX_SOURCE);
    printvall(_POSIX_SOURCE);
#else
    isndefed(_POSIX_SOURCE);
#endif

#ifdef _X_OPEN_SOURCE // ??
    isdefed(_X_OPEN_SOURCE);
    printvall(_X_OPEN_SOURCE);
#else
    isndefed(_X_OPEN_SOURCE);
#endif

#ifdef __USE_XOPEN_EXTENDED // features.h:{332,350}
    isdefed(__USE_XOPEN_EXTENDED);
    printval(__USE_XOPEN_EXTENDED);
#else
    isndefed(__USE_XOPEN_EXTENDED);
#endif

#if defined __USE_XOPEN2K8 // features.h:{324,338}
    isdefed(__USE_XOPEN2K8);
    printval(__USE_XOPEN2K8);
#else
    isndefed(__USE_XOPEN2K8);
#endif

#ifdef _GNU_SOURCE // Not defined in features.h but does control things in it
    isdefed(_GNU_SOURCE);
    printval(_GNU_SOURCE);
#else
    isndefed(_GNU_SOURCE);
#endif

#ifdef _DEFAULT_SOURCE // /usr/include/features.h:{186,208,221}
    isdefed(_DEFAULT_SOURCE);
    printval(_DEFAULT_SOURCE);
#else
    isndefed(_DEFAULT_SOURCE);
#endif
