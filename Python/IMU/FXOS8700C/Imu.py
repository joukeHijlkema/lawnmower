#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
#  =================================================
# Trigger
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - jeu. mai 21:53 2017
#   - Initial Version 1.0
#  =================================================

import FXOS8700C

class Imu:
    def __init__(self):
        "docstring"


    ## --------------------------------------------------------------
    ## Description : Init
    ## NOTE : 
    ## -
    ## Author : jouke hylkema
    ## date   : 11-54-2017 21:54:57
    ## --------------------------------------------------------------
    def Init (self):
        self.writeReg(CTRL_REG2, 0x40)
        
    ## --------------------------------------------------------------
    ## Description : write to a register
    ## NOTE : 
    ## -
    ## Author : jouke hylkema
    ## date   : 11-54-2017 21:54:26
    ## --------------------------------------------------------------
    def writeToReg (self,reg,val):
        self.bus.write_byte_data(
