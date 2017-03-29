import png as png 
import numpy as np 
import sys as sys

#arg[1] = imageName

r = png.Reader(sys.argv[1]) 
columnCount, rowCount, pngData, metaData = r.asDirect() 
bitDepth=metaData['bitdepth']
planeCount = metaData['planes']
print ("BitDepth: ", bitDepth) 
print ("planeCount: ", planeCount)
print (metaData)
image_2d = (np.vstack(list(map(np.uint8, pngData))))
print(image_2d)
# for easier referencing you could make the image into 3d like so 
image_3d = np.reshape(image_2d, (rowCount, columnCount, planeCount))
print (image_3d.shape)

omg = open(sys.argv[1][:len(sys.argv[1])-3] + 'txt', 'w')
omg.write(str(columnCount) + ' ' + str(rowCount) + '\n')
omg.write(str(np.reshape(image_3d, (-1, columnCount*planeCount)).tolist()))
omg.close()
