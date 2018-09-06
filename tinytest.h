#ifndef TINY_TEST_H
#define TINY_TEST_H

#include "debug.h"

#ifdef __cplusplus
	extern "C" {
#endif

#if defined(ARDUINO)
	#define CLOCK_SOURCE				millis
	#define CLOCK_UNIT					"ms"
#endif

#define DEBUG_DIVIDER_LENGTH 		(60)

static unsigned char passed_test = 0;
static unsigned char failed_test = 0;
static unsigned char last_test_status = 0;
static unsigned long total_time = 0;

#define ADD_TINY_TEST(test_name) 	static void test_name(void)
#define RUN_TINY_TEST(test_name) 	PLACE(\
										unsigned long start_time = CLOCK_SOURCE();\
                                		DEBUG_P(NEWLINE);\
										DEBUG_DIVIDER("-", DEBUG_DIVIDER_LENGTH);\
										DEBUG_PRINT_MSG(COLOR_YELLOW, TEST, #test_name "()");\
										test_name();\
										if(last_test_status){\
											DEBUG_PRINT_MSG(COLOR_GREEN, TEST PASSED, #test_name);\
											passed_test++;\
										} else{\
											DEBUG_PRINT_MSG(COLOR_RED, TEST FAILED, #test_name);\
											failed_test++;\
										}\
										total_time = total_time + (CLOCK_SOURCE() - start_time);\
										DEBUG_DIVIDER("-", DEBUG_DIVIDER_LENGTH);\
									)

#define TINY_TEST_REPORT() 	PLACE(\
                                DEBUG_P(NEWLINE);\
								DEBUG_DIVIDER("=", DEBUG_DIVIDER_LENGTH);\
								DEBUG_PRINT_HEADER(COLOR_YELLOW, REPORT);\
								DEBUG("%d", (passed_test + failed_test));\
								DEBUG_P(" Tests in ");\
								DEBUG("%d", total_time);\
								DEBUG_P(" " CLOCK_UNIT ", ");\
								DEBUG("%d", passed_test);\
								DEBUG_P(" Passed, ");\
								DEBUG("%d", failed_test);\
								DEBUG_P(" Failed ");\
								DEBUG_P(NEWLINE);\
								DEBUG_DIVIDER("=", DEBUG_DIVIDER_LENGTH);\
							)

#define ADD_TEST_SUITE(tiny_test_suit) 	static void tiny_test_suit(void)

#define RUN_TEST_SUITE(tiny_test_suit) 	tiny_test_suit(); 

#define TINY_ASSERT_EQUAL(expression) PLACE(\
			if(!(expression)){\
				DEBUG_PRINT_HEADER(COLOR_RED, ASSERTION ERROR);\
			} else{\
				DEBUG_PRINT_HEADER(COLOR_GREEN, ASSERTION OK);\
			}\
			DEBUG_LN(#expression);\
		)

#define ASSERT_TEST_RESULT(expression) PLACE(\
			if(!(expression)){\
				DEBUG_PRINT_HEADER(COLOR_RED, ASSERTION ERROR);\
				last_test_status = 0;\
			} else{\
				DEBUG_PRINT_HEADER(COLOR_GREEN, ASSERTION OK);\
				last_test_status = 1;\
			}\
			DEBUG_LN(#expression);\
		)

#ifdef __cplusplus
}
#endif

#endif /* TINY_TEST_H */