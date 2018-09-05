#ifndef TINY_TEST_H
#define TINY_TEST_H

#include "debug.h"

#ifdef __cplusplus
	extern "C" {
#endif

static int last_test_status = 0;

static int passed_test = 0;
static int failed_test = 0;

#define ADD_TINY_TEST(test_name) static void test_name(void)
#define RUN_TINY_TEST(test_name) 	PLACE(\
										DEBUG_NEWLINE();\
										DEBUG_PRINT_MSG(COLOR_YEL, RUN, #test_name);\
										test_name();\
										if(last_test_status){\
											DEBUG_PRINT_MSG(COLOR_GRN, TEST PASSED, #test_name"()");\
											passed_test++;\
										} else{\
											DEBUG_PRINT_MSG(COLOR_RED, TEST FAILED, #test_name"()");\
											failed_test++;\
										}\
									)

#define TINY_TEST_REPORT() 	PLACE(\
								DEBUG_NEWLINE();\
								DEBUG_PRINT_HEADER(COLOR_YEL, TEST REPORT);\
								DEBUG_LN("%d Tests, %d Passed, %d Failed" NEWLINE, (passed_test + failed_test), passed_test, failed_test);\
							)

#define ADD_TEST_SUITE(tiny_test_suit) 	static void tiny_test_suit(void)

#define RUN_TEST_SUITE(tiny_test_suit) tiny_test_suit(); 

#define TINY_ASSERT_EQUAL(expression) PLACE(\
			if(!(expression)){\
				DEBUG_PRINT_HEADER(COLOR_RED, ASSERTION ERROR);\
			} else{\
				DEBUG_PRINT_HEADER(COLOR_GRN, ASSERTION OK);\
			}\
			DEBUG_P(#expression);\
			DEBUG_NEWLINE();\
		)

#define ASSERT_TEST_RESULT(expression) PLACE(\
			if(!(expression)){\
				DEBUG_PRINT_HEADER(COLOR_RED, ASSERTION ERROR);\
				last_test_status = 0;\
			} else{\
				DEBUG_PRINT_HEADER(COLOR_GRN, ASSERTION OK);\
				last_test_status = 1;\
			}\
			DEBUG_P(#expression);\
			DEBUG_NEWLINE();\
		)

#ifdef __cplusplus
}
#endif

#endif /* TINY_TEST_H */