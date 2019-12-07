#include <Arduino.h>
#include <Wire.h>


#include "I2CTimedMessage.h"

void I2CTimedMesssage::DebugPrint() const
{
  Serial.print("0x");
  Serial.print(value, HEX);
  Serial.print(" = ");
  Serial.print(value);
}

void I2CTimedMesssage::ReceiveFromWire()
{
  // Note: the loop below assumed little-endian
  for (int i = 0; (i < 4) && Wire.available(); ++i) {
    value_bytes[i] = Wire.read();
  }

  for (int i = 0; (i < 4) && Wire.available(); ++i) {
    time_spec[i] = Wire.read();
  }

  return;
}

void I2CTimedMesssage::SendToWire()
{
  Wire.write(value_bytes, sizeof(value_bytes));
}
