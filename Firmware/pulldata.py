'''
3D Printer: POE Lab 2

This script pulls data sent over USB
by the Ardino and saves it to be plotted
by numpy

authors: dtarazi315, awenstrup
'''
#Import statements
import serial
import time
import numpy as np
import matplotlib.pyplot as plt

#Variable definitions

port = '/dev/ttyACM0'
baudRate = 9600

a = 8442
b = -0.9307

values = list()



#Setup
serialPort = serial.Serial(port=port, baudrate=9600, timeout=None)


def adc_to_dist(num):
    if num > 0:
        return a * (num ** b)
    else:
        return 150

def input_to_scatter(l, xres, yres):
    format_list(l)
    array = np.array(l).reshape(yres, xres)
    print(array)
    print(array.shape)
    return array

def format_list(l):
    for i, n in enumerate(l):
        if n > 150:
            l[i] = 150
        if n < 15:
            l[i] = 15

    return l.reverse()

def test_plot():
    l = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
    scatter = input_to_scatter(l, 4, 3)

    # make these smaller to increase the resolution
    dx, dy = 2, 2

    x = range(0, 8 + dx, dx)
    y = range(0, 6 + dy, dy)

    print(x)
    print(y)

    plt.pcolormesh(x, y, scatter)
    plt.xlabel("Theta (degrees)")
    plt.ylabel("Phi (degrees)")
    plt.title("3D Scan of letter 'A'")
    plt.show()

time.sleep(1)

#Loop
running = True
while running:

    line = serialPort.readline()
    if len(line) > 0:
        dist = adc_to_dist(int(line.decode().strip()))
        print('Distance is ', dist)
        values.append(dist)
        print()

    if len(values) == 600:
        running = False

        x = range(0, 60 + 2, 2)
        y = range(0, 40 + 2, 2)

        plt.pcolormesh(x, y, input_to_scatter(values, 30, 20))
        plt.xlabel("Theta (degrees)")
        plt.ylabel("Phi (degrees)")
        plt.title("3D Scan of letter 'A'")
        plt.show()
