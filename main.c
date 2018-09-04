#include <stdio.h>
#include <stdint.h>

#include "tinytest.h"

ADD_TINY_TEST(check_equal_variable){
	int i = 0;
	ASSERT_TEST_RESULT(i == 0);
}

ADD_TINY_TEST(check_variable){
	int i = 0;
	ASSERT_TEST_RESULT(i == 6);
}

ADD_TINY_TEST(check_variable_more){
	int i = 0;
	ASSERT_TEST_RESULT(i == 99);
}

ADD_TEST_SUITE(test_suit){
	RUN_TINY_TEST(check_variable);
	RUN_TINY_TEST(check_equal_variable);
	RUN_TINY_TEST(check_variable_more);
}

int main(int argc, char const *argv[]){
	DEBUG_OK("Tiny Test Framework Example");
	RUN_TEST_SUITE(test_suit);
	TINY_TEST_REPORT();
	return 0;
}