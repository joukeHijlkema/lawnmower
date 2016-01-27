#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  =================================================
#  gpsError.py
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - Initial Version 1.0
#  =================================================

import MySQLdb
import random
import matplotlib.pyplot as plt
import math

db = MySQLdb.connect(host="192.168.1.102",
                     user="root",
                     passwd="ptc:89",
                     db="Grasmaaier",
                     use_unicode=1,charset='utf8')

cursor = db.cursor()

def Query(SqlStr):
  print(SqlStr)
  cursor.execute(SqlStr)
  db.commit()
  return cursor.fetchall()

# for i in range(100):
#     Query("INSERT INTO data (lon,lat) VALUE (%f,%f)"%(random.random(),random.random()))

out = Query ("SELECT Lon,Lat FROM Maaier")
N = len(out)
print "%f measurements"%N
X = []
Y = []

for x,y in out:
    # print ("%f,%f"%(x,y))
    X.append(x)
    Y.append(y)


fixLat=43.168591
fixLon=1.191872
m_per_deg_lat = 111132.954 - 559.822 * math.cos( 2 * fixLat ) + 1.175 * math.cos( 4 * fixLat);
m_per_deg_lon = 111132.954 * math.cos ( fixLon );

print "m/deg lon: %f lat:%f"%(m_per_deg_lon,m_per_deg_lat)

print "error lon : %f"%((max(X)-min(X))*m_per_deg_lon)
print "error lat : %f"%((max(Y)-min(Y))*m_per_deg_lat)

plt.scatter(X,Y,1)

plt.show()
