/*
  IR Controlled Vehicle
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/probable-palm-tree/blob/master/LICENSE
*/

#include <IRremote.h>
//Remote code definitions
const long FORWARD = 0xB946FF00;
const long REVERSE = 0xEA15FF00;
const long RIGHT = 0xBC43FF00;
const long LEFT = 0xBB44FF00;
const long STOP = 0xBF40FF00;
const long LOW_SPEED = 0xE916FF00;
const long MEDIUM_SPEED = 0xE619FF00;
const long TOP_SPEED = 0xF20DFF00;
//pin assignments
const int RECEIVER = 12;
const int ENABLE1 = 6;
const int INPUT1 = 4;
const int INPUT2 = 5;
const int ENABLE2 = 9;
const int INPUT3 = 7;
const int INPUT4 = 10;

//variables
int vehicleSpeed = 150;
long remoteCode = 0;
String direction = "stop";


void setup() {
  pinMode(ENABLE1, OUTPUT);
  pinMode(INPUT1, OUTPUT);
  pinMode(INPUT2, OUTPUT);
  pinMode(ENABLE2, OUTPUT);
  pinMode(INPUT3, OUTPUT);
  pinMode(INPUT4, OUTPUT);
  Serial.begin(9600);  //Only needed for troubleshooting
  IrReceiver.begin(RECEIVER, ENABLE_LED_FEEDBACK);
  brake("left");
  brake("right");
}

void loop() {
  //First read the remote
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);  //used for debug only
    IrReceiver.printIRResultShort(&Serial); // optional use new print version
    remoteCode = IrReceiver.decodedIRData.decodedRawData;
    Serial.print("Remote code: ");
    Serial.println(remoteCode, HEX);
    switch (remoteCode) {
      case (FORWARD):
        {
          Serial.println("Forward");
          forward("left", vehicleSpeed);
          forward("right", vehicleSpeed);
          break;
        }
      case (REVERSE):
        {
          Serial.println("Reverse");
          reverse("left", vehicleSpeed);
          reverse("right", vehicleSpeed);
          break;
        }
      case (RIGHT):
        {
          Serial.println("Right");
          forward("left", 255);
          forward("right", 150);
          break;
        }
      case (LEFT):
        {
          Serial.println("left");
          forward("left", 150);
          forward("right", 255);
          break;
        }
      case (STOP):
        {
          Serial.println("Stop");
          brake("left");
          brake("right");
          break;
        }
      case (LOW_SPEED):
        {
          Serial.println("Low speed");
          vehicleSpeed = 150;
          break;
        }
      case (MEDIUM_SPEED):
        {
          Serial.println("Medium speed");
          vehicleSpeed = 200;
          break;
        }
      case (TOP_SPEED):
        {
          Serial.println("Top speed");
          vehicleSpeed = 255;
          break;
        }
      default:
        {
          //do nothing
        }
    }
    IrReceiver.resume();  // receive the next value
  }
  delay(50);
}

void forward(String motor, int speed) {

  if (motor == "left") {
    digitalWrite(ENABLE1, LOW);  //Disable H-Bridge
    digitalWrite(INPUT1, HIGH);
    digitalWrite(INPUT2, LOW);
    analogWrite(ENABLE1, speed);  //PWM to drive left motor
  } else {
    digitalWrite(ENABLE2, LOW);  //Disable H-Bridge
    digitalWrite(INPUT3, HIGH);
    digitalWrite(INPUT4, LOW);
    analogWrite(ENABLE2, speed);  //PWM to drive right motor
  }
}

//Drive motor backward at the specified speed (0 – 255)
void reverse(String motor, int speed) {
  if (motor == "left") {
    digitalWrite(ENABLE1, LOW);  //Disable H-Bridge
    digitalWrite(INPUT1, LOW);
    digitalWrite(INPUT2, HIGH);
    analogWrite(ENABLE1, speed);  //PWM to drive left motor
  } else {
    digitalWrite(ENABLE2, LOW);  //Disable H-Bridge
    digitalWrite(INPUT3, LOW);
    digitalWrite(INPUT4, HIGH);
    analogWrite(ENABLE2, speed);  //PWM to drive right motor
  }
}

//Stop motor
void brake(String motor) {
  if (motor == "left") {
    digitalWrite(ENABLE1, LOW);  //Disable H-Bridge
    digitalWrite(INPUT1, LOW);
    digitalWrite(INPUT2, LOW);
    analogWrite(ENABLE1, HIGH);  //Brake left motor
  } else {
    digitalWrite(ENABLE2, LOW);  //Disable H-Bridge
    digitalWrite(INPUT3, LOW);
    digitalWrite(INPUT4, LOW);
    analogWrite(ENABLE2, HIGH);  //Brake right motor
  }
}