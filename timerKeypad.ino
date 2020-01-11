
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 3; 
const int numDigits = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

int timer[4] = {0,0,0,0};
int index = 0;

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

void setup() {
  Serial.begin(9600);
  alpha4.begin(0x70);  // pass in the address
  
  alpha4.clear();
  alpha4.writeDisplay();

}


char displaybuffer[4] = {' ', ' ', ' ', ' '};

void loop() {
  char* str = "0123456789";
  for(int i = 0;i < timer.length();i++) {
    char customKey = customKeypad.getKey();
    int num = 0;
    num = ((int)(customKey)) - 48;
    alpha4.writeDigitAscii(i, str[num]);
    alpha4.writeDisplay();
    timer[i] = num;
  }

  int i = timer[0];
  int j = timer[1];
  int k = timer[2];
  int m = timer[3];

  for(;i >= 0;i--) {
    for(;j >= 0;j--) {
      for(;k >= 0;k--) {
        for(;m >= 0;m--) {
          alpha4.writeDigitAscii(0, str[i]);
          alpha4.writeDigitAscii(1, str[j]);
          alpha4.writeDigitAscii(2, str[k]);
          alpha4.writeDigitAscii(3, str[m]);
          alpha4.writeDisplay();
          delay(1000);
          alpha4.clear();
        }
        if(k != 0) m = 9;
      }
      if(j != 0) k = 6;
    }
    if(i != 0) j = 9;
  }

  alpha4.writeDigitAscii(1, 'E');
  alpha4.writeDigitAscii(2, 'n');
  alpha4.writeDigitAscii(3, 'd');
  alpha4.writeDisplay();
  delay(5000);
}
