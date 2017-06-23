#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
#  =================================================
# testSignal.py
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - Sat Aug 27 16:59:24 2016
#   - Initial Version 1.0
#  =================================================
import argparse
import subprocess
import re
from datetime import datetime

parser = argparse.ArgumentParser(description='Check GPS signal.')
parser.add_argument('file', help='data file name')

args = parser.parse_args()

print(args.file)

command = "convbin %s"%args.file  # the shell command
process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, shell=True)

#Launch the shell command:
output, error = process.communicate()

out   = output.decode("utf-8").split("\r")[-2]
items = out.split(" ")

FMT = '%H:%M:%S'
start = datetime.strptime(items[1].split("-")[0],FMT)
end   = datetime.strptime(items[2].strip(":"),FMT)
count = items[3].split("=")[1]

print(out)
print("start = %s, end = %s, count = %s"%(start,end,count))
print("%s seconds"%(end-start).seconds)
print("%s seconds per count"%((end-start).seconds/int(count)))
