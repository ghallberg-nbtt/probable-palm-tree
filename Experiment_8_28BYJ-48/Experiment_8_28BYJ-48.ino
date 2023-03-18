/*
  28BYJ-48 Stepper Motor Control
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/probable-palm-tree/blob/master/LICENSE
*/
#include <Stepper.h>

//Most 28BYJ-48 Motors have 32 steps/revolution or 2048 allowing for gears
const int STEPS_PER_REVOLUTION = 2048; //2048 steps/rev

//ULN2003 pins
const int IN1 = 2;
const int IN2 = 3;
const int IN3 = 4;
const int IN4 = 5;

// Initialize the stepper library - pass it the Switch control pins
Stepper myStepper(STEPS_PER_REVOLUTION, IN1, IN3, IN2, IN4);

void setup()
{
  //Set the stepper speed
  myStepper.setSpeed(10); //10 RPM
}

void loop()
{
  // step one revolution in one direction:
  myStepper.step(STEPS_PER_REVOLUTION);
  delay(500);

  // step one revolution in the other direction:
  myStepper.step(-STEPS_PER_REVOLUTION);
  delay(500);
}
