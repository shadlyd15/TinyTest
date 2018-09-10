#ifndef TINY_TEST_H
#define TINY_TEST_H

#include "debug.h"

#ifdef __cplusplus
	extern "C" {
#endif

#define DEBUG_DIVIDER_LENGTH 		(60)

typedef void (*test_proto)(void);

static unsigned char passed_test = 0;
static unsigned char failed_test = 0;
static unsigned char last_test_status = 0;
static unsigned long total_time = 0;

static unsigned long (*clock_source)(void);

static void run_test(test_proto test);
static unsigned char check(int expression);

#define CLOCK				(*clock_source)
#define CLOCK_SOURCE 		clock_source
#define CLOCK_UNIT			"ms"

#define SET_CLOCK_SOURCE(source) 	clock_source = source
#define ADD_TINY_TEST(test_name) 	static void test_name(void)


#define RUN_TINY_TEST(test_func) 	PLACE(\
										DEBUG_DIVIDER("*", DEBUG_DIVIDER_LENGTH);\
										DEBUG_PRINT_MSG(COLOR_CYAN, RUN, #test_func "()");\
										run_test(&test_func);\
									)

#define TINY_TEST_REPORT() 	PLACE(\
								DEBUG_DIVIDER("=", DEBUG_DIVIDER_LENGTH);\
								DEBUG_PRINT_HEADER(COLOR_YELLOW, REPORT);\
								DEBUG("%d Test(s), %d Passed, %d Failed ", (passed_test + failed_test), passed_test, failed_test);\
								if(clock_source) DEBUG("( %u " CLOCK_UNIT ")", total_time);\
								DEBUG(NEWLINE);\
								DEBUG_DIVIDER("=", DEBUG_DIVIDER_LENGTH);\
							)

#define ADD_TEST_SUITE(tiny_test_suit) 	static void tiny_test_suit(void)

#define RUN_TEST_SUITE(tiny_test_suit) 	tiny_test_suit(); 

#define TINY_ASSERT_EQUAL(expression) 	PLACE(\
											if(!(expression)){\
												DEBUG_PRINT_HEADER(COLOR_RED, ERROR);\
											} else{\
												DEBUG_PRINT_HEADER(COLOR_GREEN, OK);\
											}\
											DEBUG_LN(#expression);\
										)

#define ASSERT_TEST_RESULT(expression) 	PLACE(\
											check(expression);\
											DEBUG_LN(#expression);\
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
		DEBUG_PRINT_MSG(COLOR_RED, RESULT, "Test Failed");
		failed_test++;
	}
	DEBUG_DIVIDER("*", DEBUG_DIVIDER_LENGTH);
	PRINT(NEWLINE);
}

static unsigned char check(int expression){
	if(expression){
		DEBUG_PRINT_HEADER(COLOR_GREEN, OK);
		last_test_status = 1;
	} else{
		DEBUG_PRINT_HEADER(COLOR_RED, ERROR);
		last_test_status = 0;
	}
	return last_test_status;
}

#ifdef __cplusplus
}
#endif

#endif /* TINY_TEST_H */