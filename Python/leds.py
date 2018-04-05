import sys
import serial
import time
import datetime
from serial.tools import list_ports

print(list(list_ports.comports()))

#filename = "conf.txt"
filename = "/home/leds/leds/conf/conf.txt"
data = [0, 0, 0, 0, 0]
lastdata = [0, 0, 0, 0, 0]
ledsPowerSetting = True
lastLedsPowerSetting = False

currentTime = datetime.datetime.now()
onTime = datetime.datetime.now()
offTime = datetime.datetime.now()


class TeensySerial:
    def __init__(self, baudrate):
        self.teensy_port = self.getTeensyPort()
        self.ser = serial.Serial(self.teensy_port[0], baudrate, timeout=5)

    def getTeensyPort(self):
        """Discover where is Teensy."""
        ports_avaiable = list(list_ports.comports())
        teensy_port = tuple()
        for port in ports_avaiable:
            if port[2].startswith("USB VID:PID=16c0:0483") or port[2].startswith("USB VID:PID=16c0:483"):
                teensy_port = port
        if teensy_port:
            return teensy_port

    def close(self):
        if self.ser.isOpen():
            self.ser.close()


def parseInput():
    global ledsPowerSetting
    global lastdata

    global onTime
    global offTime

    if data != lastdata:
        for ind in range(len(data)):                
            if data[ind] != lastdata[ind]:
                #print "Index changed: "
                if ind == 0: # Brightness
                    print "Brightness Changed"
                    teensy.ser.write("B" + data[ind] + "\n")
                    teensy.ser.flush() 
                    print ">" + teensy.ser.readline()
                if ind == 1: #On/Off
                    if data[ind] == "On":
                        ledsPowerSetting = True
                    else:
                        ledsPowerSetting = False
                    print "Power Status Changed to: " + str(ledsPowerSetting)
                if ind == 2: #Pattern number
                    print "Pattern Changed"
                    teensy.ser.write("D" + data[ind] + "\n")
                    teensy.ser.flush() 
                    print ">" + teensy.ser.readline()
                if ind == 3: #Start Time
                    #
                    print "Time On Changed"
                if ind == 4: #End Time
                    #
                    print "Time Off Changed" 
            teensy.ser.flush()       
        #print data
        lastdata = data
        return True
    else:
        return False

def setLEDPower():
    global lastLedsPowerSetting
    global currentTime
    timeResult = True

    currentTime = datetime.datetime.now()


    if ledsPowerSetting != lastLedsPowerSetting:
        if ledsPowerSetting and timeResult:
            teensy.ser.write("P1\n")
            print "LEDS on"
        else:
            teensy.ser.write("P0\n")
            print "LEDS off"
        lastLedsPowerSetting = ledsPowerSetting
        teensy.ser.flush() 
        print ">" + teensy.ser.readline()
        return True
    else:
        return False

connectAttempts = 0

#print "Welcome to Example: Autodetect Teensy!"
while connectAttempts < 5:
    try:
        teensy = TeensySerial(115200)
    #    print "Connected to: %s" % teensy.teensy_port[1]
        teensy.ser.write("?\n")
        time.sleep(1)
        response = teensy.ser.readline()
        if response.startswith("Teensy LED Controller"):
            print("Successfully connected to: " + response)
            break
        else:
            print("Not the right Teensy. Responded with:")
            print(response)
            print(" Attempting to connect again.")
            # Reboot the Teensy by resending it more then 10 commands
            for x in xrange(15): 
                teensy.ser.write("?\n")
                time.sleep(0.2)
            #sys.exit()
    except TypeError:
        print "Cannot find a Teensy board connected..."
        sys.exit()


while 1:
    try:
#        print "File opened successfully"
        file = open(filename, "r")
        data = file.read().splitlines()
        setLEDPower()
        parseInput()

        #print ">" + teensy.ser.readline()

#        if data[0] != sp.port:
#            sp.close()
#            sp.port = data[0]
#            sp.open()

#        sp.write("D" + data[1])
    except IOError:
        print "2: There was an error reading from", filename
        teensy.close()
        sys.exit()

    time.sleep(1)


