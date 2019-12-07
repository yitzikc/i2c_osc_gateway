/*
  Arduino Slave for Raspberry Pi Master
  i2c_slave_ard.ino
  Connects to Raspberry Pi via I2C
  
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/

// TODO: Move common code to C++ file. see: https://arduino.stackexchange.com/questions/61634/multiple-ino-files-in-the-same-sketch


// Include the Wire library for I2C
#include <Wire.h>

#include "I2CTimedMessage.h"
 
// LED on pin 13
enum PinAssignments {
 ledPin = 13
};

void setup() {
  // Join I2C bus as slave with address 8
  Wire.begin(0x08);
  
  // Call receiveEvent when data received
  Wire.onRequest(onReq);
  Wire.onReceive(receiveEvent);

  Serial.begin(115200);
  // Serial.print("ISR installed\n");
  
  // Setup pin 13 as output and turn LED off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

static byte function_addr = -1;
static I2CTimedMesssage message {};

void onReq()
{
  message.SendToWire();
  Serial.print("Responding to function 0x");
  Serial.print(function_addr, HEX);
  Serial.print(" ");
  message.DebugPrint();
  Serial.println("");
  return;
}

// Function that executes whenever data is received from master
void receiveEvent(int howMany) {
  if (0 == howMany) {
    return;
  }

  function_addr  = Wire.read();
  
  message.ReceiveFromWire();
  Serial.print("Got message to function 0x");
  Serial.print(function_addr, HEX);
  Serial.print(" value: ");
  message.DebugPrint();
  Serial.println("");
  return;
}

void loop() {
  delay(100);
}
