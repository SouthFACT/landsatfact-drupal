#! /usr/bin/python
#**********************************************************************
# Description:
#    Extracts the neccesary files for processing a shapefile into the designated directory.
#
# Arguments:
#  0 - Input Zip (inZip)
#  1 - Target directory (trDir)
#
#**********************************************************************
import sys, os, zipfile

inZip = zipfile.ZipFile(sys.argv[1], 'r')
trDir = sys.argv[2]

for inFile in inZip.namelist():
    extension = os.path.splitext(inFile)[1]
    if extension == '.shp':
        shpFile = inFile
        inZip.extract(inFile, trDir)
    if extension == '.shx':
        inZip.extract(inFile, trDir)
    if extension == '.dbf':
        inZip.extract(inFile, trDir)
    if extension == '.prj':
        inZip.extract(inFile, trDir)

print shpFile

sys.exit(1);
