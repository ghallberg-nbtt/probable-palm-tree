/*
  Controlling a Motor using a Transistor
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/probable-palm-tree/blob/master/LICENSE
*/
const int MOTOR = 3; //pin for motor control

void setup() {
  pinMode (MOTOR, OUTPUT); //set pin 3 for output
}

void loop() {
  digitalWrite (MOTOR, HIGH);
  delay (2000); //turn on motor for 2 seconds
  digitalWrite (MOTOR, LOW);
  delay (2000); //turn off motor for 2 seconds
}
