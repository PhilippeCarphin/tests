#ifdef __GLIBC_USE
#if (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8	\
     || __GLIBC_USE (LIB_EXT2))
    printf("True for defining strdup\n");
#else
    printf("False for defining strdup\n");
#endif
#endif

#ifdef _POSIX_C_SOURCE
    isdefed(_POSIX_C_SOURCE);
    printvall(_POSIX_C_SOURCE);
#else
    isndefed(_POSIX_C_SOURCE);
#endif
#ifdef _POSIX_SOURCE
    isdefed(_POSIX_SOURCE);
    printvall(_POSIX_SOURCE);
#else
    isndefed(_POSIX_SOURCE);
#endif

#ifdef _X_OPEN_SOURCE
    isdefed(_X_OPEN_SOURCE);
    printvall(_X_OPEN_SOURCE);
#else
    isndefed(_X_OPEN_SOURCE);
#endif

#ifdef __USE_XOPEN_EXTENDED
    isdefed(__USE_XOPEN_EXTENDED);
    printval(__USE_XOPEN_EXTENDED);
#else
    isndefed(__USE_XOPEN_EXTENDED);
#endif

#if defined __USE_XOPEN2K8
    isdefed(__USE_XOPEN2K8);
    printval(__USE_XOPEN2K8);
#else
    isndefed(__USE_XOPEN2K8);
#endif

#ifdef LIB_EXT2
    printval(LIB_EXT2);
#else
    isndefed(LIB_EXT2);
#endif

#ifdef __GLIBC_USE
    printf("__GLIBC_USE(LIB_EXT2) = %d\n", __GLIBC_USE(LIB_EXT2));
#else
    isndefed(__GLIBC_USE);
#endif

#ifdef _GNU_SOURCE
    isdefed(_GNU_SOURCE);
    printval(_GNU_SOURCE);
#else
    isndefed(_GNU_SOURCE);
#endif

#ifdef _DEFAULT_SOURCE
    isdefed(_DEFAULT_SOURCE);
    printval(_DEFAULT_SOURCE);
#else
    isndefed(_DEFAULT_SOURCE);
#endif
