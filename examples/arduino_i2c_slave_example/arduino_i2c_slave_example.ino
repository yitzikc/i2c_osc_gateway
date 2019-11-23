/*
  Arduino Slave for Raspberry Pi Master
  i2c_slave_ard.ino
  Connects to Raspberry Pi via I2C
  
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/
 
// Include the Wire library for I2C
#include <Wire.h>

struct I2CMesssage {
  union {
    int32_t value = 0;
    unsigned char value_bytes[4];
  };
  unsigned char time_spec[4] {};

  void DebugPrint() const
  {
    Serial.print(value, HEX);
    Serial.print(" = ");
    Serial.print(value);
  }
};

static_assert(sizeof(I2CMesssage) == 8, "Unexpected message size");
 
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
  I2CMesssage message {};

  // Note: the loop below assumed little-endian
  for (int i = 0; (i < 4) && Wire.available(); ++i) {
    message.value_bytes[i] = Wire.read();
  }

  for (int i = 0; (i < 4) && Wire.available(); ++i) {
    message.time_spec[i] = Wire.read();
  }
  
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
