#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  =================================================
#  test.py
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - Initial Version 1.0
#  =================================================

from zmqClient import zmqClient

myClient = zmqClient("GpsBase","GpsBase","tcp://192.168.1.32:4245","tcp://192.168.1.32:4244")

for i in range(10):
    myClient.send("Alive")
