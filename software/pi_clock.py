#!/usr/bin/env python3
import serial
import time
from datetime import datetime

# Open the UART serial port
ser = serial.Serial('/dev/serial0', 115200, timeout=1)

try:
    print("Waiting for 'time' or 'date' request...")

    while True:
        if ser.in_waiting > 0:
            # Read incoming request
            request = ser.readline().decode('utf-8').strip().lower()

            print(f"Received: {request}")  # Optional debug print

            if request == "time":
                # Send current time
                now = datetime.now().strftime('%H:%M:%S')
                ser.write((now + '\n').encode('utf-8'))
                print(f"Sent time: {now}")

            elif request == "date":
                # Send current date
                today = datetime.now().strftime('%Y-%m-%d')
                ser.write((today + '\n').encode('utf-8'))
                print(f"Sent date: {today}")

        #time.sleep(0.1)  # Light delay to avoid high CPU usage

except KeyboardInterrupt:
    print("Stopped by user")

finally:
    ser.close()
