#!/usr/bin/env python
#
# SPI interface with an MCP3008 ADC device
# MCP3008 is 8-channel 10-bit analog to digital converter
#  Connections are:
#     CLK => SCLK
#     DOUT =>  MISO
#     DIN => MOSI
#     CS => CE0

import time
import sys
import spidev


class myMCP3008:
    spi = spidev.SpiDev()

    def __init__(self, channel):
        if ((channel > 7) or (channel < 0)):
            return -1
        self.spi.open(0, 0)
        self.channel = channel
        self.readCommand = [0x01, 0x08 | (self.channel << 4), 0]

    def processAdcValue(self,result):
        '''Take in result as array of three bytes.
           Return the two lowest bits of the 2nd byte and
           all of the third byte'''
        byte2 = (result[1] & 0x03)
        return (byte2 << 8) | result[2]

    def read(self):
        r = self.spi.xfer2(self.readCommand)
        return self.processAdcValue(r)

    # Function to read SPI data from MCP3008 chip
    # Channel must be an integer 0-7
    def ReadChannel(self,channel):
        adc = self.spi.xfer2([1,(8+channel)<<4,0])
        data = ((adc[1]&3) << 8) + adc[2]
        return data

    