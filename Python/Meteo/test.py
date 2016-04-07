#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  =================================================
# test
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - Sun Mar 13 16:42:55 2016
#   - Initial Version 1.0
#  =================================================

import time
from rainMeter import rainMeter

myRain      = rainMeter(38)

while True:
    r  = myRain.read()

    print "rain        : %s mm"%r
    print "======================="
    time.sleep(60)

GPIO.cleanup()           # clean up GPIO on normal exit
