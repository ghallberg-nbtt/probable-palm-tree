/*
  Servo
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/probable-palm-tree/blob/master/LICENSE
*/

#include <Servo.h>

const int SERVO = 3; //Servo on Pin 3
const int POT   = 0; //Pot on Analog Pin 0

Servo myServo;
int val = 0; //Value of potentiometer

void setup()
{
  //Create the Servo Object and pass pin number
  myServo.attach(SERVO);
}

void loop()
{
  val = analogRead(POT); //Read Pot
  val = map(val, 0, 1023, 0, 179); //scale it to servo range
  myServo.write(val); //moves the servo to desired angle
  delay(15); //waits for the servo to finish moving
}
