#include <NewPing.h>
#include <Servo.h> 
#include "PLab_PushButton.h"
#include "Functionalities.h"

void setup() {
  Serial.begin(9600);
  
  //Setting all pins to output/input
  pinMode(lightPin, INPUT);
  pinMode(loudSpeakerPin, OUTPUT);
  pinMode(headPhonePin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  usServo.attach(13);
}

void loop() {

    
    while (!mode) {
      SpinOn();
      delay(100);
      setState();
     }

    while (mode) { 
      SpinOff(); 
      sensorMode();
      delay(100);
      setState();
     }
}
