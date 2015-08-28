/*
 * Copyright 2002, 2015 Seanodes Ltd http://www.seanodes.com. All rights
 * reserved and protected by French, UK, U.S. and other countries' copyright laws.
 * This file is part of Exanodes Unit test library and is subject to the terms
 * and conditions defined in the LICENSE file which is present in the root
 * directory of the project.
 */

/* These unit tests are C++ oriented. They should test features
 * provided by C++, but not available in C.
 */


#include "../../src/unit_testing.h"
#include <string>


UT_SECTION(UT_ASSERT_EQUAL_STR)

ut_test(ut_assert_equal_str_char)
{
    char foo[] = "foo";

    UT_ASSERT_EQUAL_STR(foo, foo);
    UT_ASSERT_EQUAL_STR(foo, "foo");
    UT_ASSERT_EQUAL_STR("foo", "foo");
}


ut_test(ut_assert_equal_str_string)
{
    std::string foo = "foo";

    UT_ASSERT_EQUAL_STR(foo, foo);
    UT_ASSERT_EQUAL_STR(foo, "foo");
    UT_ASSERT_EQUAL_STR("foo", "foo");
}


UT_SECTION(UT_ASSERT_NOT_EQUAL_STR)

ut_test(ut_assert_not_equal_str_char)
{
    char foo[] = "foo";
    char bar[] = "bar";

    UT_ASSERT_NOT_EQUAL_STR(foo, bar);
    UT_ASSERT_NOT_EQUAL_STR(foo, "bar");
    UT_ASSERT_NOT_EQUAL_STR("foo", "bar");
    UT_ASSERT_NOT_EQUAL_STR(foo, "foo\n");
    UT_ASSERT_NOT_EQUAL_STR(foo, "foo ");
}


ut_test(ut_assert_not_equal_str_string)
{
    std::string foo = "foo";
    std::string bar = "bar";

    UT_ASSERT_NOT_EQUAL_STR(foo, bar);
    UT_ASSERT_NOT_EQUAL_STR(foo, "bar");
    UT_ASSERT_NOT_EQUAL_STR("foo", "bar");
    UT_ASSERT_NOT_EQUAL_STR(foo, "foo\n");
    UT_ASSERT_NOT_EQUAL_STR(foo, "foo ");
}
