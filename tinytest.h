#ifndef TINY_TEST_H
#define TINY_TEST_H


#ifdef __cplusplus
	extern "C" {
#endif

#define ENABLE_TEST
// #define PRINT_MINIMAL
#define TEST_DIVIDER_LENGTH 		(60)

#if defined(ENABLE_TEST)

#define DEBUG_THIS_FILE
#include "debug.h"

#if defined(PRINT_MINIMAL)
	#define TEST_VERBOSE(x)
#else
	#define TEST_VERBOSE(x)		x
#endif

#if defined(ARDUINO) && defined(ARDUINO_ARCH_ESP8266)
	#define ESP8266_ARDUINO_ONLY(x) 	x
#else
	#define ESP8266_ARDUINO_ONLY(x)
#endif

typedef void (*test_proto)(void);

static unsigned char passed_test = 0;
static unsigned char failed_test = 0;
static unsigned char last_test_status = 0;
static unsigned long total_time = 0;

static unsigned long (*clock_source)(void);

static void run_test(test_proto test);
static unsigned char check(int expression);

#define CLOCK_UNIT			"ms"
#define CLOCK_SOURCE 		clock_source
#define CLOCK				(*CLOCK_SOURCE)

#if !defined(ARDUINO)
#define SET_CLOCK_SOURCE(source)
#else
#define SET_CLOCK_SOURCE(source) 	clock_source = source
#endif

#define ADD_TINY_TEST(test_name) 	static void test_name(void)


#define RUN_TINY_TEST(test_func) 	PLACE(\
										ESP8266_ARDUINO_ONLY(yield());\
										TEST_VERBOSE(DEBUG_DIVIDER("*", TEST_DIVIDER_LENGTH));\
										DEBUG_PRINT_MSG(COLOR_CYAN, RUN, #test_func "()");\
										run_test(&test_func);\
										ESP8266_ARDUINO_ONLY(yield());\
									)

#define TINY_TEST_REPORT() 	PLACE(\
								TEST_VERBOSE(DEBUG_DIVIDER("=", TEST_DIVIDER_LENGTH));\
								DEBUG_PRINT_HEADER(COLOR_YELLOW, REPORT);\
								DEBUG("%d Test(s), %d Passed, %d Failed ", (passed_test + failed_test), passed_test, failed_test);\
								if(clock_source) DEBUG("( %u " CLOCK_UNIT ")", total_time);\
								DEBUG(NEWLINE);\
								TEST_VERBOSE(DEBUG_DIVIDER("=", TEST_DIVIDER_LENGTH));\
							)

#define ADD_TEST_SUITE(tiny_test_suit) 	static void tiny_test_suit(void)

#define RUN_TEST_SUITE(tiny_test_suit) 	tiny_test_suit(); 

#define ASSERT_ARRAY(ARRAY_1, ARRAY_2, LENGTH, TYPE_SIZE)	PLACE(\
																match_array((uint8_t*)ARRAY_1, (uint8_t*)ARRAY_2, LENGTH, TYPE_SIZE);\
																DEBUG_LN(#ARRAY_1 " , " #ARRAY_2);\
																if(!last_test_status) return;\
															)

#define ASSERT_TEST_RESULT(expression) 	PLACE(\
											check(expression);\
											TEST_VERBOSE(DEBUG_LN(#expression));\
											if(!last_test_status) return;\
										)

static void run_test(test_proto test){
	unsigned long start_time = 0;
	if(CLOCK_SOURCE) start_time = CLOCK();
	test();
	if(CLOCK_SOURCE) total_time = total_time + (CLOCK() - start_time);

	if(last_test_status){
		DEBUG_PRINT_MSG(COLOR_GREEN, RESULT, "Test Passed");
		passed_test++;
	} else{
		DEBUG_PRINT_MSG(COLOR_RED, RESULT, "Test Failed" BELL);
		failed_test++;
	}
	TEST_VERBOSE(DEBUG_DIVIDER("*", TEST_DIVIDER_LENGTH));
	PRINT(NEWLINE);
}

static unsigned char check(int expression){
	if(expression){
		TEST_VERBOSE(DEBUG_PRINT_HEADER(COLOR_GREEN, OK));
		last_test_status = 1;
	} else{
		TEST_VERBOSE(DEBUG_PRINT_HEADER(COLOR_RED, ERROR));
		last_test_status = 0;
	}
	return last_test_status;
}

static uint32_t match_array(uint8_t * array_1, uint8_t * array_2, uint32_t array_length, uint8_t type_size) {
    for(uint32_t i = 0; i < (array_length * type_size); i++) {
        if(array_1[i] != array_2[i]) {
        	last_test_status = 0;
            break;
        } else{
    		last_test_status = 1;   	
        }
    }
    if(last_test_status){
		DEBUG_PRINT_HEADER(COLOR_GREEN, MATCHED);
    } else{
		DEBUG_PRINT_HEADER(COLOR_RED, DIFFER);
    }
    return array_length;
}
#else
#include "debug.h"
#define SET_CLOCK_SOURCE(source)
#define ADD_TINY_TEST(test_name)			void test_name(void)
#define RUN_TINY_TEST(test_func)
#define TINY_TEST_REPORT()
#define ADD_TEST_SUITE(tiny_test_suit)		void tiny_test_suit(void)
#define RUN_TEST_SUITE(tiny_test_suit)
#define ASSERT_ARRAY(ARRAY_1, ARRAY_2, LENGTH, TYPE_SIZE)
#define ASSERT_TEST_RESULT(expression)
#endif

#ifdef __cplusplus
}
#endif

#endif /* TINY_TEST_H */