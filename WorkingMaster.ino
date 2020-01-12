#include <SoftwareSerial.h>

const int txPin = 11;
const int rxPin = 12;

SoftwareSerial BTSerial(rxPin, txPin); // RX, TX

void setup() {
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400);
}

void loop() {
//  if (BTSerial.available())
//  {
//    Serial.write(BTSerial.read());
    BTSerial.write("abc");
    Serial.write("abc");
    delay(1000);
//  }
//  if (Serial.available())
    //BTSerial.write(Serial.read());
}
