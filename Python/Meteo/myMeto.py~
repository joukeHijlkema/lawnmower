#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  =================================================
#  myMeto.py
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - Initial Version 1.0
#  =================================================

import time
from rainMeter import rainMeter
from windSpeed import windSpeed
from windDirection import windDirection
from TempEtc import Temp
from dataBase import dataBase
from datetime import datetime

db = dataBase("Meteo","!Meteo","localhost","Meteo")

myRain      = rainMeter(38)
myWindSpeed = windSpeed(40)
myWindDir   = windDirection()
myTemp      = Temp()

while True:
    r  = myRain.read()
    ws = myWindSpeed.read()
    wd = myWindDir.read()
    t = myTemp.readTemp()
    h = myTemp.readHumidity()
    p = myTemp.readPressure()
    db.Put(("INSERT INTO Mesurements "
            "(Time,Rain,WindSpeed,WindDirection,Temperature,Humidity,Pressure)"
            "VALUES (%s,%s,%s,%s,%s,%s,%s)"),
       (datetime.now(),r,ws,wd,t,h,p))

    print "time        : %s "%datetime.now()
    print "rain        : %s mm"%r
    print "windspeed   : %s m/s"%ws
    print "wind dir    : %s °"%wd
    print "temperature : %s°"%t
    print "pressure    : %s Pa"%p
    print "humidity    : %s %%"%h
    print "======================="
    time.sleep(900)

GPIO.cleanup()           # clean up GPIO on normal exit
