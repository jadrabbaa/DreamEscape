#include <NewPing.h>   //include the library

int led = 5;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount1 = 7;    // how many points to fade the LED by
int fadeAmount2 = 2;    // how many points to fade the LED by


int triggerPin = 12;   //pin conneccted to the Trig pin on the sensor
int echoPin = 11;       //pin connected to the Echo pin on the sensor
int maxDistance = 200;  //set the max distance for the sensor to read (helps with errors)
int distanceVal; //variable to hold the distance val
int lastFade;
int fadeRate = 200;

int inData;

int sampleRate = 200;   //how fast to sample the value
long lastReading;       //used for the timer



NewPing proximity1(triggerPin, echoPin, maxDistance);   //sets up the sensor object

void setup() 
{
  Serial.begin(9600);  //start the serial port
  pinMode(led, OUTPUT);
}

void loop() {

  if(millis()-lastReading>=sampleRate) //this very simple statement is the timer,
{ 
  distanceVal = proximity1.ping_cm();  //get the distance value in centimeters


  lastReading = millis();

//  Serial.print("Distance Reading CM : ");  //print the value to the Serial monitor
//  Serial.println(distanceVal);
}




if((distanceVal<50)&&(distanceVal>1)){

  inData = map(distanceVal, 1, 50, 100, 75); // remap the pot value to fit in 1 byte

    // set the brightness of pin 9:
  analogWrite(led, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount1;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount1 = -fadeAmount1;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(10);
}


else{

    inData = map(distanceVal, 51, 200, 75, 1); // remap the pot value to fit in 1 byte


    // set the brightness of pin 9:
  analogWrite(led, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount2;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount2 = -fadeAmount2;
  }

   if((distanceVal==0))
  {
    inData = 1;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(25);
}
Serial.println(distanceVal);
Serial.println(inData);
}
