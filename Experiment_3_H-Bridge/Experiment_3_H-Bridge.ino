/*
  Controlling a Motor using a H-Bridge
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/probable-palm-tree/blob/master/LICENSE
*/

const int ENABLE1 = 3;
const int INPUT1 = 4;
const int INPUT2 = 5;
const int SWITCH = 6;
const int POT = 0;
int speed = 0;
boolean previousButton = HIGH; // Variable containing the previous button state
boolean currentButton = HIGH; // Variable containing the current button state
boolean goForward = true; //Set initial direction as forward

void setup() {
  pinMode (ENABLE1, OUTPUT);
  pinMode (INPUT1, OUTPUT);
  pinMode (INPUT2, OUTPUT);
  pinMode (SWITCH, INPUT_PULLUP);
  brake (); //Stop motor
}

void loop() {
  //Read the switch to check for direction toggle
  currentButton = digitalRead(SWITCH); // Read the switch state

  if (previousButton != currentButton)  // If switch pressed
  {
    delay(5);  // Wait 5ms
    currentButton = digitalRead(SWITCH);  // Read switch again
  }
  if (previousButton == HIGH && currentButton == LOW)  // Detect a button press
  {
    goForward = !goForward;  // Change direction
  }
  previousButton = currentButton;  // Reset button value

  //Read the potentiometer
  speed = analogRead (POT);
  speed = map (speed, 0, 1023, 0, 255);
  if (speed <= 10) {
    brake();
  } else {
    if (goForward == true) {
      forward (speed);
    } else {
      reverse (speed);
    }
  }
}
//Drive motor forward at the specified speed (0 – 255)
void forward (int speed)
{
  digitalWrite (ENABLE1, LOW); //Disable H-Bridge
  digitalWrite (INPUT1, HIGH);
  digitalWrite (INPUT2, LOW);
  analogWrite (ENABLE1, speed); //PWM to drive motor
}

//Drive motor backward at the specified speed (0 – 255)
void reverse (int speed)
{
  digitalWrite (ENABLE1, LOW); //Disable H-Bridge
  digitalWrite (INPUT1, LOW);
  digitalWrite (INPUT2, HIGH);
  analogWrite (ENABLE1, speed); //PWM to drive motor
}

//Stop motor
void brake ()
{
  digitalWrite (ENABLE1, LOW); //Disable H-Bridge
  digitalWrite (INPUT1, LOW);
  digitalWrite (INPUT2, LOW);
  analogWrite (ENABLE1, HIGH); //Brake motor
}
