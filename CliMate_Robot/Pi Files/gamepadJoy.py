# We use the "serial" package to connect to the Arduino over USB
# You need to install pySerial first (e.g., pip install pyserial)
import serial
import inputs

import csv  # To write data to a file
import time  # For logging time



#Set up Gamepad
print(inputs.devices.gamepads)
pads = inputs.devices.gamepads
if len(pads) == 0:
    raise Exception("Couldn't find any Gamepads!")

#Set up serial
Arduino_Serial = serial.Serial('/dev/ttyACM1', 9600)  # Create Serial port object called arduinoSerialData


print("Enter 1 to ON LED and 0 to OFF LED")

#check for inputs
while True:
    events = inputs.get_gamepad()
    #print(Arduino_Serial.readline())  # read the serial data and print it as line
    for event in events:
    	#print(event.ev_type, event.code, event.state)
        print(event.code)
        if event.code == 'ABS_RZ':
            print("Forward")
            sig = 1000 + event.state
            Arduino_Serial.write(sig)  # send 1 to arduino
        elif event.code == 'ABS_Z':
            #Arduino_Serial.write('2'.encode())  # send 1 to arduino
            print("Turn")
            #Arduino_Serial.write('0'.encode())  # send 1 to arduino

