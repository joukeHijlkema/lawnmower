#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  =================================================
# Trigger
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - dim. mars 15:20 2017
#   - Initial Version 1.0
#  =================================================
import smbus
import math
from LSM9DS0 import *
import datetime
import numpy as np
import time

import threading

class Acc(threading.Thread):

    # scale = 0b00000000 #+/- 2G full scale
    # scale = 0b00001000 #+/- 4G full scale
    scale = 0b00010000 #+/- 6G full scale
    # scale = 0b00011000 #+/- 8G full scale
    # scale = 0b00100000 #+/- 16G full scale

    GAIN = {}
    GAIN[0b00000000] = 0.061
    GAIN[0b00001000] = 0.122
    GAIN[0b00010000] = 0.183
    GAIN[0b00011000] = 0.244
    GAIN[0b00100000] = 0.732

    nbPnts = 1000
    Coords = np.zeros((nbPnts,3))

    T0 = 0
    T1 = 0

    regL = [OUT_X_L_A,OUT_Y_L_A,OUT_Z_L_A]
    regH = [OUT_X_H_A,OUT_Y_H_A,OUT_Z_H_A]

    def __init__(self):
        "docstring"
        super(Acc, self).__init__()
        self.bus = smbus.SMBus(1)

        #initialise the accelerometer
        self.bus.write_byte_data(ACC_ADDRESS , CTRL_REG1_XM, 0b01100111) #z,y,x axis enabled, continuos update,  100Hz data rate
        self.bus.write_byte_data(ACC_ADDRESS , CTRL_REG2_XM, self.scale) 

        # calibrate
        print "Accellerometer calibrating ..."

        for i in range(self.nbPnts):
            self.Coords[i] = self.readSensor()

        self.Corr=self.Coords.mean(0)
        # self.Corr.fill(1.0)

    def run(self):
       
        print "Accelerometer running"

        self.T0 = time.time()
        self.T1 = time.time()
        while 1:
            self.poll()
            time.sleep(0.01)
        
    ## --------------------------------------------------------------
    ## Description :do a reading
    ## NOTE :
    ## -
    ## Author : jouke hylkema
    ## date   : 12-30-2017 15:30:00
    ## --------------------------------------------------------------
    def Read (self):
        out     = [self.T1-self.T0,self.conv(self.Coords.mean(0))]
        self.T0 = self.T1
        self.Coords.fill(0)
        return out

    ## --------------------------------------------------------------
    ## Description :convert to m/s²
    ## NOTE :
    ## -
    ## Author : jouke hylkema
    ## date   : 18-37-2017 12:37:50
    ## --------------------------------------------------------------
    def conv (self,v):
        return 9.81*v*self.GAIN[self.scale]/1000

    ## --------------------------------------------------------------
    ## Description :read the sensor
    ## NOTE :
    ## -
    ## Author : jouke hylkema
    ## date   : 18-29-2017 15:29:02
    ## --------------------------------------------------------------
    def readSensor (self):
        out = np.zeros(3)

        for i in range(3):
        
            acc_l = self.bus.read_byte_data(ACC_ADDRESS, self.regL[i])
            acc_h = self.bus.read_byte_data(ACC_ADDRESS, self.regH[i])
	    acc_combined = (acc_l | acc_h <<8)

	    out[i] = acc_combined  if acc_combined < 32768 else acc_combined - 65536

        return out
        
    ## --------------------------------------------------------------
    ## Description : poll the sensor
    ## NOTE :
    ## -
    ## Author : jouke hylkema
    ## date   : 18-30-2017 13:30:24
    ## --------------------------------------------------------------
    def poll (self):
        self.Coords    = np.roll(self.Coords,1,0)
        self.Coords[0] = self.readSensor()-self.Corr
        self.T1        = time.time()
