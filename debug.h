#ifndef TINY_DEBUG_H
#define TINY_DEBUG_H

#ifdef __cplusplus
	extern "C" {
#endif

#define NEWLINE     "\r\n"
#define PRINT_FUNC  printf

#define SUPPORT_COLOR_TEXT
#define ENABLE_GLOBAL_DEBUG
// #define ENABLE_VERBOSE

#if defined(SUPPORT_COLOR_TEXT)
    #define COLOR_RED   			"\x1B[31m"
    #define COLOR_GRN   			"\x1B[32m"
    #define COLOR_YEL   			"\x1B[33m"
    #define COLOR_BLU   			"\x1b[34m"
    #define COLOR_MAG   			"\x1b[35m"
    #define COLOR_CYN   			"\x1B[36m"
	#define COLOR_RESET 			"\x1B[0m"
#else
    #define COLOR_RED
    #define COLOR_GRN
    #define COLOR_YEL
    #define COLOR_BLU
    #define COLOR_MAG
    #define COLOR_CYN
    #define COLOR_RESET
#endif  /* SUPPORT_COLOR_TEXT  */

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

    #if defined(ENABLE_GLOBAL_DEBUG) || defined(DEBUG_THIS_FILE)

        #define PLACE(x)                    do{x;} while(0)
        #define PRINT(...)                  PRINT_FUNC(__VA_ARGS__)
        #define PRINT_COLOR(COLOR, ...)     PRINT(COLOR)\
                                            PRINT(__VA_ARGS__)\
                                            PRINT(COLOR_RESET)
                                            
        #define PRINTLN(...)                PRINT(__VA_ARGS__);  \
                                            PRINT(NEWLINE)
        #define DEBUG_NEWLINE()             PRINT(NEWLINE)

        #define DEBUG(...)                  PRINT(__VA_ARGS__)

        #define DEBUG_LN(...)               PRINTLN(__VA_ARGS__)

        #define DEBUG_PRINT_HEADER(COLOR, TEXT) PRINT(COLOR "[" #TEXT "] " COLOR_RESET)

        #define DEBUG_PRINT_MSG(COLOR, TEXT, ...)   PRINT(COLOR "[" #TEXT "] " COLOR_RESET);\
                                                    DEBUG_LN(__VA_ARGS__)

        #define DEBUG_OK(...)       PLACE(  DEBUG_PRINT_HEADER(COLOR_GRN, OK);     \
                                        	PRINTLN(__VA_ARGS__);   )

        #define DEBUG_ERROR(...)    PLACE(  DEBUG_PRINT_HEADER(COLOR_RED, ERROR);     \
                                        	PRINTLN(__VA_ARGS__);   )

        #define DEBUG_ALERT(...)  	PLACE(  DEBUG_PRINT_HEADER(COLOR_YEL, ALERT);     \
                                        	PRINTLN(__VA_ARGS__);   )

        #define DEBUG_WARNING(...)  PLACE(  PLACE(  DEBUG_PRINT_HEADER(COLOR_MAG, WARNING);     \
                                        	PRINTLN(__VA_ARGS__);   )

        #define DEBUG_ARRAY(ARRAY, LENGTH, FORMAT) \
		        PLACE(\
		            PRINT(COLOR_CYN "[ARRAY] " COLOR_RESET);\
		            PRINT(#ARRAY);\
		            PRINT("[%d] = { ", LENGTH);\
		            for(int i = 0; i < LENGTH; i++) {\
						PRINT(FORMAT, ARRAY[i]); \
						if(i < (LENGTH - 1)) \
							PRINT(", ");\
					}\
		            PRINTLN(" };");\
		        )

        #define DEBUG_VALUE(VALUE, TYPE)  PLACE(\
		        							PRINT(COLOR_CYN "[VALUE] " COLOR_RESET);\
                                          	PRINT(#VALUE);\
                                          	DEBUG(" = ");\
                                          	PRINTLN(TYPE, VALUE);\
                                          )

        #define DEBUG_DIVIDER(CHAR, LENGTH) PLACE(\
        										PRINT(COLOR_YEL);\
	                                            for(int i = 0; i < LENGTH; i++){\
	                                                PRINT("%c", CHAR);\
	                                            }\
	                                            PRINT("\n");\
	                                            PRINT(COLOR_RESET);\
	                                        )

        #define DEBUG_TRACE() PRINT(COLOR_YEL "[TRACE] File : %s :: Function : %s :: Line : %d\n" COLOR_RESET, __FILENAME__, __func__, __LINE__)

        #define THROW_EXCEPTION(...)    PLACE(\
        									DEBUG_PRINT_HEADER(COLOR_GRN, EXCEPTION);     \
                                            PRINTLN(__VA_ARGS__);   \
                                            DEBUG_TRACE();  \
                                        )

    #else
        #define PLACE(x)
        #define PRINT(...)
        #define PRINTLN(...)
        #define DEBUG_NEWLINE()
		#define DEBUG_TRACE(...)
        #define DEBUG(...)
        #define DEBUG_LN(...)
        #define DEBUG_PRINT_HEADER(COLOR, TEXT)        
        #define DEBUG_PRINT_MSG(COLOR, TEXT, ...)
        #define DEBUG_OK(...)
        #define DEBUG_ERROR(...)
        #define DEBUG_WARNING(...)
        #define DEBUG_ARRAY(ARRAY, LENGTH, FORMAT)
        #define DEBUG_VALUE(...)
        #define DEBUG_DIVIDER(CHAR, LENGTH)
        #define THROW_EXCEPTION(...)

    #endif /* defined(ENABLE_GLOBAL_DEBUG) || defined(DEBUG_THIS_FILE) */

    #if defined(ENABLE_VERBOSE)
        #define VERBOSE(x)  {x}
    #else
        #define VERBOSE(x)
    #endif /* ENABLE_VERBOSE */

#ifdef __cplusplus
}
#endif

#endif /* TINY_DEBUG_H */