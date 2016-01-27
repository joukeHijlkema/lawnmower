#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  =================================================
#  zmqClient.py
#   - Author jouke hijlkema <jouke.hijlkema@onera.fr>
#   - Initial Version 1.0
#  =================================================
import zmq

class zmqClient:
    "client for zeromq communication"

    outContext = zmq.Context()
    inContext  = zmq.Context()
    outSocket  = outContext.socket(zmq.PUSH)
    inSocket   = inContext.socket(zmq.SUB)
    name = ""
    string = 0
    poller = zmq.Poller()
    delimiter =":"
    Messages = {}

    def __init__(self,channel,name,adIn,adOut):
        zmqClient.name = name
        zmqClient.inSocket.connect(adIn)
        zmqClient.inSocket.setsockopt(zmq.SUBSCRIBE, channel)
        zmqClient.inSocket.setsockopt(zmq.SUBSCRIBE, "Global")
        print "In  connected to SUB %s subscribed to Global and %s"%(adIn,channel)
        zmqClient.outSocket.connect(adOut)
        print "Out connected to PUSH %s"%adOut

        zmqClient.poller.register(zmqClient.inSocket, zmq.POLLIN)

    def send(self,Out):
        print "sending %s"%Out
        zmqClient.outSocket.send("%s:%s"%(zmqClient.name,Out))

    def receiveNb(self):
        print zmqClient.inSocket.recv()
        socks = dict(zmqClient.poller.poll(0))
        if socks:
            if socks.get(zmqClient.inSocket) == zmq.POLLIN:
                zmqClient.storeMsg(self,zmqClient.inSocket.recv(zmq.NOBLOCK))
                return True
        return False

    def storeMsg(self,msg):
        print "received : %s"%msg
        key   = zmqClient.key(self,msg)
        value = zmqClient.value(self,msg)
        if zmqClient.Messages.has_key(key):
            zmqClient.Messages[zmqClient.key(self,msg)].append(value)
        else:
            zmqClient.Messages[key] = [value]

    def key(self,msg):
        return msg.split(zmqClient.delimiter)[0]

    def value(self,msg):
        return zmqClient.delimiter.join(msg.split(zmqClient.delimiter)[1:])

    def got(self,key,value,erase):
        msgFound = zmqClient.get(self,key,value,erase)
        subKey   = zmqClient.key(self,value)
        return (subKey == value)

    def get(self,key,value,erase):
        out="NotFound"
        if zmqClient.Messages.has_key(key):
            subKey=zmqClient.key(self,value)
            if (subKey == value):
                print zmqClient.Messages[key]
                out=zmqClient.Messages[key][0]
                if erase:
                    del zmqClient.Messages[key][0]
                    if len(zmqClient.Messages[key]) ==0:
                        del zmqClient.Messages[key]
                return out
        return out
