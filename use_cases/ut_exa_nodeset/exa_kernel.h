/*
 * Copyright 2002, 2015 Seanodes Ltd http://www.seanodes.com. All rights
 * reserved and protected by French, UK, U.S. and other countries' copyright laws.
 * This file is part of Exanodes Unit test library and is subject to the terms
 * and conditions defined in the LICENSE file which is present in the root
 * directory of the project.
 */

#ifndef _EXA_KERNEL_H
#define _EXA_KERNEL_H

#ifndef __KERNEL__
#error "Should not be included in userspace"
#endif

#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/sysrq.h>
#include <linux/delay.h>
#include <linux/version.h>
#include <asm/div64.h>

#include "exa_memtrace.h"

/** \file exa_kernel.h
 * \brief Various kernel-space macros.
 *
 * Contains message logging macros, memory allocation routines, bit
 * manipulation macros and 64-bits integer division functions.
 */

/* --- 64-bit integer division ------------------------------------ */

/**
 * Computes the division's remainder of a by q
 */
static inline u32 reste64(u64 a, u32 q) {
  return do_div(a,q);
}

/**
 * Returns the quotient of a by q, rounded at the immediatly inferior
 * integer.
 */
static inline u64 quotient64(u64 a, u32 q) {
  /*
   *  The semantic of the do_div(a, b) macro is ugly. It divides a by
   *  b, returns the rest and modify a so that it contains the
   *  quotient of the division.
   */
   do_div(a,q);
   return a;
}

/**
 * Returns the quotient of a by q, rounded at the immediatly superior
 * integer.
 */
static inline u64 quotient_ceil64(u64 a, u32 q) {
  /*
   *  The semantic of the do_div(a, b) macro is ugly. It divides a by
   *  b, returns the rest and modify a so that it contains the
   *  quotient of the division.
   */
  if (do_div(a,q) == 0)
    return a;
  else
    return a+1;
}

/* --- message loggging macros --------------------------------------- */

/** Conditionnaly log a message depending on the value of \a
 * debug_switch. The message is logged at level KERN_EMERG and prepended
 * by the file, line number an function name in which the macro is
 * invoked.
 * \param[in] debug_switch Print message only if equal to 1
 * \param[in] fmt          Printf-like format string, followed by arguments.
 * \param[in] args         Printf-like arguments
 * \sa PERROR(), PINFO().
 */

#define PDEBUG(debug_switch, fmt, args...)					\
  do if (debug_switch==1) {						\
    printk(KERN_DEBUG "%s:%d - %s: " fmt,__FILE__,__LINE__,__FUNCTION__, ## args);	\
  } while(0)

/** Log an error message at level KERN_ERR. Message is prepended
 * by the file, line number an function name in which the macro is
 * invoked.
 * \param[in] fmt     Printf-like format string, followed by arguments.
 * \param[in] args    Printf-like arguments.
 * \sa PDEBUG(), PINFO().
 */

#define PERROR(fmt, args...)							\
  do {									\
    printk(KERN_ERR "%s:%d (%s): ERROR - " fmt,__FILE__,__LINE__,__FUNCTION__, ## args); \
  } while(0)

/** Log an informational message at level KERN_ERR. Message is prepended
 * by the file, line number an function name in which the macro is
 * invoked.
 * \param[in] fmt     Printf-like format string, followed by arguments.
 * \param[in] args    Printf-like arguments.
 * \sa PDEBUG(), PERROR().
 */

#define PINFO(fmt, args...)								\
  do {										\
    printk(KERN_INFO "%s:%d (%s): INFO - " fmt,__FILE__,__LINE__,__FUNCTION__, ## args);	\
  } while(0)

/* --- Assertion macros ---------------------------------------------- */

#ifdef DEBUG

#ifdef CONFIG_MAGIC_SYSRQ

/*
 * handle_sysrq() doesn't have the same prototype in 2.4 and 2.6
 * kernels.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
#define EXA_HANDLE_SYSRQ(c) handle_sysrq((c), NULL, NULL, NULL)
#elif LINUX_VERSION_CODE < KERNEL_VERSION(2,6,19)
#define EXA_HANDLE_SYSRQ(c) handle_sysrq((c), NULL, NULL)
#else
#define EXA_HANDLE_SYSRQ(c) handle_sysrq((c), NULL)
#endif /* LINUX_VERSION_CODE */

#define EXA_ASSERT_SYSRQ() ({ \
    EXA_HANDLE_SYSRQ ('v'); \
    EXA_HANDLE_SYSRQ ('w'); \
    EXA_HANDLE_SYSRQ ('m'); \
    EXA_HANDLE_SYSRQ ('t'); \
})
#else  /* CONFIG_MAGIC_SYSRQ */
#define EXA_ASSERT_SYSRQ()
#endif /* CONFIG_MAGIC_SYSRQ */

#define EXA_ASSERT(expr) ({ \
  if (! (expr)) {\
    int i; \
    printk(KERN_EMERG "[%s@%s:%d] Assertion '%s' failed\n", __PRETTY_FUNCTION__, \
	   __FILE__, __LINE__, # expr); \
    for (i = 0; i < 1000; i++) \
      udelay (1000); \
    EXA_ASSERT_SYSRQ(); \
    BUG(); }\
})

#define EXA_ASSERT_VERBOSE(expr, fmt, args...) ({ \
  if (! (expr)) {\
    int _i; \
    printk(KERN_EMERG "[%s@%s:%d] Assertion '%s' failed: " fmt "\n", __PRETTY_FUNCTION__, \
	   __FILE__, __LINE__, # expr, ## args); \
    for (_i = 0; _i < 1000; _i++) \
      udelay (1000); \
    EXA_ASSERT_SYSRQ(); \
    BUG(); }\
})

#else /* DEBUG */

#define EXA_ASSERT(expr) ({ \
  if (! (expr)) {\
    printk(KERN_EMERG "[%s@%s:%d] Assertion '%s' failed\n", __PRETTY_FUNCTION__, \
	   __FILE__, __LINE__, # expr); \
    BUG(); }\
})

#define EXA_ASSERT_VERBOSE(expr, fmt, args...) ({ \
  if (! (expr)) {\
    printk(KERN_EMERG "[%s@%s:%d] Assertion '%s' failed: " fmt "\n", __PRETTY_FUNCTION__, \
	   __FILE__, __LINE__, # expr, ## args); \
    BUG(); }\
})

#endif /* DEBUG */

/* Some sparse annotations are not available in old kernels */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 4, 28)
 #define __user
#endif

#endif /* _EXA_KERNEL_H */
