#include "SevSeg.h"
SevSeg sevseg; 

void setup(){
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};

  bool resistorsOnSegments = true; 
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

void loop(){
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
          sevseg.setNumber(1000*i + 100*j + 10*k + m, 2);
          delay(1000);
          sevseg.refreshDisplay(); 
        }
        if(k != 0) m = 9;
      }
      if(j != 0) k = 5;
    }
    if(i != 0) j = 9;
  }
}
