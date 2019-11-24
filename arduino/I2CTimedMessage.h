#ifndef _I2C_TIMED_MESSAGE_H_
#define _I2C_TIMED_MESSAGE_H_

#include <ctype.h>

struct I2CTimedMesssage {
  union {
    int32_t value = 0;
    unsigned char value_bytes[4];
  };
  unsigned char time_spec[4] {};

  void ReceiveFromWire();

  void DebugPrint() const;
};

static_assert(sizeof(I2CTimedMesssage) == 8, "Unexpected message size");

#endif // #ifndef _I2C_TIMED_MESSAGE_H_
