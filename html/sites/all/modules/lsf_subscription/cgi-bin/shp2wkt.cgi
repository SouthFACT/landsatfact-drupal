#! /usr/bin/python
# Example of usage:
# ./shp2wkt.py "../../../../default/files/shapefiles/CherokeeCounty_1.zip"
from osgeo import ogr
import os, sys, zipfile

# import logging
# logging.basicConfig(filename='example.log',level=logging.DEBUG)
# logging.debug('This message should go to the log file')

# print sys.argv[1]
fileName = os.path.basename(sys.argv[1])
fileName = os.path.splitext(fileName)[0]
# print "got here";

zf = zipfile.ZipFile(sys.argv[1], 'r')
# Get the three mandatory files of .shp, .shx, and .dbf
sourceZip = zipfile.ZipFile(sys.argv[1], 'r')
for filename in zf.namelist():
	# print os.path.splitext(filename)[1]
	if os.path.splitext(filename)[1]=='.shp':
		shpFile = filename
		#print "doing shp file: " +shpFile
		#print "at path: " +os.path.realpath(os.path.dirname(sys.argv[0]))
		sourceZip.extract(shpFile,os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp')
	if os.path.splitext(filename)[1]=='.shx':
		shxFile = filename
		sourceZip.extract(shxFile,os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp')
	if os.path.splitext(filename)[1]=='.dbf':
		dbfFile = filename
		sourceZip.extract(dbfFile,os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp')		

driver = ogr.GetDriverByName("ESRI Shapefile")
dataSource = driver.Open(os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp/'+shpFile, 0)
layer = dataSource.GetLayer()

for feature in layer:
    geom = feature.GetGeometryRef()
env = geom.GetEnvelope()
#print env
print str(env[0])+','+str(env[1])+','+str(env[2])+','+str(env[3])

# Cleanup after yourself
if os.path.isfile(os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp/'+shpFile):
	os.remove(os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp/'+shpFile)
if os.path.isfile(os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp/'+shxFile):
	os.remove(os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp/'+shxFile)
if os.path.isfile(os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp/'+dbfFile):
	os.remove(os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp/'+dbfFile)
