#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  =================================================
#  dataBase.py
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - Initial Version 1.0
#  =================================================

import sqlite3

class dataBase:
    """docstring for dataBase   """
    def __init__(self, file):
        self.conn = sqlite3.connect(file)
        print "Opened database successfully";
