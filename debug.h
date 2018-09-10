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
#else
    #include <stdio.h>
#endif

#define DEFAULT_TEXT_COLOR      COLOR_YELLOW

#define NEWLINE                 "\r\n"
#define PRINT_FUNC              printf

#define SUPPORT_COLOR_TEXT
#define ENABLE_GLOBAL_DEBUG
// #define ENABLE_VERBOSE

#if !defined(ARDUINO)
    #define PRINT_FUNC_P  printf
#else
    #define PRINT_FUNC_P  printf_P
#endif // defined(ARDUINO)


#if !defined(SUPPORT_COLOR_TEXT)
    #define COLOR_RED               
    #define COLOR_GREEN             
    #define COLOR_YELLOW            
    #define COLOR_BLUE              
    #define COLOR_MAGENTA           
    #define COLOR_CYAN              
    #define COLOR_WHITE             
#else
    #define COLOR_RED               "\x1B[31m"
    #define COLOR_GREEN             "\x1B[32m"
    #define COLOR_YELLOW            "\x1B[33m"
    #define COLOR_BLUE              "\x1b[34m"
    #define COLOR_MAGENTA           "\x1b[35m"
    #define COLOR_CYAN              "\x1B[36m"
    #define COLOR_WHITE             "\x1B[0m"
#endif  /* SUPPORT_COLOR_TEXT  */

    #if defined(ENABLE_GLOBAL_DEBUG) || defined(DEBUG_THIS_FILE)

        #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

        #define PLACE(x)                    do{x} while(0)
        #define PRINT(...)                  PRINT_FUNC(__VA_ARGS__)

        #if defined(ARDUINO) && defined(ARDUINO_ARCH_AVR)
            #define FLASH                       PSTR
            #define FIRST_ARG(ARG_1, ...)       ARG_1
            #define ATTACH_DEBUG_STREAM(stream) {   _debug_stream = stream;\
                                                    fdevopen(&serial_putc, 0);  }
            #define DEBUG(string, ...)          PRINT_FUNC_P(FLASH(string), ##__VA_ARGS__)
        #else
            #define FLASH                       
            #define FIRST_ARG(ARG_1, ...)       
            #define ATTACH_DEBUG_STREAM(x)      
            #define DEBUG(string, ...)          PRINT(string, ##__VA_ARGS__)
        #endif /* defined(ARDUINO) && defined(ARDUINO_ARCH_AVR) */
                                
        #define DEBUG_LN(...)               DEBUG(__VA_ARGS__);\
                                            PRINT(NEWLINE)

        #define DEBUG_PRINT_HEADER(COLOR, HEADER) DEBUG(COLOR " + [" #HEADER "] \t: " DEFAULT_TEXT_COLOR)

        #define DEBUG_PRINT_MSG(COLOR, HEADER, MSG)   DEBUG(COLOR " + [" #HEADER "] \t: " DEFAULT_TEXT_COLOR MSG NEWLINE)

        #define DEBUG_OK(...)       PLACE(  DEBUG_PRINT_HEADER(COLOR_GREEN, OK);     \
                                        	DEBUG_LN(__VA_ARGS__);   )

        #define DEBUG_ERROR(...)    PLACE(  DEBUG_PRINT_HEADER(COLOR_RED, ERROR);     \
                                        	DEBUG_LN(__VA_ARGS__);   )

        #define DEBUG_ALERT(...)  	PLACE(  DEBUG_PRINT_HEADER(COLOR_CYAN, ALERT);     \
                                        	DEBUG_LN(__VA_ARGS__);   )

        #define DEBUG_WARNING(...)  PLACE(  PLACE(  DEBUG_PRINT_HEADER(COLOR_YELLOW, WARNING);     \
                                        	DEBUG_LN(__VA_ARGS__);   )

        #define DEBUG_ARRAY(VICTIM, LENGTH, FORMAT) \
		        PLACE(\
		            DEBUG_PRINT_HEADER(COLOR_CYAN, ARRAY);\
		            DEBUG(#VICTIM);\
		            DEBUG("[%d] = { ", LENGTH);\
		            for(int i = 0; i < LENGTH; i++) {\
						DEBUG(FORMAT, VICTIM[i]); \
						if(i < (LENGTH - 1)) \
							DEBUG(", ");\
					}\
		            DEBUG(" };" NEWLINE);\
		        )

        #define DEBUG_VALUE(TYPE, VAR)  PLACE(\
		        							DEBUG_PRINT_HEADER(COLOR_MAGENTA, VALUE);\
                                          	DEBUG(#VAR " = ");\
                                          	DEBUG_LN(TYPE, VAR);\
                                          )

        #define DEBUG_DIVIDER(STR, LENGTH)          print_divider(STR, LENGTH)

        static void print_divider(char * str, int length){
            #if defined(SUPPORT_COLOR_TEXT)
                DEBUG(COLOR_CYAN);
            #endif
            for(int i = 0; i < length; i++){
                PRINT(str);
            }
            DEBUG(DEFAULT_TEXT_COLOR NEWLINE);
        }

        #define DEBUG_TRACE()           DEBUG(COLOR_YELLOW " + [TRACE] Function : %s() :: Line : %d" DEFAULT_TEXT_COLOR NEWLINE, __func__, __LINE__)

        #define THROW_EXCEPTION(...)    PLACE(\
        									DEBUG_PRINT_HEADER(COLOR_GREEN, EXCEPTION);     \
                                            DEBUG_LN(__VA_ARGS__);   \
                                            DEBUG_TRACE();  \
                                        )

    #else
        #if defined(ARDUINO)
            #define ATTACH_DEBUG_STREAM(x)
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