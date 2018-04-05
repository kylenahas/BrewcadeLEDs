import serial
import sys
import time

sp = serial.Serial()
sp.baudrate = 9600

filename = "/home/leds/leds/conf/conf-lcd.txt"

data = []

try:
    initFile = open(filename, "r")
    data = initFile.read().splitlines()

    initFile.close()
except IOError:
    print "There was an error reading from", filename
    sp.close()
    sys.exit()

sp.port = data[0]
try:
    sp.open()
except:
    print "There was an error opening the serial port", data[0]

while 1:
    try:
        file = open(filename, "r")
        data = file.read().splitlines()

        if data[0] != sp.port:
            sp.close()
            sp.port = data[0]
            sp.open()

        sp.write(data[1])
    except IOError:
        print "2: There was an error reading from", filename
        sp.close()
        sys.exit()  

    time.sleep(1)

sp.close()