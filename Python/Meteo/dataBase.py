#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  =================================================
# dataBase
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - Sun Mar 13 16:20:33 2016
#   - Initial Version 1.0
#  =================================================
import mysql.connector

class dataBase:

    def __init__(self,_user,_password,_host,_database):

        try:
            self.cnx = mysql.connector.connect(user=_user, password=_password, host=_host, database=_database)
        except mysql.connector.Error as err:
            if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
                print("Something is wrong with your user name or password")
            elif err.errno == errorcode.ER_BAD_DB_ERROR:
                print("Database does not exist")
            else:
                print(err)
        else:
            print "connection OK"
        
    def Put(self,What,Values):
        while not self.cnx.is_connected():
            self.cnx.reconnect()
            print "reconnecting to db"
        cursor = self.cnx.cursor()
        cursor.execute(What,Values)
        self.cnx.commit()
        cursor.close()
    
    
        
