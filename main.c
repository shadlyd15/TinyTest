#if !defined(ARDUINO)

#include <string.h>
#include <stdlib.h>
#include "tinytest.h"
#include "tinytest.ino"

int main(int argc, char const *argv[]){
  setup();
  while(1) {
    loop();
  }
}

#endif