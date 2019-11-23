#!/usr/bin/env python3

""" Example gateway that uses the supplied classes to run a simple
blocking OSC server
"""


import typing
import sys
import os.path as osp

import logging
logger = logging.getLogger(__name__)
logging.basicConfig(level = logging.INFO)

from pythonosc.osc_server import BlockingOSCUDPServer

sys.path.append(osp.join(osp.dirname(osp.realpath(__file__)), ".."))

import i2c_device
import i2c_osc_dispatcher

# TODO: Specify devices in a data file, or perhaps even by probing the I2C bus

devices = [
    i2c_device.I2CDevice("light", 1, "rgb", 0x08, 0x100)
]

def main():
    dispatcher = i2c_osc_dispatcher.I2COscDispatcher(devices)

    port = 6449
    logger.setLevel(logging.INFO)

    server = BlockingOSCUDPServer(("0.0.0.0", port), dispatcher)
    server.serve_forever()  # Blocks forever

if __name__ == "__main__":
    main()
