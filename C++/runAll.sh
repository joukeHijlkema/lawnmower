#!/bin/bash
xterm -e ./grasmaaier.exe&
sleep 5
xterm -e $1 ./Motor.exe&
xterm -e $1 ./GPS.exe&
xterm -e $1 ./Blades.exe&
xterm -e $1 ./Battery.exe&
xterm -e $1 ./Direction.exe&
