#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <Keypad.h>
#include <SoftwareSerial.h>

const byte ROWS = 4;
const byte COLS = 3;
const int numDigits = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

int timer[4] = {0, 0, 0, 0};
int idx = 0;

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3};
char str[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();


const int txPin = 11;
const int rxPin = 12;

SoftwareSerial BTSerial(rxPin, txPin); // RX, TX

void setup() {
  Serial.begin(9600);
  alpha4.begin(0x70);  // pass in the address

  // alpha4.clear();
  // alpha4.writeDisplay();
  BTSerial.begin(38400);

}


char displaybuffer[4] = {' ', ' ', ' ', ' '};
int num = 0;
bool done = false;
int counter = 0;
bool timerDone = false;

void loop() {
  char customKey = customKeypad.getKey();
  if (!done && customKey) {
    Serial.println(customKey);
    if (customKey != '*' && customKey != '#' && num < 1000) {
      int inputNum = (int)customKey - (int)'0';
      num = 10 * num + inputNum;
      alpha4.writeDigitAscii(counter, str[inputNum]);
      alpha4.writeDisplay();
      counter++;

    } else {
      done = true;
    }
    Serial.println(num);
  }
  if (done && !timerDone) {
    int i = num / 1000;
    int j = (num / 100) % 10;
    int k = (num / 10) % 10;
    int m = num % 10;

    for (; i >= 0; i--) {
      for (; j >= 0; j--) {
        for (; k >= 0; k--) {
          for (; m >= 0; m--) {
            alpha4.writeDigitAscii(0, str[i]);
            alpha4.writeDigitAscii(1, str[j]);
            alpha4.writeDigitAscii(2, str[k]);
            alpha4.writeDigitAscii(3, str[m]);
            alpha4.writeDisplay();

            int writable = i * 1000 + j * 100 + k * 10 + m;
            BTSerial.println(String(writable));
            Serial.println(String(writable));
            
            delay(1000);
            alpha4.clear();
          }
          if (k != 0) m = 9;
        }
        if (j != 0) k = 6;
      }
      if (i != 0) j = 10;
    }

    timerDone = true;

  } else if (done) {
    alpha4.writeDigitAscii(1, 'E');
    alpha4.writeDigitAscii(2, 'n');
    alpha4.writeDigitAscii(3, 'd');
    alpha4.writeDisplay();
    delay(100);
    alpha4.clear();
    alpha4.writeDisplay();
  }


}
