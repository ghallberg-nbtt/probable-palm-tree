/*
  28BYJ-48 Stepper Motor Control with Rotary Encoder
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/probable-palm-tree/blob/master/LICENSE
*/
#include <Stepper.h>

//Most 28BYJ-48 Motors have 32 steps/revolution or 2048 allowing for gears
const int STEPS_PER_REVOLUTION = 32; //32 steps/rev
const int MULTIPLIER = 50; //Multiplier for number of steps
//ULN2003 pins
const int IN1 = 2;
const int IN2 = 3;
const int IN3 = 4;
const int IN4 = 5;

//Rotary encoder inputs
const int CLK = 8;
const int DT = 9;
const int SWITCH = 10;

//Variables
int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir = "";
boolean previousButton = HIGH; 
boolean currentButton = HIGH; 

// Initialize the stepper library - pass it the Switch control pins
Stepper myStepper(STEPS_PER_REVOLUTION, IN1, IN3, IN2, IN4);

void setup() {

  //Set encoder pins as inputs
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SWITCH, INPUT_PULLUP);
  //Set the stepper speed
  myStepper.setSpeed(600); //600 RPM

  //Setup Serial Monitor
  Serial.begin(9600);

  //Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);
}

void loop() {

  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if ((currentStateCLK != lastStateCLK)  && (currentStateCLK == 1)) {

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT) != currentStateCLK) {
      counter --;
      currentDir = "CCW";
      //step motor one step CCW x multiplier
      myStepper.step(-1 * MULTIPLIER);
    } else {
      // Encoder is rotating CW so increment
      counter ++;
      currentDir = "CW";
      //step motor one step CW
      myStepper.step(1 * MULTIPLIER);
    }

    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;

  // Read the button state
  //int buttonState = digitalRead(SWITCH);

  currentButton = digitalRead(SWITCH); // Read the switch state

  if (previousButton != currentButton)  // If switch pressed
  {
    delay(5);  // Wait 5ms
    currentButton = digitalRead(SWITCH);  // Read switch again
  }

  if (previousButton == HIGH && currentButton == LOW)  // Detect a button press
  {
    Serial.println("Button pressed");
    // Step motor back to start position
    myStepper.step(-counter * MULTIPLIER);
    counter = 0;
  }

  // Put in a slight delay to help debounce the reading
  delay(1);
}
