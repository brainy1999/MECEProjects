import cv2 as cv
import numpy as np
import imutils
import sys
import select
import os
import time
import RPi.GPIO as GPIO
from matplotlib.pyplot import imshow
from matplotlib import pyplot as plt

GPIO.setmode(GPIO.BCM)

GPIO.setup(18, GPIO.OUT)
GPIO.setup(23, GPIO.OUT)
GPIO.setup(24, GPIO.OUT)
GPIO.setup(25, GPIO.OUT)

cap = cv.VideoCapture(0)

final_frame = None
initial_frame = None

width = 640
height = 480

ret, frame = cap.read() # gets the image
fig = plt.figure()
plt.subplot(2,2,1)
framered = cv.resize(frame, (width, height))
imshow(framered[0:480, 0:640, 2], cmap='Reds')
plt.subplot(2,2,2)
framered = cv.resize(frame, (width, height))
imshow(framered[0:480, 0:640, 1], cmap='Greens')
plt.subplot(2,2,3)
framered = cv.resize(frame, (width, height))
imshow(framered[0:480, 0:640, 0], cmap='Blues')





bluenum = np.sum(frame[0:480, 0:640, 0]) / (480*640)
greennum = np.sum(frame[0:480, 0:640, 1]) / (480*640)
rednum = np.sum(frame[0:480, 0:640, 2]) / (480*640)

GPIO.output(18,GPIO.LOW)
GPIO.output(23,GPIO.LOW)
GPIO.output(24,GPIO.LOW)
GPIO.output(25,GPIO.LOW)

print("%f\n%f\n%f" % (greennum, bluenum, rednum))

if greennum < rednum and bluenum < rednum and rednum > 30 and rednum-bluenum > 20 and rednum-greennum > 20:
	print("red")
	GPIO.output(18,GPIO.HIGH)
elif greennum < bluenum and bluenum > 30 and rednum < bluenum and bluenum-greennum > 20 and bluenum-rednum > 20:
	print("blue")
	GPIO.output(23,GPIO.HIGH)
elif greennum > 30 and bluenum < greennum and rednum < greennum and greennum-bluenum > 20 and greennum-bluenum > 20:
	print("green")
	GPIO.output(24,GPIO.HIGH)
elif greennum >= 100 and bluenum >= 100 and rednum >= 100 and bluenum-greennum < 20 and bluenum-rednum < 20:
	print("white")
	GPIO.output(25,GPIO.HIGH)
else:
	print("none")

plt.show()

GPIO.cleanup()
