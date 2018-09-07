#include "tinytest.h"
// #include "debug.h"

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

ADD_TINY_TEST(check_variable_once_more){
	int i = 0;
	ASSERT_TEST_RESULT(i == 99);
}

ADD_TINY_TEST(other_test){
	int i = 0;
	ASSERT_TEST_RESULT(i == 99);
}

ADD_TINY_TEST(few_other_test){
	int i = 99;
	ASSERT_TEST_RESULT(i == 99);
}

ADD_TEST_SUITE(test_suit){
	RUN_TINY_TEST(check_variable);
	RUN_TINY_TEST(check_equal_variable);
	RUN_TINY_TEST(check_variable_more);
	RUN_TINY_TEST(check_variable_once_more);
	RUN_TINY_TEST(other_test);
	RUN_TINY_TEST(few_other_test);
}

int main(int argc, char const *argv[])
{	
	ATTACH_DEBUG_STREAM(&Serial);
	DEBUG_OK("printf Example");
	DEBUG_OK("printf_P Example : %d", 100);
	RUN_TEST_SUITE(test_suit);
	TINY_TEST_REPORT();
}