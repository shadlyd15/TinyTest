#include "tinytest.h"
// #include "arduino_printf_support.h"

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

void setup(){
	Serial.begin(19200);
	ATTACH_DEBUG_STREAM(&Serial);
	DEBUG_OK("Tiny Test Framework Example");
	RUN_TEST_SUITE(test_suit);
	TINY_TEST_REPORT();
}

void loop(){

}
