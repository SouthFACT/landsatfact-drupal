#! /usr/bin/python
# Example of usage:
# ./shp2wkt.py "../../../../default/files/shapefiles/CherokeeCounty_1.zip"
from osgeo import ogr
import os, sys, zipfile

try:
	fileName = os.path.basename(sys.argv[1])
	fileName = os.path.splitext(fileName)[0]

	zf = zipfile.ZipFile(sys.argv[1], 'r')
	sourceZip = zipfile.ZipFile(sys.argv[1], 'r')
	for filename in zf.namelist():
		if os.path.splitext(filename)[1]=='.shp':
			shpFile = filename.rsplit( ".", 1 )[ 0 ]+'_4326.shp'
	driver = ogr.GetDriverByName("ESRI Shapefile")
	dataSource = driver.Open(os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp/'+shpFile, 0)
	layer = dataSource.GetLayer()

	for feature in layer:
		geom = feature.GetGeometryRef()
	env = geom.GetEnvelope()
	print shpFile+':'+str(env[0])+','+str(env[1])+','+str(env[2])+','+str(env[3])
except:
    print "Unexpected error:", sys.exc_info()[0]
    raise