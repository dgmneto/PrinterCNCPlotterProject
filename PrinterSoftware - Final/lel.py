import png as png 
import numpy as np 
import sys as sys


image = []
with open(sys.argv[1], 'r') as f:
    lines = f.read().split('\n')
    for line in lines:
        array = []
        for value in line.split():
            array.append(int(value))
        image.append(array)

r = open('fdc.txt', 'w')
r.write(str(image))
f = open('greyCat.png', 'wb')
w = png.Writer(int(sys.argv[2]), int(sys.argv[3]) + 1, greyscale=True)
w.write(f, image)
