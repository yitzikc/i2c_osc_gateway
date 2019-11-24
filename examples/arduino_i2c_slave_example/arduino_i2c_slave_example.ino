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
  // Wire.onRequest(onReq);
  Wire.onReceive(receiveEvent);

  Serial.begin(115200);
  // Serial.print("ISR installed\n");
  
  // Setup pin 13 as output and turn LED off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

/*void onReq()
{
  Serial.print("ISR Request");
  return;
}
*/


// Function that executes whenever data is received from master
void receiveEvent(int howMany) {
  if (0 == howMany) {
    return;
  }

  const uint8_t function_addr = Wire.read();
  I2CTimedMesssage message {};
  message.ReceiveFromWire();
  
  Serial.print("Got message to function ");
  Serial.print(function_addr);
  Serial.print(" value: 0x");
  message.DebugPrint();
  Serial.println("");
  return;
}

void loop() {
  delay(100);
}
