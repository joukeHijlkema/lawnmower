#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  =================================================
#  temp.py
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - Initial Version 1.0
#  =================================================
from Adafruit_BME280 import *
import time

class Temp:

    Sensor = BME280(mode=BME280_OSAMPLE_8)

    def readTemp(self):
        return self.Sensor.read_temperature()
    def readHumidity(self):
        return self.Sensor.read_humidity()
    def readPressure(self):
        return self.Sensor.read_pressure()
        

        

        
