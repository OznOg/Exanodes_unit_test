#
# Copyright 2002, 2015 Seanodes Ltd http://www.seanodes.com. All rights
# reserved and protected by French, UK, U.S. and other countries' copyright laws.
# This file is part of Exanodes Unit test library and is subject to the terms
# and conditions defined in the LICENSE file which is present in the root
# directory of the project.
#

check_PROGRAMS = \
	ut_basic_c \
	ut_basic_cplusplus

TESTS = $(check_PROGRAMS)

noinst_PROGRAMS = \
	ut_basic_c \
	ut_basic_cplusplus

ut_basic_c_SOURCES = \
	ut_basic_c.c

ut_basic_cplusplus_SOURCES = \
	ut_basic_cplusplus.cpp

AM_CFLAGS = \
	-I@top_srcdir@/src

AM_CPPFLAGS = \
	-I@top_srcdir@/src

ut_basic_c.o: ut_basic_c.c
	echo $(COMPILE) && export UT_BUILD_TEMPLATE=@top_srcdir@/src/ut_build_template.c && \
	@top_srcdir@/src/ut_build $(COMPILE) -o $@ $<

ut_basic_cplusplus.o: ut_basic_cplusplus.cpp
	echo $(CXXCOMPILE) && export UT_BUILD_TEMPLATE=@top_srcdir@/src/ut_build_template.c && \
	@top_srcdir@/src/ut_build $(CXXCOMPILE) -o $@ $<
