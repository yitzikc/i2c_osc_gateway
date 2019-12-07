import typing
import struct
import math
import logging
logger = logging.getLogger(__name__)

try:
    import smbus
except ImportError:
    logger.warning("SMBus support is not installed")
    smbus = None

class I2CDevice:
    TOPIC_PREFIX = "devices"
    # LTC time reference frames / sec
    LTC_FPS = 30
    I2C_BUS = 1

    MessageFormat = struct.Struct("<iBBBB")

    def __init__(self, dev_class: str, dev_num, dev_function, i2c_addr: int, function_addr: int):
        self.dev_class = dev_class
        self.dev_num = dev_num
        self.dev_function = dev_function
        self.i2c_addr = i2c_addr
        self.function_addr = function_addr

        self.i2c = None
        if smbus is not None:
            try:
                self.i2c = smbus.SMBus(self.I2C_BUS)
            except FileNotFoundError:
                self.warning("Unable to open I2C bus %d", self.I2C_BUS)

    @property
    def topic(self):
        return f"/{self.TOPIC_PREFIX}/{self.dev_class}/{self.dev_num}/{self.dev_function}"

    def write(self, topic, value: int, timing_spec: typing.SupportsFloat = 0, *args):
        # FIXME: Support also timing specs as int or float, which would be in seconds
        total_secs = math.floor(float(timing_spec) // 1)
        total_mins, secs = total_secs // 60, total_secs % 60
        hours, mins = total_mins // 60, total_mins % 60
        # Frame for LTC 30 fps
        frame = round(self.LTC_FPS * float(timing_spec)) % self.LTC_FPS
        if self.is_connected:
            message = list(
                self.MessageFormat.pack(value, hours, mins, secs, frame))
            try:
                self.i2c.write_i2c_block_data(self.i2c_addr, self.function_addr, message)
                logging.info("Wrote to device %s value %d (0x%x) for time %d f%d",
                    topic, value, int(value), total_secs, frame)
            except OSError:
                logger.error("Unable to write to I2C device 0x%x (%d)", self.i2c_addr, self.i2c_addr)

        if args:
            logging.warning("Ignoring unknown args: %s", args)

    def read(self, topic = None):
        if self.is_connected:
            try:
                result = self.i2c.read_i2c_block_data(self.i2c_addr, self.function_addr, 4)
                as_bytes = "".join(map(chr, result)).encode()
                return struct.Struct("<i").unpack(as_bytes)
            except OSError:
                logger.error("Unable to read from I2C device 0x%x (%d)", self.i2c_addr, self.i2c_addr)

        return None

    @property
    def is_connected(self):
        return self.i2c is not None
