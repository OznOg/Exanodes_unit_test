/*
 * Copyright 2002, 2015 Seanodes Ltd http://www.seanodes.com. All rights
 * reserved and protected by French, UK, U.S. and other countries' copyright laws.
 * This file is part of Exanodes Unit test library and is subject to the terms
 * and conditions defined in the LICENSE file which is present in the root
 * directory of the project.
 */

#define UT_REALLY_ASSERT()

#include "../src/unit_testing.h"
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>


typedef enum
{
    __UT_RESULT_FAILED,
    __UT_RESULT_PASSED,
    __UT_RESULT_SKIPPED
} ut_result_t;



char buffer[1024 * 32];
int exit_code = 0;


void ut_end(int successful)
{
    exit_code = successful ? 0 : 1;
}


/* fake ut_printf definition to redirect to a buffer */
void ut_printf(const char *format, ...)
{
    va_list al;

    va_start(al, format);
    vsprintf(buffer, format, al);
    va_end(al);
}


int ut_test_assert_equal_macro()
{
    char expected_assert_msg[1024 * 32];
    /* int, int */
    {
	int e = 12;
	int v = 12;
	exit_code = 0;
	UT_ASSERT_EQUAL(e, v);
	assert(exit_code == 0);
    }
    {
	const char* assert_failed_format =
	    "Assertion failed (%s:%d): expected %d got %d";
	int e = 12;
	int v = -178;
	exit_code = 0;
	UT_ASSERT_EQUAL(e, v);
	sprintf(expected_assert_msg, assert_failed_format, __FILE__, __LINE__-1, e, v);
	assert(exit_code == 1);

 	if (strcmp(expected_assert_msg, buffer))
	{
	    printf("Messages do not matches :\n expected : '%s'\n got      : '%s'\n",
		   expected_assert_msg, buffer);
	    return 1;
	}
    }

    /* unsigned int, unsigned int */
    {
	unsigned int e = 12;
	unsigned int v = 12;
	exit_code = 0;
	UT_ASSERT_EQUAL(e, v);
	assert(exit_code == 0);
    }
    {
	const char* assert_failed_format =
	    "Assertion failed (%s:%d): expected %u got %u";
	unsigned int e = 12;
	unsigned int v = -155;
	exit_code = 0;
	UT_ASSERT_EQUAL(e, v);
	sprintf(expected_assert_msg, assert_failed_format, __FILE__, __LINE__-1, e, v);
	assert(exit_code == 1);

 	if (strcmp(expected_assert_msg, buffer))
	{
	    printf("Messages do not matches :\n expected : '%s'\n got      : '%s'\n",
		   expected_assert_msg, buffer);
	    return 1;
	}
    }

    /* TODO : test other types output in the same spirit
       note that for decimal types, even if a low precision type is used
       for typing tested/expected values, always long double format will be used */

    return 0;
}


/* TODO : test with fake functions, that macros evaluate functions once
   if used as macro parameters */


#define PRINT_STATUS(fn, nb_failures)					\
    do									\
    {									\
	int __status = (fn);						\
	printf(" %s %s\n", #fn, (__status != 0) ? "failed" : "success");	\
	if (__status != 0) ++nb_failures;				\
    } while (false)



int main()
{
    int nb_failed = 0;
    PRINT_STATUS(ut_test_assert_equal_macro(), nb_failed);
    return nb_failed != 0;
}
