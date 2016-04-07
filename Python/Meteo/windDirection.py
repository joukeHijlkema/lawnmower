#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  =================================================
#  windDirection.py
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - Initial Version 1.0
#  =================================================
import myMCP3008
import time

class windDirection:

    ADC = myMCP3008.myMCP3008(0)
    Dirs = {925:0,775:90,95:180,290:270,870:45,460:135,186:225,625:315}
    
    def read(self):
        v = self.ADC.ReadChannel(0)
        for k in self.Dirs:
            if (abs(k-v) < 10):
                return self.Dirs[k]
        return -1.0*v
