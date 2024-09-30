import pygame
import serial
import time
import sys
import math

class Joystick:
    def __init__(self):
        self.xaxis = 0
        self.yaxis = 0
        self.current_angle = 0
        self.current_length = 0
    def send_data_to_arduino(self, angle, length, rot_angle, rot_length):
        # **Format the data as <angle, length>**
        data = f"<{angle:.2f}, {length:.2f}, {rot_angle:.2f}, {rot_length:.2f}>\n"  # Updated format
        ser.write(data.encode())  # Send the formatted data via Bluetooth
        time.sleep(0.1)  # Small delay to ensure data is sent
    def calcAngAndLength(self, x, y):
        self.current_angle = math.degrees(math.atan2(x, y)) - 90 # In degrees, relative to the x-axis
        if self.current_angle < 0:
            self.current_angle += 360  # Ensure the angle is positive (0 to 360 degrees)
        self.current_length = math.sqrt((x)**2 + (y)**2) * 10
        if abs(x) <= 0.1 and abs(y) <= 0.1:
            self.current_angle = 0
            self.current_length = 0
        return self.current_angle, self.current_length
        
    

pygame.init()
pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)
joystick.init()

joystick_inst = Joystick()

clock = pygame.time.Clock()

screen = pygame.display.set_mode((300,100))
pygame.display.set_caption("Coordinates of the mouse")
font = pygame.font.SysFont("Arial", 16)
text = font.render("hello", True, (255,255,255))

bt_button = pygame

ser = serial.Serial('COM6',9600,timeout=1)

while True:
    pygame.event.pump()  # Process the event queue
    xaxis = joystick.get_axis(2)  # Left joystick horizontal axis, linear replacement
    yaxis = joystick.get_axis(3)
    rot_xaxis = joystick.get_axis(0)  # Right joystick horizontal axis, rotation
    rot_yaxis = joystick.get_axis(1)

    screen.fill("lightsteelblue1")
    text = font.render(f"rotation X: {rot_xaxis:.2f}, rotation Y: {rot_yaxis:.2f}", True, (0,0,0))
    screen.blit(text, (10, 10))

    rot_angle, rot_length = joystick_inst.calcAngAndLength(rot_xaxis, rot_yaxis)
    text3 = font.render(f"angle: {rot_angle:.2f}, length: {rot_length:.2f}", True, (0,0,0))
    screen.blit(text3, (10,30))

    text1 = font.render(f"X: {xaxis:.2f}, Y: {yaxis:.2f}", True, (0,0,0))
    screen.blit(text1, (10, 50))

    angle, length = joystick_inst.calcAngAndLength(xaxis, yaxis)
    text2 = font.render(f"angle: {angle:.2f}, length: {length:.2f}", True, (0,0,0))
    screen.blit(text2, (10,70))

    pygame.display.update()

    joystick_inst.send_data_to_arduino(angle, length, rot_angle, rot_length)

    time.sleep(0.01)  # Sleep briefly to avoid excessive CPU usage

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
