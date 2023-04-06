#if !defined _FEATURES_H && !defined __need_uClibc_config_h
# error Never include <bits/uClibc_config.h> directly; use <features.h> instead
#endif

#define __UCLIBC_MAJOR__ 1
#define __UCLIBC_MINOR__ 0
#define __UCLIBC_SUBLEVEL__ 39
/* Automatically generated file; DO NOT EDIT. */
/* uClibc-ng 1.0.39 C Library Configuration */
#undef __TARGET_aarch64__
#undef __TARGET_alpha__
#undef __TARGET_arc__
#define __TARGET_arm__ 1
#undef __TARGET_avr32__
#undef __TARGET_bfin__
#undef __TARGET_c6x__
#undef __TARGET_cris__
#undef __TARGET_csky__
#undef __TARGET_frv__
#undef __TARGET_h8300__
#undef __TARGET_hppa__
#undef __TARGET_i386__
#undef __TARGET_ia64__
#undef __TARGET_kvx__
#undef __TARGET_lm32__
#undef __TARGET_m68k__
#undef __TARGET_metag__
#undef __TARGET_microblaze__
#undef __TARGET_mips__
#undef __TARGET_nds32__
#undef __TARGET_nios2__
#undef __TARGET_or1k__
#undef __TARGET_powerpc__
#undef __TARGET_riscv64__
#undef __TARGET_sh__
#undef __TARGET_sparc__
#undef __TARGET_sparc64__
#undef __TARGET_tile__
#undef __TARGET_x86_64__
#undef __TARGET_xtensa__

/* Target Architecture Features and Options */
#define __TARGET_ARCH__ "arm"
#define __FORCE_OPTIONS_FOR_ARCH__ 1
#define __CONFIG_ARM_EABI__ 1
#define __TARGET_SUBARCH__ ""
#undef __UCLIBC_FORMAT_FDPIC_ELF__
#define __UCLIBC_FORMAT_FLAT__ 1
#undef __UCLIBC_FORMAT_FLAT_SEP_DATA__
#undef __UCLIBC_FORMAT_SHARED_FLAT__
#define __ARCH_HAS_DEPRECATED_SYSCALLS__ 1
#define __ARCH_ANY_ENDIAN__ 1
#define __ARCH_LITTLE_ENDIAN__ 1
#undef __ARCH_WANTS_BIG_ENDIAN__
#define __ARCH_WANTS_LITTLE_ENDIAN__ 1
#define __ARCH_HAS_MMU__ 1
#undef __ARCH_USE_MMU__
#define __UCLIBC_HAS_FLOATS__ 1
#undef __UCLIBC_HAS_FPU__
#define __UCLIBC_HAS_SOFT_FLOAT__ 1
#define __DO_C99_MATH__ 1
#undef __DO_XSI_MATH__
#define __UCLIBC_HAS_LONG_DOUBLE_MATH__ 1
#define __KERNEL_HEADERS__ "/home/wzl/x-tools/arm-m4-linux-uclibceabi/arm-m4-linux-uclibceabi/sysroot/usr/include"
#define __UCLIBC_UCLINUX_BROKEN_MUNMAP__ 1
#define __HAVE_DOT_CONFIG__ 1

/* General Library Settings */
#define __DOPIC__ 1
#define __ARCH_HAS_NO_SHARED__ 1
#define __ARCH_HAS_NO_LDSO__ 1
#define __ARCH_HAS_UCONTEXT__ 1
#define __UCLIBC_CTOR_DTOR__ 1
#define __HAS_NO_THREADS__ 1
#undef __UCLIBC_HAS_LINUXTHREADS__
#undef __UCLIBC_HAS_THREADS_NATIVE__
#define __UCLIBC_HAS_SYSLOG__ 1
#define __UCLIBC_HAS_LFS__ 1
#define __MALLOC__ 1
#undef __MALLOC_SIMPLE__
#define __UCLIBC_DYNAMIC_ATEXIT__ 1
#define __UCLIBC_HAS_UTMPX__ 1
#define __UCLIBC_HAS_UTMP__ 1
#define __UCLIBC_SUSV2_LEGACY__ 1
#define __UCLIBC_SUSV3_LEGACY__ 1
#undef __UCLIBC_HAS_CONTEXT_FUNCS__
#undef __UCLIBC_SUSV3_LEGACY_MACROS__
#define __UCLIBC_SUSV4_LEGACY__ 1
#undef __UCLIBC_STRICT_HEADERS__
#undef __UCLIBC_HAS_STUBS__
#define __UCLIBC_HAS_SHADOW__ 1
#define __UCLIBC_HAS_PROGRAM_INVOCATION_NAME__ 1
#define __UCLIBC_HAS___PROGNAME__ 1
#define __UCLIBC_HAS_PTY__ 1
#define __ASSUME_DEVPTS__ 1
#define __UNIX98PTY_ONLY__ 1
#define __UCLIBC_HAS_GETPT__ 1
#define __UCLIBC_HAS_LIBUTIL__ 1
#define __UCLIBC_HAS_TM_EXTENSIONS__ 1
#define __UCLIBC_HAS_TZ_CACHING__ 1
#define __UCLIBC_HAS_TZ_FILE__ 1
#define __UCLIBC_HAS_TZ_FILE_READ_MANY__ 1
#define __UCLIBC_TZ_FILE_PATH__ "/etc/TZ"
#define __UCLIBC_FALLBACK_TO_ETC_LOCALTIME__ 1

/* Advanced Library Settings */
#define __UCLIBC_PWD_BUFFER_SIZE__ 256
#define __UCLIBC_GRP_BUFFER_SIZE__ 256

/* Support various families of functions */
#define __UCLIBC_LINUX_SPECIFIC__ 1
#define __UCLIBC_HAS_GNU_ERROR__ 1
#define __UCLIBC_BSD_SPECIFIC__ 1
#define __UCLIBC_HAS_BSD_ERR__ 1
#define __UCLIBC_HAS_OBSOLETE_BSD_SIGNAL__ 1
#undef __UCLIBC_HAS_BSD_B64_NTOP_B64_PTON__
#undef __UCLIBC_HAS_OBSOLETE_SYSV_SIGNAL__
#undef __UCLIBC_NTP_LEGACY__
#undef __UCLIBC_SV4_DEPRECATED__
#define __UCLIBC_HAS_REALTIME__ 1
#define __UCLIBC_HAS_ADVANCED_REALTIME__ 1
#define __UCLIBC_HAS_EPOLL__ 1
#define __UCLIBC_HAS_XATTR__ 1
#define __UCLIBC_HAS_PROFILING__ 1
#define __UCLIBC_HAS_CRYPT_IMPL__ 1
#undef __UCLIBC_HAS_SHA256_CRYPT_IMPL__
#undef __UCLIBC_HAS_SHA512_CRYPT_IMPL__
#define __UCLIBC_HAS_CRYPT__ 1
#define __UCLIBC_HAS_NETWORK_SUPPORT__ 1
#define __UCLIBC_HAS_SOCKET__ 1
#define __UCLIBC_HAS_IPV4__ 1
#undef __UCLIBC_HAS_IPV6__
#define __UCLIBC_USE_NETLINK__ 1
#define __UCLIBC_SUPPORT_AI_ADDRCONFIG__ 1
#undef __UCLIBC_HAS_BSD_RES_CLOSE__
#define __UCLIBC_HAS_COMPAT_RES_STATE__ 1
#undef __UCLIBC_HAS_EXTRA_COMPAT_RES_STATE__
#define __UCLIBC_HAS_RESOLVER_SUPPORT__ 1

/* String and Stdio Support */
#define __UCLIBC_HAS_STRING_GENERIC_OPT__ 1
#define __UCLIBC_HAS_STRING_ARCH_OPT__ 1
#define __UCLIBC_HAS_CTYPE_TABLES__ 1
#define __UCLIBC_HAS_CTYPE_SIGNED__ 1
#undef __UCLIBC_HAS_CTYPE_UNSAFE__
#define __UCLIBC_HAS_CTYPE_CHECKED__ 1
#undef __UCLIBC_HAS_CTYPE_ENFORCED__
#undef __UCLIBC_HAS_WCHAR__
#undef __UCLIBC_HAS_LIBICONV__
#undef __UCLIBC_HAS_LIBINTL__
#undef __UCLIBC_HAS_LOCALE__
#define __UCLIBC_HAS_HEXADECIMAL_FLOATS__ 1
#define __UCLIBC_HAS_GLIBC_CUSTOM_PRINTF__ 1
#undef __USE_OLD_VFPRINTF__
#define __UCLIBC_PRINTF_SCANF_POSITIONAL_ARGS__ 9
#undef __UCLIBC_HAS_STDIO_BUFSIZ_NONE__
#define __UCLIBC_HAS_STDIO_BUFSIZ_256__ 1
#undef __UCLIBC_HAS_STDIO_BUFSIZ_512__
#undef __UCLIBC_HAS_STDIO_BUFSIZ_1024__
#undef __UCLIBC_HAS_STDIO_BUFSIZ_2048__
#undef __UCLIBC_HAS_STDIO_BUFSIZ_4096__
#undef __UCLIBC_HAS_STDIO_BUFSIZ_8192__
#define __UCLIBC_HAS_STDIO_BUILTIN_BUFFER_NONE__ 1
#undef __UCLIBC_HAS_STDIO_BUILTIN_BUFFER_4__
#undef __UCLIBC_HAS_STDIO_BUILTIN_BUFFER_8__
#undef __UCLIBC_HAS_STDIO_SHUTDOWN_ON_ABORT__
#define __UCLIBC_HAS_STDIO_GETC_MACRO__ 1
#define __UCLIBC_HAS_STDIO_PUTC_MACRO__ 1
#define __UCLIBC_HAS_STDIO_AUTO_RW_TRANSITION__ 1
#undef __UCLIBC_HAS_FOPEN_LARGEFILE_MODE__
#define __UCLIBC_HAS_FOPEN_EXCLUSIVE_MODE__ 1
#undef __UCLIBC_HAS_FOPEN_CLOSEEXEC_MODE__
#define __UCLIBC_HAS_GLIBC_CUSTOM_STREAMS__ 1
#define __UCLIBC_HAS_PRINTF_M_SPEC__ 1
#define __UCLIBC_HAS_ERRNO_MESSAGES__ 1
#undef __UCLIBC_HAS_SYS_ERRLIST__
#define __UCLIBC_HAS_SIGNUM_MESSAGES__ 1
#undef __UCLIBC_HAS_SYS_SIGLIST__
#define __UCLIBC_HAS_GNU_GETOPT__ 1
#define __UCLIBC_HAS_GETOPT_LONG__ 1
#define __UCLIBC_HAS_GNU_GETSUBOPT__ 1
#undef __UCLIBC_HAS_ARGP__

/* Big and Tall */
#define __UCLIBC_HAS_REGEX__ 1
#define __UCLIBC_HAS_FNMATCH__ 1
#undef __UCLIBC_HAS_WORDEXP__
#define __UCLIBC_HAS_NFTW__ 1
#define __UCLIBC_HAS_FTW__ 1
#undef __UCLIBC_HAS_FTS__
#define __UCLIBC_HAS_GLOB__ 1
#define __UCLIBC_HAS_GNU_GLOB__ 1

/* Library Installation Options */
#define __RUNTIME_PREFIX__ "/"
#define __DEVEL_PREFIX__ "/usr/"
#define __MULTILIB_DIR__ "lib"
#define __HARDWIRED_ABSPATH__ 1

/* Security options */
#undef __UCLIBC_HAS_SSP__
#define __UCLIBC_BUILD_NOEXECSTACK__ 1

/* Development/debugging options */
#define __CROSS_COMPILER_PREFIX__ ""
#define __UCLIBC_EXTRA_CFLAGS__ ""
#undef __DODEBUG__
#undef __DOSTRIP__
#undef __DOASSERTS__
#undef __UCLIBC_MALLOC_DEBUGGING__
#define __WARNINGS__ "-Wall"
#undef __EXTRA_WARNINGS__
