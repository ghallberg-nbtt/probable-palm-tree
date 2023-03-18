/*
  Speed Control of a DC Motor using PWM
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/probable-palm-tree/blob/master/LICENSE
*/
const int MOTOR = 3; //pin for motor control
const int POT = 5; //A5 pin

int speed = 0; //variable for the speed

void setup() {
  pinMode (MOTOR, OUTPUT); //set pin 3 for output
}

void loop() {
  speed = analogRead (POT); //read the pot value
  speed = map (speed, 0, 1023, 0, 255); // Map the ADC value to PWM value
  analogWrite(MOTOR, speed); //change speed of motor
  delay (50);
}
