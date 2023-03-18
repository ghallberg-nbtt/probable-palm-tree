/*
  Reading IR Remote Codes
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/probable-palm-tree/blob/master/LICENSE
*/

#include <IRremote.hpp>

const int RECEIVER = 2;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECEIVER, ENABLE_LED_FEEDBACK); // Start the receiver
}

void loop() {
if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
      IrReceiver.printIRResultShort(&Serial); // optional use new print version
      IrReceiver.resume(); // Enable receiving of the next value
  }
}
