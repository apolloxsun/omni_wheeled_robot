import tkinter as tk
import serial
import time
import math

class joystick:
    def __init__(self, root):
        self.canvas = tk.Canvas(root, width = 300, height = 300)
        self.canvas.pack()

        self.joystick_radius = 100
        self.center_x = 150
        self.center_y = 150
        self.canvas.create_oval(self.center_x - self.joystick_radius,
                                self.center_y - self.joystick_radius,
                                self.center_x + self.joystick_radius,
                                self.center_y + self.joystick_radius, 
                                fill="gray70", outline="gray70", width=2)
        
        self.knob_radius = 20
        self.knob = self.canvas.create_oval(self.center_x - self.knob_radius,
                                            self.center_y - self.knob_radius,
                                            self.center_x + self.knob_radius,
                                            self.center_y + self.knob_radius,
                                            fill="cornflowerblue", outline="cornflowerblue")
        
        self.canvas.bind("<B1-Motion>", self.move_knob)  # While dragging the joystick
        self.canvas.bind("<ButtonRelease-1>", self.reset_knob)  # When released

        self.current_angle = 0

    def move_knob(self, event):
            # Calculate distance from center
            dx = event.x - self.center_x
            dy = event.y - self.center_y
            distance = math.sqrt(dx ** 2 + dy ** 2)

            # Constrain knob to move within the joystick circle
            if distance > self.joystick_radius:
                # Limit the position to the edge of the joystick circle
                angle = math.atan2(dy, dx)
                dx = self.joystick_radius * math.cos(angle)
                dy = self.joystick_radius * math.sin(angle)

            # Update knob position
            self.canvas.coords(self.knob, self.center_x + dx - self.knob_radius,
                                        self.center_y + dy - self.knob_radius,
                                        self.center_x + dx + self.knob_radius,
                                        self.center_y + dy + self.knob_radius)

            # Calculate normalized position (x, y in range [-1, 1])
            self.current_x = dx / self.joystick_radius
            self.current_y = dy / self.joystick_radius


            # Print joystick position (you can send this via Bluetooth to the Arduino)
            self.current_angle = math.degrees(math.atan2(dx, dy))  # In degrees, relative to the x-axis
            if self.current_angle < 0:
                self.current_angle += 360  # Ensure the angle is positive (0 to 360 degrees)

            # Print and send the angle
            print(f"Joystick Angle: {self.current_angle:.2f} degrees")
            self.send_angle_to_arduino(self.current_angle)

    def send_angle_to_arduino(self, angle):
        # Send the angle data over Bluetooth
        angle_data = f"{angle:.2f}\n"  # Format the angle as a string with two decimal places
        ser.write(angle_data.encode())  # Send data via serial (Bluetooth)
        time.sleep(0.1)  # Small delay to ensure data is sent

    def reset_knob(self, event):
        # Move the knob back to the center
        self.canvas.coords(self.knob, self.center_x - self.knob_radius,
                                      self.center_y - self.knob_radius,
                                      self.center_x + self.knob_radius,
                                      self.center_y + self.knob_radius)

        # Reset position to (0, 0)
        self.current_x = 0
        self.current_y = 0

        # Print the reset position
        print(f"Joystick Position: X: {self.current_x:.2f}, Y: {self.current_y:.2f}")

ser = serial.Serial('COM6',9600,timeout=1)

def send_data():
    # Get data from input field
    data = entry.get()
    if data:
        ser.write(data.encode())  # Send the data over Bluetooth
        time.sleep(1)  # Optional: Allow some time for the device to process
        response = ser.readline().decode().strip()  # Read the response (if any)
        label_response.config(text=f"Arduino Response: {response}")  # Update the UI with the response

# Close the serial connection when closing the window
def on_closing():
    ser.close()
    root.destroy()

# Create the Tkinter UI
root = tk.Tk()
root.title("Bluetooth Serial Communicator with Joystick")

# Create UI elements
label = tk.Label(root, text="Enter Data to Send to Arduino:")
label.pack()

entry = tk.Entry(root)
entry.pack()

button_send = tk.Button(root, text="Send", command=send_data)
button_send.pack()

label_response = tk.Label(root, text="")
label_response.pack()

# Handle window closing
root.protocol("WM_DELETE_WINDOW", on_closing)

joystick1 = joystick(root)

# Start the Tkinter loop
root.mainloop()

# Close serial connection when the program finishes
ser.close()