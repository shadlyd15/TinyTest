#include "tinytest.h"
// #include "debug.h"

ADD_TINY_TEST(test_0){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 0);
}

ADD_TINY_TEST(test_1){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 1);
}

ADD_TINY_TEST(test_2){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 2);
}

ADD_TINY_TEST(test_3){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 3);
}

ADD_TINY_TEST(test_4){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 4);
}

ADD_TINY_TEST(test_5){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 5);
}

ADD_TINY_TEST(test_6){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 6);
}

ADD_TINY_TEST(test_7){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 7);
}

ADD_TINY_TEST(test_8){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 8);
}

ADD_TINY_TEST(test_9){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 9);
}

ADD_TINY_TEST(test_10){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 10);
}

ADD_TINY_TEST(test_11){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 11);
}

ADD_TINY_TEST(test_12){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 12);
}

ADD_TINY_TEST(test_13){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 13);
}

ADD_TINY_TEST(test_14){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 14);
}

ADD_TINY_TEST(test_15){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 15);
}

ADD_TINY_TEST(test_16){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 16);
}

ADD_TINY_TEST(test_17){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 17);
}

ADD_TINY_TEST(test_18){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 18);
}

ADD_TINY_TEST(test_19){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 19);
}

ADD_TINY_TEST(test_20){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 20);
}

ADD_TINY_TEST(test_21){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 21);
}

ADD_TINY_TEST(test_22){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i == 22);
}

ADD_TINY_TEST(test_23){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 23);
}

ADD_TINY_TEST(test_24){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 24);
}

ADD_TINY_TEST(test_25){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i == 25);
}

ADD_TINY_TEST(test_26){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i == 26);
}

ADD_TINY_TEST(test_27){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 27);
}

ADD_TINY_TEST(test_28){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 28);
}

ADD_TINY_TEST(test_29){
  int i = rand()%50;
  ASSERT_TEST_RESULT(i != 29);
}
ADD_TEST_SUITE(test_suit){
	RUN_TINY_TEST(test_0);
	RUN_TINY_TEST(test_1);
	RUN_TINY_TEST(test_2);
	RUN_TINY_TEST(test_3);
	RUN_TINY_TEST(test_4);
	RUN_TINY_TEST(test_5);
	RUN_TINY_TEST(test_6);
	RUN_TINY_TEST(test_7);
	RUN_TINY_TEST(test_8);
	RUN_TINY_TEST(test_9);
	RUN_TINY_TEST(test_10);
	RUN_TINY_TEST(test_11);
	RUN_TINY_TEST(test_12);
	RUN_TINY_TEST(test_13);
	RUN_TINY_TEST(test_14);
	RUN_TINY_TEST(test_15);
	RUN_TINY_TEST(test_16);
	RUN_TINY_TEST(test_17);
	RUN_TINY_TEST(test_18);
	RUN_TINY_TEST(test_19);
	RUN_TINY_TEST(test_20);
	RUN_TINY_TEST(test_21);
	RUN_TINY_TEST(test_22);
	RUN_TINY_TEST(test_23);
	RUN_TINY_TEST(test_24);
	RUN_TINY_TEST(test_25);
	RUN_TINY_TEST(test_26);
	RUN_TINY_TEST(test_27);
	RUN_TINY_TEST(test_28);
	RUN_TINY_TEST(test_29);
}

void setup(){
	SET_CLOCK_SOURCE(&millis);
	Serial.begin(19200);
	ATTACH_DEBUG_STREAM(&Serial);
	DEBUG_OK("printf Example");
	DEBUG_OK("printf_P Example : %d", 100);
	RUN_TEST_SUITE(test_suit);
	TINY_TEST_REPORT();
	// DEBUG_TRACE();
}

void loop(){

}
