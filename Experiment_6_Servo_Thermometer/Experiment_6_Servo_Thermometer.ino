/*
  Servo Thermometer
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/probable-palm-tree/blob/master/LICENSE
*/

#include <Servo.h>
/*
  This Sketch was written with SimpleDHT version 1.0.11
  The code may need to be modified if other versions are used
*/
#include <SimpleDHT.h>

const int SERVO = 3; //Servo on Pin 3
const int POT   = 0; //Pot on Analog Pin 0
int pinDHT11 = 2;
int angle = 0; //angle for servo
Servo myServo;
SimpleDHT11 dht11(pinDHT11);


void setup()
{
  //Create the Servo Object and pass pin number
  myServo.attach(SERVO);
  Serial.begin (9600);
}

void loop()
{

  // now read temperature and humidity
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.println("DHT11 read fail");
    Serial.print ("err="); Serial.print(err); delay(1000);
    return;
  }
  Serial.print ("temperature :"); Serial.print (temperature);
  angle = map(temperature, 0, 50, 179, 0); //scale it to servo range
  angle = constrain (angle, 0, 179); //ensure we do not pass an angle outside of range
  Serial.print (" angle :"); Serial.println (angle);
  myServo.write(angle); //moves the servo to desired angle
  delay(1500); //wait for next temperature sample
}
