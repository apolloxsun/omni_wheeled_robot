from __future__ import print_function

from inputs import get_gamepad
import serial
import math
import time

class Joystick:
    def __init__(self):
        self.xaxis = 0
        self.yaxis = 0
    def getValues(self):
        while True:
            events = get_gamepad()
            for event in events:
                #print(event.ev_type, event.code, event.state) #event.ev_type --> Absolute, event.code --> ABS_RY or ABS_RX, event.state gives coordinate information
                if event.ev_type == "Absolute":
                    if event.code == "ABS_RY":
                        self.xaxis = event.state
                        #print(f"y axis moved: {event.state:.2f}")
                    elif event.code == "ABS_RX":
                        self.yaxis = event.state
                        #print(f"x axis moved: {event.state:.2f}")
                if self.xaxis != 0 and self.yaxis != 0:
                    print(f"X: {self.xaxis}, Y: {self.yaxis}")
                    self.xaxis = 0
                    self.yaxis = 0
                elif self.xaxis == 0 or self.yaxis == 0:
                    print(f"X: {self.xaxis}, Y: {self.yaxis}")
                #print(f"X: {self.xaxis}, Y: {self.yaxis}")

joystick = Joystick()

joystick.getValues()
