#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  =================================================
#  windSpeed.py
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - Initial Version 1.0
#  =================================================

import RPi.GPIO as GPIO
import time
import math
import thread

class windSpeed:

    pin      = 40
    vTot     = 0
    count    = 0
    lastTime = 0
    l        = math.pi*0.07
    Vmin     = 0.1
    Vmax     = 60.0
    dtMin    = l/Vmax
    dtMax    = l/Vmin

    def __init__(self,_pin):
        self.pin = _pin
        GPIO.setmode(GPIO.BOARD)
        GPIO.setup(self.pin, GPIO.IN)
        GPIO.add_event_detect(self.pin, GPIO.FALLING, callback=self.speedUpdate,bouncetime=10)
        self.mastTime = time.time()

    def speedUpdate(self,channel):
        dt = time.time()-self.lastTime
        print "dt = %f (%f,%f)"%(dt,self.dtMin,self.dtMax)
        self.lastTime = time.time()
        if (dt<self.dtMin or dt>self.dtMax):
            return
        v = self.l/dt
        print "windspeed = %s m/s dt = %s"%(v,dt)
        self.vTot    += v 
        self.count   += 1

    # return a reading
    def read(self):

        if (self.count == 0):
            speed = 0.0
        else:
            speed = self.vTot/self.count
        if (speed < 0.01):
            speed = 0.0
        self.vTot  = 0
        self.count = 0
        return speed
