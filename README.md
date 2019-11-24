# I2C OSC Gateway

A Python and Arduino library bridging between Open Sound Control (OSC) messages and devices on an I2C bus, easing the use of ```pythonosc```.

The library allows software which can use the OSC protocol for real-time control of devices, which is commonly used in music and sound applications, to control hardware  devices on an I2C bus, which typically wouldn't be network-enabled. It provides the building block for a Python server to listen for OSC messages arriving over UDP on topics and route them to the corresponding devices on an I2C bus, according to the topic set in
the OSC header.

## Usage

The I2CDevice in i2c_device.py allows both sides of the mapping to be defined.
The arguments passed to its constructor determine the OSC topic on one hand, and the bus address and memory address on the device on the other hand.

The I2COscDispatcher class in i2c_osc_dispatcher.py acts as a wrapper around the Dispatcher class in the ```pythonosc``` package.

The Arduino library is in the _arduino_ subdirectory. It provides a C++ class for receiving messages sent from the Python code.

See below examples/blocking_gateway.py for simple usage of both classes.

## Protocols

### OSC Topics

The OSC topics are in the format devices/_Device class_/_Device number_/_Function_
_Device class_, _Device number_, and _Function_ are specified by the user.

### I2C Bus Addresses

I2C Bus addressed comprise the address to which the device responds on the bus, and a base address in its logical
memory space.

Every write will be of 8 bytes:

## Message format

Messages are 8 bytes long in total.

* bytes for the value, as a signed little-endian integer.
* 4 bytes for time, which is used to indicate a future time for execution, in a format compatible with SMPTE. The format ```[0h:2m:23s:12f]``` where the hour is in the MSB, and the LSB gives teh SMPTE frame in the range 0 .. 30. Each byte will be an unsigned integer. The time bytes are treated as unsigned.

## Examples

The I2CDevice in i2c_device.py allows both sides of the mapping to be defined. All the examples are built to run together, with compatible settings:

* OSC topic "/devices/light/1/rgb"
* I2C device address 0x08
* Address 0x100 in the device's address-space.

The examples provided:

* blocking_gateway.py: A simple blocking server, making use of the I2CDevice and I2COscDispatcher classes.
* arduino_i2c_slave_example: Arduino programme that implements the device side of the protocol
* chuck_sample.ck: A programme in the language Chuck, which sends OSC messages to blocking_gateway.py
