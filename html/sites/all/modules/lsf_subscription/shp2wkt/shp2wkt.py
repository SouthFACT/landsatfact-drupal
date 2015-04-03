#! /usr/bin/python
# Example of usage:
# ./shp2wkt.py "../../../../default/files/shapefiles/CherokeeCounty_1.zip"
from osgeo import ogr
import os, sys, zipfile

# print sys.argv[1]
fileName = os.path.basename(sys.argv[1])
fileName = os.path.splitext(fileName)[0]
# print fileName

zf = zipfile.ZipFile(sys.argv[1], 'r')
# Get the three mandatory files of .shp, .shx, and .dbf
sourceZip = zipfile.ZipFile(sys.argv[1], 'r')
for filename in zf.namelist():
	print os.path.splitext(filename)[1]
	if os.path.splitext(filename)[1]=='.shp':
		print "doing shp file"
		shpFile = filename
		sourceZip.extract(shpFile,os.getcwd())
	if os.path.splitext(filename)[1]=='.shx':
		print "doing shx file"
		shxFile = filename
		sourceZip.extract(shxFile,os.getcwd())
	if os.path.splitext(filename)[1]=='.dbf':
		print "doing dbf file"
		dbfFile = filename
		sourceZip.extract(dbfFile,os.getcwd())		

driver = ogr.GetDriverByName("ESRI Shapefile")
dataSource = driver.Open(shapefile, 0)
layer = dataSource.GetLayer()

for feature in layer:
    geom = feature.GetGeometryRef()
    wkt = geom.GetEnvelope()
print wkt 
