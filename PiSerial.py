import RPi.GPIO as GPIO
import serial

ser = serial.Serial(port='/dev/ttyS0',baudrate=9600)
print("Connected to Arduino Feather M0.")
try:
	while True:
		input = ser.readline()
		ser.write(input)
except KeyboardInterrupt:
	GPIO.cleanup()