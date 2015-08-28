#
# Copyright 2002, 2015 Seanodes Ltd http://www.seanodes.com. All rights
# reserved and protected by French, UK, U.S. and other countries' copyright laws.
# This file is part of Exanodes Unit test library and is subject to the terms
# and conditions defined in the LICENSE file which is present in the root
# directory of the project.
#

noinst_LTLIBRARIES = libexa_nodeset.la

check_PROGRAMS = ut_nodeset

TESTS = $(check_PROGRAMS)


libexa_nodeset_la_SOURCES = \
	exa_nodeset.c       \
	exa_nodeset.h       \
	common.h            \
	exa_byteorder.h     \
	exa_constants.h     \
	exa_inttypes.h      \
        exa_memtrace.h      \
	exa_kernel.h

noinst_PROGRAMS = \
	ut_nodeset

ut_nodeset_SOURCES = \
	ut_nodeset.c

AM_CFLAGS = \
        -I@top_srcdir@/src

ut_%.o: ut_%.c
	echo $(COMPILE) && export UT_BUILD_TEMPLATE=@top_srcdir@/src/ut_build_template.c && \
	@top_srcdir@/src/ut_build $(COMPILE) -o $@ $<


ut_nodeset_LDADD =             \
	libexa_nodeset.la      \
	-L@top_builddir@/src

