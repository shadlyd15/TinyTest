#ifndef TINY_TEST_H
#define TINY_TEST_H

#include "debug.h"

#ifdef __cplusplus
	extern "C" {
#endif

#define DEBUG_DIVIDER_LENGTH 		(50)

static unsigned char passed_test = 0;
static unsigned char failed_test = 0;
static unsigned char last_test_status = 0;
static unsigned long total_time = 0;

static unsigned long (*clock_source)(void);

typedef void (*test_proto)(void);

#define CLOCK				(*clock_source)
#define CLOCK_SOURCE 		clock_source
#define CLOCK_UNIT			"ms"

#define SET_CLOCK_SOURCE(source) 	clock_source = source;
#define ADD_TINY_TEST(test_name) 	static void test_name(void)

#define RUN_TINY_TEST(test_name) 	\
	DEBUG_P(NEWLINE);\
	DEBUG_DIVIDER("-", DEBUG_DIVIDER_LENGTH);\
	DEBUG_PRINT_MSG(COLOR_CYAN, RUN, #test_name "()");\
									print_result(&test_name)

static void print_result(test_proto test){
	unsigned long start_time = 0;
	if(CLOCK_SOURCE) start_time = CLOCK();
	test();
	if(last_test_status){
		DEBUG_PRINT_MSG(COLOR_GREEN, RESULT, "Passed");
		passed_test++;
	} else{
		DEBUG_PRINT_MSG(COLOR_RED, RESULT, "Failed");
		failed_test++;
	}
	if(CLOCK_SOURCE) total_time = total_time + (CLOCK() - start_time);
	DEBUG_DIVIDER("-", DEBUG_DIVIDER_LENGTH);
}

#define TINY_TEST_REPORT() 	PLACE(\
                                DEBUG_P(NEWLINE);\
								DEBUG_DIVIDER("=", DEBUG_DIVIDER_LENGTH);\
								DEBUG_PRINT_HEADER(COLOR_YELLOW, REPORT);\
								DEBUG("%d", (passed_test + failed_test));\
								DEBUG_P(" Tests ");\
								if(CLOCK_SOURCE){\
									DEBUG_P("in ");\
									DEBUG("%d", total_time);\
									DEBUG_P(" " CLOCK_UNIT);\
								}\
								DEBUG("%d", passed_test);\
								DEBUG_P(", Passed, ");\
								DEBUG("%d", failed_test);\
								DEBUG_P(" Failed ");\
								DEBUG_P(NEWLINE);\
								DEBUG_DIVIDER("=", DEBUG_DIVIDER_LENGTH);\
							)

#define ADD_TEST_SUITE(tiny_test_suit) 	static void tiny_test_suit(void)

#define RUN_TEST_SUITE(tiny_test_suit) 	tiny_test_suit(); 

#define TINY_ASSERT_EQUAL(expression) PLACE(\
			if(!(expression)){\
				DEBUG_PRINT_HEADER(COLOR_RED, ERROR);\
			} else{\
				DEBUG_PRINT_HEADER(COLOR_GREEN, OK);\
			}\
			DEBUG_LN(#expression);\
		)

#define ASSERT_TEST_RESULT(expression) PLACE(\
			check(expression);\
			DEBUG_LN(#expression);\
			if(last_test_status) return;\   	
		)

static void check(int result){
	if((result)){
		DEBUG_PRINT_HEADER(COLOR_GREEN, OK);
		last_test_status = 1;
	} else{\
		DEBUG_PRINT_HEADER(COLOR_RED, ERROR);
		last_test_status = 0;
	}
}

#ifdef __cplusplus
}
#endif

#endif /* TINY_TEST_H */