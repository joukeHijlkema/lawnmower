#!/usr/bin/env bash

rm -f /home/pi/GPS/sol1.pos

cp -f /home/pi/GPS/conf$1/*  /home/pi/GPS

device=$(find /dev/ttyACM*  -printf "%f\n")
sed -e "s|ttyACM[0-9]|$device|" /home/pi/GPS/myRtk.conf > /tmp/myRtk.conf && mv -f /tmp/myRtk.conf /home/pi/GPS/myRtk.conf


