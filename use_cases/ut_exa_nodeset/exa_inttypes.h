/*
 * Copyright 2002, 2015 Seanodes Ltd http://www.seanodes.com. All rights
 * reserved and protected by French, UK, U.S. and other countries' copyright laws.
 * This file is part of Exanodes Unit test library and is subject to the terms
 * and conditions defined in the LICENSE file which is present in the root
 * directory of the project.
 */

#ifndef _EXA_INTTYPES_H
#define _EXA_INTTYPES_H

/**
 * \file exa_inttypes.h
 * \brief fixed size integer types definitions and formatting
 */


#ifdef __KERNEL__

#include <linux/types.h>

#else /* __KERNEL__ */

#ifdef __cplusplus
#define __STDC_FORMAT_MACROS
#endif
#include <inttypes.h>

typedef uint8_t __u8;
typedef uint16_t __u16;
typedef uint32_t __u32;
typedef uint64_t __u64;

#endif /* __KERNEL__ */

/** Macro for size_t constant declaration */
# if BITS_PER_LONG == 64
# define EXA_SIZE_T_C(c)	c ## LU
#else
# define EXA_SIZE_T_C(c)	c ## U
#endif /* BITS_PER_LONG */

#endif /* _EXA_INTTYPES_H */
