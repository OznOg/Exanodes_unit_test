/*
 * Copyright 2002, 2015 Seanodes Ltd http://www.seanodes.com. All rights
 * reserved and protected by French, UK, U.S. and other countries' copyright laws.
 * This file is part of Exanodes Unit test library and is subject to the terms
 * and conditions defined in the LICENSE file which is present in the root
 * directory of the project.
 */

#ifndef H_EXA_MEMTRACE
#define H_EXA_MEMTRACE

/** \file exa_memtrace.h
 * \brief Memory allocation routines.
 *
 * Memory allocation statistics can be switched on or off with
 * EXA_MEMTRACE (user space) and EXA_KMEMTRACE (kernel space).
 *
 * \sa exa_memtrace.c, exa_kmemtrace.c
 */

/** Memory trace verbosity */
typedef enum exa_meminfo_level
  {
    EXA_MEMINFO_SILENT,
    EXA_MEMINFO_SUMMARY,
    EXA_MEMINFO_DETAILED
  } exa_meminfo_level_t;

#ifdef __KERNEL__

#include <linux/vmalloc.h>
#include <linux/slab.h>

/** \def exa_kmalloc
 * Intended to be a replacement for kmalloc. If compiled with
 * EXA_KMEMTRACE defined, this function will be able to generate
 * statistics on memory allocation.
 * \param[in] size: number of bytes to be allocated.
 * \param[in] priority: importance and type of the request (see
 * kmalloc()).
 * \return a pointer to the allocated memory.
 * \sa exa_kfree
 */

/** \def exa_kfree
 * Intended to be a replacement for kfree.
 * \param[in] ptr: block of memory to be released. It must be a pointer
 * to memory allocated with exa_kmalloc().
 * \sa exa_kmalloc
 */

/** \def exa_vmalloc
 * Intended to be a replacement for vmalloc. If compiled with
 * EXA_KMEMTRACE defined, this function will be able to generate
 * statistics on memory allocation.
 * \param[in] size: number of bytes to be allocated.
 * \return a pointer to the allocated memory.
 * \sa exa_vfree
 */

/** \def exa_vfree
 * Intended to be a replacement for vfree.
 * \param[in] ptr: block of memory to be released. It must be a pointer
 * to memory allocated with exa_vmalloc().
 * \sa exa_vmalloc
 */

#ifdef EXA_KMEMTRACE

#define exa_kmalloc(size, priority) \
  exa_kmalloc_trace(size, priority, __FILE__, __LINE__)
#define exa_kfree(ptr) \
  exa_kfree_trace(ptr, __FILE__, __LINE__)

#define exa_vmalloc(size) \
  exa_vmalloc_trace(size, __FILE__, __LINE__)
#define exa_vfree(ptr) \
  exa_vfree_trace(ptr, __FILE__, __LINE__)


void *	exa_kmalloc_trace(size_t size, int priority, const char *file,
		unsigned int line);
void	exa_kfree_trace(void *ptr, const char *file, unsigned int line);
void *	exa_vmalloc_trace(unsigned long, const char *file, unsigned int line);
void	exa_vfree_trace(void *ptr, const char *file, unsigned int line);

void exa_meminfo(const char *descr, exa_meminfo_level_t level);

#else

#define exa_kmalloc(size, priority)	kmalloc(size, priority)
#define exa_kfree(ptr)			kfree(ptr)
#define exa_vmalloc(size)		vmalloc(size)
#define exa_vfree(ptr)			vfree(ptr)
#define exa_meminfo(descr, log_level)	/* empty */

#endif /* EXA_KMEMTRACE */

#else /* __KERNEL__ */

#include <stdlib.h>

/** \def exa_malloc
 * Intended to be a replacement for malloc. If compiled with
 * EXA_MEMTRACE defined, this function will be able to generate
 * statistics on memory allocation.
 * \param[in] size: number of bytes to be allocated.
 * \return a pointer to the allocated memory.
 * \sa exa_free
 */

/** \def exa_free
 * Intended to be a replacement for free.
 * \param[in] ptr: block of memory to be released. It must be a pointer
 * to memory allocated with exa_malloc().
 * \sa exa_malloc
 */

/** \def exa_calloc
 * Intended to be a replacement for calloc. If compiled with
 * EXA_MEMTRACE defined, this function will be able to generate
 * statistics on memory allocation.
 * \param[in] nmemb: number of elements to be allocated.
 * \param[in] size: size in bytes of elements to be allocated.
 * \return a pointer to the allocated memory.
 * \sa exa_free
 */

/** \def exa_meminfo
 * Display statistics on memory allocations. No-op if EXA_MEMTRACE is not
 * defined.
 * \param[in] descr	Short string describing what statistics are
 *			displayed.
 * \param[in] summary	If true, display only a summary.
 */

#ifdef EXA_MEMTRACE

#define exa_malloc(size) \
  exa_malloc_trace(size, __FILE__, __LINE__)
#define exa_strdup(string) \
  exa_strdup_trace(string, __FILE__, __LINE__)
#define exa_realloc(ptr, size)			\
  exa_realloc_trace(ptr, size, __FILE__, __LINE__)
#define exa_free(ptr) \
  exa_free_trace(ptr, __FILE__, __LINE__)
#define exa_calloc(nmemb, size)			\
  exa_calloc_trace(nmemb, size, __FILE__, __LINE__)

#ifdef __cplusplus
extern "C" {
#endif

void *	exa_malloc_trace(size_t size, const char *file, unsigned int line);
void *	exa_realloc_trace(void *ptr, size_t size, const char *file,
		unsigned int line);
void	exa_free_trace(void *ptr, const char *file, unsigned int line);
void *	exa_calloc_trace(size_t nmemb, size_t size, const char *file,
		unsigned int line);

char *	exa_strdup_trace(const char *s, const char *file, unsigned int line);

void exa_meminfo(const char *descr, exa_meminfo_level_t level);

#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
#include <new>
#include <exception>

inline void* operator new (size_t size, const char *file, int line)
{
  void *p=exa_malloc_trace(size, file, line);
  if (p==0)
    throw std::bad_alloc(); /* seems to be standard behaviour */
  return p;
}

inline void* operator new[] (size_t size, const char *file, int line)
{
  void *p=exa_malloc_trace(size, file, line);
  if (p==0)
    throw std::bad_alloc(); /* seems to be standard behaviour */
  return p;
}
#define exa_new new(__FILE__, __LINE__)

inline void operator delete (void *p, const char *file, int line)
{
  exa_free_trace(p, file, line );
}

inline void operator delete[] (void *p, const char *file, int line)
{
  exa_free_trace(p, file, line );
}
#define exa_delete delete(__FILE__, __LINE__)

#endif

#else

#define exa_malloc(size)		malloc(size)
#define exa_realloc(ptr, size)		realloc(ptr, size)
#define exa_free(ptr)			free(ptr)
#define exa_calloc(nmemb, size)		calloc(nmemb, size)

#define	exa_strdup(s)			strdup(s)

#define exa_meminfo(descr, log_level)	/* empty */

#endif /* EXA_MEMTRACE */

#endif /* __KERNEL__ */

#endif /* H_EXA_MEMTRACE */
