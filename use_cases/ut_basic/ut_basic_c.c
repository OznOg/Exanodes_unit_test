/*
 * Copyright 2002, 2015 Seanodes Ltd http://www.seanodes.com. All rights
 * reserved and protected by French, UK, U.S. and other countries' copyright laws.
 * This file is part of Exanodes Unit test library and is subject to the terms
 * and conditions defined in the LICENSE file which is present in the root
 * directory of the project.
 */

/**
 * The purpose of this very basic unit test is to ensure that the unit
 * test library behaves correctly on all platforms.
 * This unit test does not test any module.
 */


#include "../../src/unit_testing.h"
#include <stdlib.h>  /* for NULL */
#include <limits.h>  /* for INT_MIN, INT_MAX and friends */
#include <float.h>   /* for FLT_MIN, FLT_MAX, DBL_MIN, DBL_MAX */

#ifdef WIN32
#ifndef bool
#define bool    _Bool
#define true    1
#define false   0
#endif
#else
#include <stdbool.h>
#endif

/* FIXME: Definition of a portable sleep() function.
 * Maybe we should use libOS instead. For now, I prefer to hardcode a
 * sleep() function to reduce the dependency to libOS.
 */
#ifdef WIN32
#include <winbase.h>
#define my_sleep(N) Sleep(N * 1000)
#else
#include <unistd.h>  /* sleep() */
#define my_sleep(N) sleep(N)
#endif

UT_SECTION(UT_ASSERT)

ut_test(ut_assert_constants)
{
    UT_ASSERT(0 == 0);
    UT_ASSERT(1);
    UT_ASSERT(1 == 1);
    UT_ASSERT(1 != 2);
    UT_ASSERT(1 < 2);
    UT_ASSERT(1 && 1);
    UT_ASSERT(0 || 1);
    UT_ASSERT(0 ^ 1);
    UT_ASSERT(! 0);
}


ut_test(ut_assert_null)
{
    UT_ASSERT(! NULL);
    UT_ASSERT(NULL == NULL);
}


ut_test(ut_assert_bool)
{
    UT_ASSERT(! false);
    UT_ASSERT(false == false);
    UT_ASSERT(true);
    UT_ASSERT(true == true);
    UT_ASSERT(true != false);
    UT_ASSERT(true && true);
    UT_ASSERT(false || true);
}


UT_SECTION(UT_ASSERT_EQUAL)

ut_test(ut_assert_equal_constants)
{
    UT_ASSERT_EQUAL(0, 0);
    UT_ASSERT_EQUAL(1, 1);
    UT_ASSERT_EQUAL(2, 1 + 1);
    UT_ASSERT_EQUAL(2, 2 * 1);
    UT_ASSERT_EQUAL(2, 1 << 1);
}


ut_test(ut_assert_equal_bool)
{
    UT_ASSERT_EQUAL(true, true);
    UT_ASSERT_EQUAL(false, false);
    UT_ASSERT_EQUAL(true, !false);
}


ut_test(ut_assert_equal_signed_char)
{
    /* signed char, signed char: zero */
    {
        signed char a = 0;
        signed char b = 0;
        UT_ASSERT_EQUAL(a, b);
    }
    /* signed char, signed char: positive values */
    {
        signed char a = 1;
        signed char b = 1;
        UT_ASSERT_EQUAL(a, b);
    }
    /* signed char, signed char: maximum values */
    {
        signed char a = SCHAR_MAX;
        signed char b = SCHAR_MAX;
        UT_ASSERT_EQUAL(a, b);
    }
    /* signed char, signed char: negative values */
    {
        int a = -1;
        int b = -1;
        UT_ASSERT_EQUAL(a, b);
    }
    /* signed char, signed char: minimum values */
    {
        int a = SCHAR_MIN;
        int b = SCHAR_MIN;
        UT_ASSERT_EQUAL(a, b);
    }
}


ut_test(ut_assert_equal_unsigned_char)
{
    /* unsigned char, unsigned char: zero */
    {
        signed char a = 0;
        signed char b = 0;
        UT_ASSERT_EQUAL(a, b);
    }
    /* unsigned char, unsigned char: positive values */
    {
        signed char a = 1;
        signed char b = 1;
        UT_ASSERT_EQUAL(a, b);
    }
    /* unsigned char, unsigned char: maximum values */
    {
        signed char a = UCHAR_MAX;
        signed char b = UCHAR_MAX;
        UT_ASSERT_EQUAL(a, b);
    }
}


ut_test(ut_assert_equal_int)
{
    /* int, int: zero */
    {
        int a = 0;
        int b = 0;
        UT_ASSERT_EQUAL(a, b);
    }
    /* int, int: positive values */
    {
        int a = 1;
        int b = 1;
        UT_ASSERT_EQUAL(a, b);
    }
    /* int, int: maximum values */
    {
        int a = INT_MAX;
        int b = INT_MAX;
        UT_ASSERT_EQUAL(a, b);
    }
    /* int, int: negative values */
    {
        int a = -1;
        int b = -1;
        UT_ASSERT_EQUAL(a, b);
    }
    /* int, int: minimum values */
    {
        int a = INT_MIN;
        int b = INT_MIN;
        UT_ASSERT_EQUAL(a, b);
    }
}


ut_test(ut_assert_equal_unsigned_int)
{
    /* unsigned int, unsigned int: zero */
    {
        unsigned int a = 0;
        unsigned int b = 0;
        UT_ASSERT_EQUAL(a, b);
    }
    /* unsigned int, unsigned int: positive values */
    {
        unsigned int a = 1;
        unsigned int b = 1;
        UT_ASSERT_EQUAL(a, b);
    }
    /* unsigned int, unsigned int: maximum values */
    {
        unsigned int a = UINT_MAX;
        unsigned int b = UINT_MAX;
        UT_ASSERT_EQUAL(a, b);
    }
}


ut_test(ut_assert_equal_long)
{
    /* long, long: zero */
    {
        long a = 0;
        long b = 0;
        UT_ASSERT_EQUAL(a, b);
    }
    /* long, long: positive values */
    {
        long a = 1;
        long b = 1;
        UT_ASSERT_EQUAL(a, b);
    }
    /* long, long: maximum values */
    {
        long a = LONG_MAX;
        long b = LONG_MAX;
        UT_ASSERT_EQUAL(a, b);
    }
    /* long, long: negative values */
    {
        long a = -1;
        long b = -1;
        UT_ASSERT_EQUAL(a, b);
    }
    /* long, long: minimum values */
    {
        long a = LONG_MIN;
        long b = LONG_MIN;
        UT_ASSERT_EQUAL(a, b);
    }
}

ut_test(ut_assert_equal_unsigned_long)
{
    /* unsigned long, unsigned long: zero */
    {
        unsigned long a = 0;
        unsigned long b = 0;
        UT_ASSERT_EQUAL(a, b);
    }
    /* unsigned long, unsigned long: positive values */
    {
        unsigned long a = 1;
        unsigned long b = 1;
        UT_ASSERT_EQUAL(a, b);
    }
    /* unsigned int, unsigned int: maximum values */
    {
        unsigned long a = ULONG_MAX;
        unsigned long b = ULONG_MAX;
        UT_ASSERT_EQUAL(a, b);
    }
}


ut_test(ut_assert_equal_float)
{
    /* float, float: zero */
    {
        float a = 0.0f;
        float b = 0.0f;
        UT_ASSERT_EQUAL(a, b);
    }
    /* float, float: positive values */
    {
        float a = 1.0f;
        float b = 1.0f;
        UT_ASSERT_EQUAL(a, b);
    }
    /* float, float: maximum values */
    {
        float a = FLT_MAX;
        float b = FLT_MAX;
        UT_ASSERT_EQUAL(a, b);
    }
    /* float, float: negative values */
    {
        float a = -1.0f;
        float b = -1.0f;
        UT_ASSERT_EQUAL(a, b);
    }
    /* float, float: minimum values */
    {
        float a = FLT_MIN;
        float b = FLT_MIN;
        UT_ASSERT_EQUAL(a, b);
    }
}


ut_test(ut_assert_equal_double)
{
    /* double, double: zero */
    {
        double a = 0.0;
        double b = 0.0;
        UT_ASSERT_EQUAL(a, b);
    }
    /* double, double: positive values */
    {
        double a = 1.0;
        double b = 1.0;
        UT_ASSERT_EQUAL(a, b);
    }
    /* double, double: maximum values */
    {
        double a = DBL_MAX;
        double b = DBL_MAX;
        UT_ASSERT_EQUAL(a, b);
    }
    /* double, double: negative values */
    {
        double a = -1.0;
        double b = -1.0;
        UT_ASSERT_EQUAL(a, b);
    }
    /* double, double: minimum values */
    {
        double a = DBL_MIN;
        double b = DBL_MIN;
        UT_ASSERT_EQUAL(a, b);
    }
}


UT_SECTION(UT_ASSERT_EQUAL_STR)

ut_test(ut_assert_equal_str)
{
    char foo[] = "foo";

    UT_ASSERT_EQUAL_STR(foo, foo);
    UT_ASSERT_EQUAL_STR(foo, "foo");
    UT_ASSERT_EQUAL_STR("foo", "foo");
}


UT_SECTION(UT_ASSERT_NOT_EQUAL_STR)

ut_test(ut_assert_not_equal_str)
{
    char foo[] = "foo";
    char bar[] = "bar";

    UT_ASSERT_NOT_EQUAL_STR(foo, bar);
    UT_ASSERT_NOT_EQUAL_STR(foo, "bar");
    UT_ASSERT_NOT_EQUAL_STR("foo", "bar");
    UT_ASSERT_NOT_EQUAL_STR(foo, "foo\n");
    UT_ASSERT_NOT_EQUAL_STR(foo, "foo ");
}


UT_SECTION(UT_FAIL)

/* FIXME: I don't know if this is a good idea to have a test fail. */
ut_test(ut_fail)
{
    ut_printf("[Info] Don't worry, this test MUST fail!");
    UT_FAIL();
}


UT_SECTION(ut_timeout)

ut_test(ut_timeout_pass) __ut_timeout(5s)
{
    my_sleep(4);
    UT_ASSERT(true);
}

ut_test(ut_timeout_fail) __ut_timeout(5s)
{
    ut_printf("[Info] Don't worry, this test MUST fail!");
    my_sleep(6);
    UT_ASSERT(true);
}


UT_SECTION(ut_lengthy)

ut_test(ut_lengthy) __ut_lengthy
{
    ut_printf("[Info] Next time, skip this test by providing '-s' as an option");
    my_sleep(5);
    UT_ASSERT(true);
}

UT_SECTION(ut_expect)

ut_test(get_unexpected_signal) __ut_signal(SIGABRT)
{
    ut_printf("[Info] Don't worry, this test MUST fail!");
    raise(SIGSEGV);
}

ut_test(expect_signal_get_none) __ut_signal(SIGUSR1)
{
    ut_printf("[Info] Don't worry, this test MUST fail!");
}

ut_test(get_expected_signal) __ut_signal(SIGABRT)
{
    assert(false);
}

ut_test(get_special_assertion_signal) __ut_signal(ASSERT)
{
    assert(false);
}

UT_SECTION(ut_setup_and_cleanup)

static int foo = 0;

ut_setup()
{
    foo = 42;
}

ut_cleanup()
{
    UT_ASSERT_EQUAL(42, foo);
    foo = 0;
}

ut_test(ut_setup_and_cleanup)
{
    UT_ASSERT_EQUAL(42, foo);
}
