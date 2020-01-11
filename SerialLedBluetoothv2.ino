/*
 * Written by Alexander Graening and Arti Patankar on behalf of IEEE at UCLA in Janurary 2019 for the 2019 IDEA Hacks hardware hackathon.
 * Updated in December 2019 by Alexander Graening for the January 2020 IDEA Hacks.
 * 
 */


//Remember to change pins for LEDs on different Arduinos.


//Defining LED Constants. These will work if you follow the tutorial, but if you connect the LEDs to other pins, simply change the pin numbers here.
//Note: LED_BUILTIN is a constant defined for whichever Arduino board you choose.
#define YELLOW_LED 11
#define RED_LED 12

//This is a starting character value that will be replaced by values recieved over bluetooth
char inputChar = 'a';

//Initialize starting states for leds. This enables toggling leds.
bool rLedState = false;
bool yLedState = false;
bool bLedState = false;


// the setup function runs once when you press reset or power the board
void setup() {
  //Initialize
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  if (Serial.available() > 0) //The value returned by Serial.available() will be 0 if there has not been a transmission.
  {
    inputChar = Serial.read();  //Store character read from serial
    Serial.println(inputChar);  //This sends the recieved value back to the the Bluetooth master (your computer). This prints the value for you to see
    switch (inputChar)
    {
      case 'r':   //Red LED
        if (rLedState)
        {
          digitalWrite(RED_LED,LOW);
          rLedState = false;
        }
        else
        {
          digitalWrite(RED_LED, HIGH);
          rLedState = true;
        }
        break;
      case 'y':   //Yellow LED        
        if (yLedState)
        {
          digitalWrite(YELLOW_LED,LOW);
          yLedState = false;
        }
        else
        {
          digitalWrite(YELLOW_LED, HIGH);
          yLedState = true;
        }
        break;
      case 'b':   //Built-in LED
        if (bLedState)
        {
          digitalWrite(LED_BUILTIN,LOW);
          bLedState = false;
        }
        else
        {
          digitalWrite(LED_BUILTIN, HIGH);
          bLedState = true;
        }
        break;
      case 'o':   //All LEDs off
        digitalWrite(LED_BUILTIN,LOW);
        digitalWrite(YELLOW_LED,LOW);
        digitalWrite(RED_LED,LOW);
        rLedState = false;
        yLedState = false;
        bLedState = false;
        break;
      default:
        break;
    }
  }
}
