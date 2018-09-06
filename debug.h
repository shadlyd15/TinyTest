#ifndef TINY_DEBUG_H
#define TINY_DEBUG_H

#ifdef __cplusplus
	extern "C" {
#endif

#define NUMARGS(...)  (sizeof((int[]){__VA_ARGS__})/sizeof(int))

#if defined(ARDUINO)
    #include <Stream.h>
    static Stream * _debug_stream;
    
    static int serial_putc(char c, FILE *){
      _debug_stream->write(c);
      return c;
    }
#endif

#define NEWLINE     "\r\n"
#define PRINT_FUNC  printf

#if defined(ARDUINO)
    #define PRINT_FUNC_P  printf_P
#else
    #define PRINT_FUNC_P  PRINT_FUNC
#endif

#define OVERLOAD_PRINTF(y, x)  PRINT_FUNC_P(PSTR(x))

#define FIRST_ARG(ARG_1, ...) ARG_1
#define SELECTED_PRINT_FUNC(...)    if(NUMARGS(__VA_ARGS__) > 1) PRINT_FUNC(__VA_ARGS__);\
                                    else PRINT_FUNC_P(PSTR(FIRST_ARG(__VA_ARGS__)))\

#define P(x)  0, x

// #define ENABLE_VERBOSE
#define SUPPORT_COLOR_TEXT
#define ENABLE_GLOBAL_DEBUG

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

        #if defined(ARDUINO)
            #if defined(ARDUINO_ARCH_AVR)
                #define ATTACH_DEBUG_STREAM(stream) _debug_stream = stream;\
                                                    fdevopen(&serial_putc, 0)
            #else
                #define ATTACH_DEBUG_STREAM(stream) _debug_stream = stream
            #endif

            #define DEBUG_P(...)                PRINT_FUNC_P(PSTR(__VA_ARGS__))
        #else
            #define ATTACH_DEBUG_STREAM(x)
            #define DEBUG_P(...)                PRINT(__VA_ARGS__);
        #endif

        #define PLACE(x)                    do{x;} while(0)

        #define PRINT(...)                  PRINT_FUNC(__VA_ARGS__);

        #define PRINT_COLOR(COLOR, TEXT)    DEBUG_P(COLOR);\
                                            DEBUG_P(TEXT);\
                                            DEBUG_P(COLOR_RESET)
                                            
        #define PRINT_LN(...)               PRINT(__VA_ARGS__);  \
                                            DEBUG_P(NEWLINE)

        #define DEBUG_NEWLINE()             DEBUG_P(NEWLINE)

        #define DEBUG(...)                  PRINT(__VA_ARGS__)

        #define DEBUG_LN(...)               PRINT_LN(__VA_ARGS__)

        #define DEBUG_PRINT_HEADER(COLOR, HEADER) DEBUG_P(COLOR "[" #HEADER "] " COLOR_RESET)

        #define DEBUG_PRINT_MSG(COLOR, HEADER, MSG)   DEBUG_P(COLOR "[" #HEADER "] " COLOR_RESET);\
                                                      DEBUG_LN(MSG)

        #define DEBUG_OK(...)       PLACE(  DEBUG_PRINT_HEADER(COLOR_GRN, OK);     \
                                        	SELECTED_PRINT_FUNC(__VA_ARGS__);   )

        #define DEBUG_ERROR(...)    PLACE(  DEBUG_PRINT_HEADER(COLOR_RED, ERROR);     \
                                        	PRINT_LN(__VA_ARGS__);   )

        #define DEBUG_ALERT(...)  	PLACE(  DEBUG_PRINT_HEADER(COLOR_YEL, ALERT);     \
                                        	PRINT_LN(__VA_ARGS__);   )

        #define DEBUG_WARNING(...)  PLACE(  PLACE(  DEBUG_PRINT_HEADER(COLOR_MAG, WARNING);     \
                                        	PRINT_LN(__VA_ARGS__);   )

        #define DEBUG_ARRAY(ARRAY, LENGTH, FORMAT) \
		        PLACE(\
		            DEBUG_PRINT_HEADER(COLOR_CYN, ARRAY);\
		            DEBUG_P(#ARRAY);\
		            PRINT("[%d] = { ", LENGTH);\
		            for(int i = 0; i < LENGTH; i++) {\
						PRINT(FORMAT, ARRAY[i]); \
						if(i < (LENGTH - 1)) \
							PRINT(", ");\
					}\
		            PRINT_LN(" };");\
		        )

        #define DEBUG_VALUE(VALUE, TYPE)  PLACE(\
		        							DEBUG_PRINT_HEADER(COLOR_CYN, VALUE);\
                                          	DEBUG_P(#VALUE);\
                                          	DEBUG_P(" = ");\
                                          	PRINT_LN(TYPE, VALUE);\
                                          )

        #define DEBUG_DIVIDER(CHAR, LENGTH) PLACE(\
        										DEBUG_P(COLOR_YEL);\
	                                            for(int i = 0; i < LENGTH; i++){\
	                                                PRINT("%c", CHAR);\
	                                            }\
	                                            DEBUG_P("\n");\
	                                            DEBUG_P(COLOR_RESET);\
	                                        )

        #define DEBUG_TRACE() PRINT(COLOR_YEL "[TRACE] File : %s :: Function : %s :: Line : %d\r\n" COLOR_RESET, __FILENAME__, __func__, __LINE__)

        #define THROW_EXCEPTION(...)    PLACE(\
        									DEBUG_PRINT_HEADER(COLOR_GRN, EXCEPTION);     \
                                            PRINT_LN(__VA_ARGS__);   \
                                            DEBUG_TRACE();  \
                                        )

    #else
        #if defined(ARDUINO)
            #define ATTACH_DEBUG_STREAM(x)
            #define DEBUG_P(...)                PRINT(__VA_ARGS__);
        #endif

        #define PLACE(x)
        #define PRINT(...)
        #define PRINT_LN(...)
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