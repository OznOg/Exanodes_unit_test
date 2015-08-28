/* $Id$
 *
 * Copyright 2002, 2015 Seanodes Ltd http://www.seanodes.com. All rights
 * reserved and protected by French, UK, U.S. and other countries' copyright laws.
 * This file is part of Exanodes Unit test library and is subject to the terms
 * and conditions defined in the LICENSE file which is present in the root
 * directory of the project.
 */

#ifndef _EXA_BYTEORDER_H
#define _EXA_BYTEORDER_H


#ifdef __KERNEL__

#  include <asm/byteorder.h>

#else /* __KERNEL__ */

#  include <byteswap.h>

#  if defined(EXA_LITTLE_ENDIAN)
#    define __le16_to_cpu(x) (x)
#    define __le32_to_cpu(x) (x)
#    define __le64_to_cpu(x) (x)
#    define __cpu_to_le16(x) (x)
#    define __cpu_to_le32(x) (x)
#    define __cpu_to_le64(x) (x)
#    define __be16_to_cpu(x) bswap_16(x)
#    define __be32_to_cpu(x) bswap_32(x)
#    define __be64_to_cpu(x) bswap_64(x)
#    define __cpu_to_be16(x) bswap_16(x)
#    define __cpu_to_be32(x) bswap_32(x)
#    define __cpu_to_be64(x) bswap_64(x)
#  elif defined(EXA_BIG_ENDIAN)
#    define __le16_to_cpu(x) bswap_16(x)
#    define __le32_to_cpu(x) bswap_32(x)
#    define __le64_to_cpu(x) bswap_64(x)
#    define __cpu_to_le16(x) bswap_16(x)
#    define __cpu_to_le32(x) bswap_32(x)
#    define __cpu_to_le64(x) bswap_64(x)
#    define __be16_to_cpu(x) (x)
#    define __be32_to_cpu(x) (x)
#    define __be64_to_cpu(x) (x)
#    define __cpu_to_be16(x) (x)
#    define __cpu_to_be32(x) (x)
#    define __cpu_to_be64(x) (x)
#  else
#    error Unknown endianness
#  endif

#endif  /* __KERNEL__ */


#ifdef EXA_BIG_ENDIAN_SUPERBLOCKS
#  define exa16_to_cpu(x) __be16_to_cpu(x)
#  define exa32_to_cpu(x) __be32_to_cpu(x)
#  define exa64_to_cpu(x) __be64_to_cpu(x)
#  define cpu_to_exa16(x) __cpu_to_be16(x)
#  define cpu_to_exa32(x) __cpu_to_be32(x)
#  define cpu_to_exa64(x) __cpu_to_be64(x)
#else /* EXA_BIG_ENDIAN_SUPERBLOCKS */
#  define exa16_to_cpu(x) __le16_to_cpu(x)
#  define exa32_to_cpu(x) __le32_to_cpu(x)
#  define exa64_to_cpu(x) __le64_to_cpu(x)
#  define cpu_to_exa16(x) __cpu_to_le16(x)
#  define cpu_to_exa32(x) __cpu_to_le32(x)
#  define cpu_to_exa64(x) __cpu_to_le64(x)
#endif /* EXA_BIG_ENDIAN_SUPERBLOCKS */


#endif /* _EXA_BYTEORDER_H */
