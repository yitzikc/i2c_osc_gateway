import typing
import logging

import pythonosc.dispatcher

import i2c_device

logger = logging.getLogger(__name__)


class I2COscDispatcher(pythonosc.dispatcher.Dispatcher):
    @classmethod
    def default_handler(cls, address, *args):
        logger.warning("Ignored message for unknown device %s: %s",
                address, args_with_types(args))

    def __init__(self, devices: typing.Sequence[i2c_device.I2CDevice]):
        super().__init__()
        self.set_default_handler(self.default_handler)
        for dev in devices:
            self.map(dev.topic, dev.write)


def args_with_types(args: typing.Iterable):
    return [(type(a).__name__, a) for a in args]
