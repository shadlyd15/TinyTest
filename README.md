
# Tiny Test

**Tiny Test** is a minimal unit test framework for C/C++. It is designed especially for embedded systems keeping in mind the limitation and capabilities of the platform.
  - Low memory usage
  - Supports a wide range of compilers and processor architectures
  - Arduino compatible
  - Color debug output
  - Very easy to use
  
## How to use
- **Add Test and Assert Result :**
 ```C
	ADD_TINY_TEST(test_0){
		  int i = rand()%50;
		  ASSERT_TEST_RESULT(i != 1);
	}
```
- **Run Test :**
 ```C
	RUN_TINY_TEST(test_0);
```
- **Add Test Suit :**
 ```C
	ADD_TEST_SUITE(test_suit){
		RUN_TINY_TEST(test_0);
	}
```
- **Run Test Suit :**
 ```C
	RUN_TEST_SUITE(test_suit);
```
- **Generate Test Report :**
 ```C
	TINY_TEST_REPORT();
```
## Arduino Example 

 ``` C

	#include "tinytest.h"

	ADD_TINY_TEST(test_0){
	  int i = rand()%50;
	  ASSERT_TEST_RESULT(i != 1);
	}

	ADD_TINY_TEST(test_1){
	  int i = rand()%50;
	  ASSERT_TEST_RESULT(i == 2);
	}

	ADD_TINY_TEST(test_2){
	  int i = rand()%50;
	  ASSERT_TEST_RESULT(i != 3);
	}

	ADD_TEST_SUITE(test_suit){
	  RUN_TINY_TEST(test_0);
	  RUN_TINY_TEST(test_1);
	  RUN_TINY_TEST(test_2);
	}

	int popup(const char * input){
	  if(!strncmp(input, "Y", strlen("Y"))){
	    DEBUG_DIVIDER("*", TEST_DIVIDER_LENGTH);
	    DEBUG_OK("Tiny Test Starting");  
	    RUN_TEST_SUITE(test_suit);
	    TINY_TEST_REPORT();
	    DEBUG_INPUT(NULL, "Press Enter To Exit", 0);
	    return 1;
	  }
	  return 0;
	}

	void setup(){
	  SET_CLOCK_SOURCE(&millis);
	  ARDUINO_ONLY(Serial.begin(115200));
	  ATTACH_DEBUG_STREAM(&Serial);
	  DEBUG_DIVIDER("*", TEST_DIVIDER_LENGTH);
	  DEBUG_INPUT(&popup, "Run Test? (Y/N)", 0);
	  DEBUG_OK("Going To Loop");
	}

	void loop(){

	}
	
 ```

## Sample Output

![Sample Output](https://raw.githubusercontent.com/shadlyd15/tinytest/master/images/output.png)