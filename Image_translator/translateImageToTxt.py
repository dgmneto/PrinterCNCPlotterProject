import png as png
import numpy as np
import sys as sys

#Getting image properties
reader = png.Reader(sys.argv[1])
columnCount, rowCount, pngData, metaData = reader.asDirect()
bitDepth = metaData['bitdepth']
planeCount = metaData['planes']

#Printing image properties
print ("BitDepth: ", bitDepth)
print ("planeCount: ", planeCount)

#Getting image to print
image_2d = (np.vstack(list(map(np.uint8, pngData))))
image_3d = np.reshape(image_2d, (rowCount, columnCount, planeCount))
print (image_3d.shape)

#Wrinting to file
omg = open(sys.argv[1][:len(sys.argv[1])-3] + 'txt', 'w')
omg.write(str(columnCount) + ' ' + str(rowCount) + '\n')
omg.write(str(np.reshape(image_3d, (-1, columnCount*planeCount)).tolist()))
omg.close()
