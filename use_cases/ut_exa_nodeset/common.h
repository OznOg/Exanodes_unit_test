/* $Id$
 *
 * Copyright 2002, 2015 Seanodes Ltd http://www.seanodes.com. All rights
 * reserved and protected by French, UK, U.S. and other countries' copyright laws.
 * This file is part of Exanodes Unit test library and is subject to the terms
 * and conditions defined in the LICENSE file which is present in the root
 * directory of the project.
 */

#ifndef _COMMON_H
#define _COMMON_H

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <syslog.h>
#include <sys/types.h>
#include <netinet/in.h>
#endif

#include "exa_inttypes.h"

#ifndef __KERNEL__
#include "exa_memtrace.h"
#endif /* ifdef __KERNEL__ */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAX
/** Maximum of two values */
#define MAX(a, b)  ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
/** Minimum of two values */
#define MIN(a, b)  ((a) < (b) ? (a) : (b))
#endif

/**
 * Align val on a boundary so that return value <= val. Boundary
 * must be a power of 2
 */
#define ALIGN_INF(val,boundary) \
   ((val) & (~((typeof(val))(boundary)-1)))

/*
 * Align val on a boundary so that val <= return value. Boundary
 * must be a power of 2
 */
#define ALIGN_SUP(val,boundary) \
   ((((val)-1) & (~((typeof(val))(boundary)-1))) + (typeof(val))(boundary))

/*
 * Test if a value is a power of two
 * */
#define IS_POWER_OF_TWO(x) \
  (((x) != 0) && ((x) & ((x) - 1)) == 0)

/*
 * Static assert: if the predicate is FALSE, the 2nd case will be a duplicate
 * of the 1st case.
 * */
#define COMPILE_TIME_ASSERT(predicate)		\
  switch (0) { case 0: case (predicate): ; }

/*
 * The macro exa_mkstr(a) makes a string from an integer value. For
 * example, the exa_mkstr(11) will be replaced by "11".
 *
 * The important point here is that we need 2 macros to do this job
 * properly on constants given by #define.  FE if we have #define TOTO
 * 11 , the exa_mkstrinter(TOTO) will be replaced by \"TOTO\" and
 * _NOT_ "TOTO". The difference is that calling it in
 * printf(exa_mkstrinter(TOTO)); will be replaced by printf(\"TOTO\");
 * and that is obviously not correct (\"TOTO\" is a string, but a
 * string must be sur- -rounded by "", and that is not the case.
 *
 * So the aim of calling this macro through another one is that the
 * second macro will interpret \" as " and give the good result
 * "TOTO". So even if this is quite strange these two macros must be
 * kept.
 *
 * This macro is used for example in the following situation :
 * #define TOTO 11
 * char toto[TOTO+1];
 * sscanf(str, "%s", toto); <- does not specify the max size of the string
 * sscanf(str, "%"exa_mkstr(TOTO)"s", toto); does the trick because will be
 *  replaced by sscanf(str, "%11s", toto);
 */

#define exa_mkstrinter(a) #a
#define exa_mkstr(a) exa_mkstrinter(a)

/* --- Assertion macros ---------------------------------------------- */

#ifndef __KERNEL__

#define EXA_ASSERT(expr) ({						\
      if (! (expr)) {							\
	syslog(LOG_EMERG, "[%s@%s:%d] Assertion '%s' failed",           \
	       __PRETTY_FUNCTION__, __FILE__, __LINE__, # expr);        \
	abort();							\
      }									\
    })

#define EXA_ASSERT_VERBOSE(expr,fmt,args...) ({                         \
      if (! (expr)) {                                                   \
	syslog(LOG_EMERG, "[%s@%s:%d] Assertion '%s' failed: " fmt,     \
	       __PRETTY_FUNCTION__, __FILE__, __LINE__, # expr,         \
	       ## args);						\
	abort();							\
      }									\
    })

#endif /* __KERNEL__ */

/* --- Misc functions --------------------------------------------- */

char *exa_get_human_size(char *size_str, size_t n, uint64_t size_kb);
uint64_t exa_get_size_kb(const char *size_string);
int exa_process_set_name(char *name);
int exa_noio(int socket_id);
int exa_get_fd(void);
int exa_select_in(int fd, fd_set *set);
int exa_select_out(int fd, fd_set *set);

#ifndef __KERNEL__
int exa_host_addr(const char *hostname, struct in_addr *addr);
#endif

#ifdef __cplusplus
}
#endif

#endif


