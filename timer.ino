// Demo the quad alphanumeric display LED backpack kit
// scrolls through every character, then scrolls Serial
// input onto the display

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

void setup() {
  alpha4.begin(0x70);  // pass in the address
}


char displaybuffer[4] = {' ', ' ', ' ', ' '};

void loop() {
  const char* foo = "0123456789";
  int i = INPUT_0;
  int j = INPUT_1;
  int k = INPUT_2;
  int m = INPUT_3;
  for(;i > 0;i--) {
    for(;j > 0;j--) {
      int k = INPUT_2;
      for(;k > 0;k--) {
        int m = INPUT_3;
        for(;m > 0;m--) {
        // set every digit to the buffer
          alpha4.writeDigitAscii(0, foo[i]);
          alpha4.writeDigitAscii(1, foo[j]);
          alpha4.writeDigitAscii(2, foo[k]);
          alpha4.writeDigitAscii(3, foo[m]);
          alpha4.writeDisplay();
          delay(1000);
        }
        if(k != 0) m = 9;
      }
      if(j != 0) k = 5;
    }
    if(i != 0) j = 9;
  }
  
 
}
