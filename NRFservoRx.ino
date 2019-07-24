/*
* Arduino Wireless Communication Tutorial
*     Example 2 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define button 4

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
Servo myServo;
boolean buttonState = 0;

void setup() {
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  myServo.attach(5);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MAX);
  for(int p = 0; p < 180; p++)
  {
    myServo.write(p);
  }
  for(int p = 180; p > 0; p--)
  {
    myServo.write(p);
  }
}

void loop() {
  delay(5);
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()) {
      int angleV = 0;
      radio.read(&angleV, sizeof(angleV));
      myServo.write(angleV);
      Serial.println(angleV);
    }
    delay(5);
    radio.stopListening();
    buttonState = not(digitalRead(button));
    radio.write(&buttonState, sizeof(buttonState));
    }
    if(buttonState)
    {
      Serial.println("Button Pressed");
    }
  }

