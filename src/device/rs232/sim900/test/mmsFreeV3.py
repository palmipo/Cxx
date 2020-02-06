#!/usr/bin/env python3
import time
import serial
import os
import sys


def simSendWithNoAnswer(cmd):
    cmd_b = cmd.encode()
    ser.write(cmd_b)
    print(ser.readline())#Copy of command

def simSend(cmd):
    cmd_b = cmd.encode()
    ser.write(cmd_b)
    print(ser.readline())#Copy of command
    print(ser.readline().decode())#answer

def checkModuleAvailability():
    value = b''
    while value !=b'OK\r\n':
        simSendWithNoAnswer("AT\r")
        value = ser.readline()
        if value == b'':
            time.sleep(5)
        else:
            print(value)

def sendMMS():
    retry = 2
    value = b''
    while retry:
        value = b''
        print(retry)
        simSendWithNoAnswer("AT+CMMSSEND\r")
        while ("OK" not in value.decode()) and ("ERROR" not in  value.decode()) :
            value = ser.readline()
            #print("Dbg while")
            if value == b'':
                #print("Dbg if")
                print('.', end='', flush=True)
                time.sleep(2)
            else:
                #print("Dbg else")
                print(value.decode())
                if "OK" in value.decode():
                    print(" dbg ok")
                    retry = 0 
                    break
                if "ERROR" in value.decode():
                    print("dbg NOK")
                    retry = retry - 1

phoneNb = "+33670170343"
MMSCenterUrl = "http://mms.free.fr"
MMSProxyIP = "212.27.40.225"
MMSPort ="80"
BearerParam = "3,1,\"Contype\",\"GPRS\""
BearerParam2="3,1,\"APN\",\"mmsfree\"\r"
BearerParam3="1,1\r"
picPath = str(sys.argv[1])
text="hello"
mmsText = text.encode()

pic = open(picPath,"rb")
#picEncoded =( pic.read()).encode("base64")
picSize=os.path.getsize(picPath)
print(picSize)

ser = serial.Serial('/dev/ttyAMA0')
ser.baudrate=115200

ser.timeout = 2
ser.xonxoff=False
ser.reset_input_buffer()
ser.reset_output_buffer()
print("Begin session on V3.1")
time.sleep(3)
print("Session on",ser.name,"opened with success")

checkModuleAvailability()

simSend("AT+CMMSINIT\r")

time.sleep(0.5)

print("starting configuring mms settings")

simSend("AT+CMMSSENDCFG=6,2,0,0,2,4,2,1\r")

simSend("AT+CMMSCURL=\""+MMSCenterUrl+"\"\r")

time.sleep(0.5)

simSend("AT+CMMSPROTO=\""+MMSProxyIP+"\","+MMSPort+"\r")

time.sleep(0.5)

simSend("AT+SAPBR="+BearerParam+"\r")

time.sleep(0.5)

simSend("AT+SAPBR="+BearerParam2+"\r")

time.sleep(0.5)

simSend("AT+SAPBR="+BearerParam3+"\r")

time.sleep(0.5)

simSend("AT+CMMSEDIT=1\r")

time.sleep(0.5)

print("sending picture")

simSend("AT+CMMSDOWN=\"PIC\","+str(picSize)+",100000\r")

print("sending data")
#ser.write(pic.encode("base64"))

offset = 0
MTU = 50
while (offset < picSize):
        pic.seek(offset, 0)
        if picSize - offset > MTU:
                ser.write(pic.read(MTU))
        else:
                MTU = picSize - offset
                ser.write(pic.read(MTU))
                print(str(MTU))
        offset = offset + MTU
        time.sleep(0.01)
       # print(str(offset))
#print(ser.readline())
line = ser.read()
while line :
        line =ser.read()
        print(line)

#simSend("AT+CMMSDOWN=\"TEXT\","+str(5)+",10000\r")
#print(ser.readline())

#ser.write(mmsText)
#print(ser.readline())

simSend("AT+CMMSRECP=\""+phoneNb+"\"\r")

time.sleep(2)

#simSend("AT+CMMSVIEW\r")
#print(ser.readline())

print("get the mms being sent")

sendMMS()

simSend("AT+CMMSEDIT=0\r")

simSend("AT+CMMSTERM\r")

ser.close()
