/*
  NEMA-17 Stepper Motor Control
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/probable-palm-tree/blob/master/LICENSE
*/
#include <Stepper.h>

//Most NEMA-17 Motors have 200 steps/revolution
const int STEPS_PER_REVOLUTION = 200; //200 steps/rev

//L298N pins
const int INPUT1 = 2;
const int INPUT2 = 3;
const int INPUT3 = 4;
const int INPUT4 = 5;

// Initialize the stepper library - pass it the Switch control pins
Stepper myStepper(STEPS_PER_REVOLUTION, INPUT1, INPUT2, INPUT3, INPUT4);

void setup()
{
  //Set the stepper speed
  myStepper.setSpeed(60); //60 RPM
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
