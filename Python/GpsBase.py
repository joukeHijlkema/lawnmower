#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  =================================================
#  GpsBase.py
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - Initial Version 1.0
#  =================================================

from zmqClient import zmqClient
from Item import Item
from adresses import PILOT_IN,PILOT_OUT
from dataBase import dataBase
import gps

class GpsBase (Item):

    db = 0
    gpsSession = 0

    def __init__(self):
        GpsBase.com = zmqClient("GpsBase","GpsBase",PILOT_IN,PILOT_OUT)
        # Gpsbase.db  = dataBase("/home/pi/gpsBase.db")
        # GpsBase.db  = dataBase("/home/hylkema/gpsBase.db")
        # GpsBase.gpsSession = gps(**opts)
        # GpsBase.gpsSession.stream(WATCH_ENABLE|WATCH_NEWSTYLE)

    def parse(self):
        print "Parsing GpsBase"
        if GpsBase.com.got("Global","Quit",True) or  GpsBase.com.got(item.com.name,"Quit",True):
            GpsBase.quit=True
        if GpsBase.com.got("Global","Alive?",True):
            GpsBase.com.send("Alive")
        return


if __name__ == '__main__':
    myBase = GpsBase();
    while (1):
        if myBase.com.receiveNb():
            myBase.parse()
