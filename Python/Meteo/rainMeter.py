#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  =================================================
#  rainMeter.py
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - Initial Version 1.0
#  =================================================

import RPi.GPIO as GPIO
import math
import time
import thread

class rainMeter:

    pin = 38
    # 1 click = 2.0 ml = 2000 mm³ , Surface = 5319.54 mm² => 1 click = 0.282 mm of rain
    vol = 0.376
    count = 0
    down = False
    t1 = 0
    t2 = 0
    dtMin = 0.01
    dtMax = 0.6
    testDtMin = 1.0
    testDtMax = 0.0

    def __init__(self, _pin):
        self.pin = _pin
        GPIO.setmode(GPIO.BOARD)
        GPIO.setup(self.pin, GPIO.IN)
        # GPIO.add_event_detect(self.pin, GPIO.BOTH, callback=self.runMonitor)
        GPIO.add_event_detect(self.pin, GPIO.FALLING, callback=self.runMonitor2,bouncetime=200)

    def runMonitor(self,channel):
        if (self.down):
            self.down = False
            self.t2 = time.time()
            dt = self.t2-self.t1
            self.testDtMin = min(dt,self.testDtMin)
            self.testDtMax = max(dt,self.testDtMax)
            print "dt = %s (%s,%s)"%(dt,self.testDtMin,self.testDtMax)
            
            if (dt>=self.dtMin and dt<self.dtMax):
                self.count+=1
                print "rain\n\n"
        else:
            self.down = True
            self.t1  = time.time()
            
    def runMonitor2(self,channel):
        self.count+=1
        print "rain : %d %s"%(self.count,str(time.time()))

    def read(self):
        return self.count*self.vol