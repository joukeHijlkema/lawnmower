#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  =================================================
# Trigger
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - dim. mars 15:20 2017
#   - Initial Version 1.0
#  =================================================
import time

from Acceleration import Acc
import numpy as np

myAcc = Acc()

P  = np.zeros(3)
A  = np.zeros(3)
V  = np.zeros(3)

Vmin = np.ones(3)*0.5
dt   = 1

myAcc.start()

while 1:
    
    print "-------------------------------------------------"
    
    R   = myAcc.Read()
    rdt = R[0]
    A   = R[1]
    V  += A*rdt
    V   = np.where(V>Vmin,V,0)
    P  += V*rdt
        
    print "dt = %f"%rdt
    print "accelaration (m/s²): %10.8g, %10.8g, %10.8g"%(A[0],A[1],A[2])
    print "speed         (m/s): %10.8g, %10.8g, %10.8g"%(V[0],V[1],V[2])
    print "position        (m): %10.8g, %10.8g, %10.8g"%(P[0],P[1],P[2])

    time.sleep(dt)
