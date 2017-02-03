#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  =================================================
#  test.py
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - Initial Version 1.0
#  =================================================

import zmq
import time

context = zmq.Context()
socket  = context.socket(zmq.PUB)
socket.bind("tcp://134.212.97.63:5060")

for n in range (5):
    time.sleep(1)
    socket.send_multipart(["Global","%s"%n])
    print "send 'Global %s'"%n
    
    
    
