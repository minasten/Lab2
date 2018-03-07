//Global variables
//Constant pin values
const int loudSpeakerPin= 8;
const int headPhonePin= 7;
const int buttonPin = 9;
const int triggerPin= 11;     //Ultrasonic sensor
const int echoPin = 12;       //Ultrasonic sensor
const int lightPin = A0;      //IR sensor

//Boolean value for off/on
bool mode = true;

//Setting up ultrasonic sensor
const int maxDistance = 300;
NewPing sonar(triggerPin, echoPin, maxDistance);
int frequency_us = 0;
int duration = 200;

//Setting up servo for ultrasonic sensor
Servo usServo;
int pos = 0;

//Initial led state
int ledState = LOW;

//Initial button states
PLab_PushButton myButton(buttonPin);
int buttonState = 0;
int previousButtonState = HIGH;

//Function for boolean state
void setState() {
     myButton.update();
     if (myButton.pressed()) {
      mode = !mode;
     }
}


//Defining tones in Hz
#define  c4     262 
#define  d4     294 
#define  e4     330 
#define  f4     349 
#define  g4     392 
#define  a4     440 
#define  b4     494 
#define  c5     523 
#define   R       0


//"Lisa gikk til skolen"
int melody[] = {
  c4,  d4,  e4,  f4,  g4,   g4,  a4,  a4,  a4,  a4, g4 };
  
int beats[]  = { 
  4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 1 };
  
int MAX_COUNT = 11;  //Melody length, for looping.


long tempo = 1000;  // Set overall tempo
long pauseTime = tempo/25;  // Set length of pause between notes
int pianoFrequency = 0;  
int pianoBeat = 0;
long pianoDuration  = 0;

//Setting up function for piano music "Lisa gikk til skolen"
void PianoMusic() {  
  for (int i=0; i<MAX_COUNT; i++) {
      pianoFrequency = melody[i];
      pianoBeat = beats[i];
      pianoDuration = tempo / pianoBeat;                    // Timing set up
      tone(loudSpeakerPin, pianoFrequency, pianoDuration);
      delay(pianoDuration);
      delay(pauseTime); //                                  //Pause between notes
      setState();
      if(!mode){
        delay(50);
        return;
        }
  }
  delay(500);                                             //Pause between melodies.
}


//Setting up function for playing music from sensors
void playMusic(int pin, int freq, int dur) {
    long int pulseLength = 500000 / freq;
    long int durLong = dur;
    long int noOfPulses = (durLong*1000) / (pulseLength*2);
    for (long int i=0; i < noOfPulses; i++) {
      digitalWrite(loudSpeakerPin, HIGH);
      delayMicroseconds(pulseLength);
      digitalWrite(loudSpeakerPin, LOW);
      delayMicroseconds(pulseLength);
    }
  }

//Setting up functions for ultrasonic sensor
void pingMode() {
  unsigned int time = sonar.ping();
  float distance = sonar.convert_cm(time);
  frequency_us = 20*distance;
  Serial.println(distance);
  Serial.println(frequency_us);
  playMusic(loudSpeakerPin, frequency_us, 200);
}

void SpinOn() {
  usServo.write(100);
  pingMode();
  setState();
      if(mode){
        delay(50);
        return;
        }
}

void SpinOff() {
  usServo.write(10);
  delay(100);
}

//Setting up functions for light sensor
void sensorMode() {
 int lightValue = analogRead(lightPin);
 int frequency_l = lightValue * 10;
 Serial.println(frequency_l);
 Serial.println(lightValue);
 playMusic(headPhonePin, frequency_l, 200);
 delay(300);
 if(!mode){
        delay(50);
        return;
        }
}
 
/*Setting up functions for led on/off
void LedOn() {
  digitalWrite(ledPin, HIGH);
}

void LedOff() {
  digitalWrite(ledPin, LOW);
}*/
