#! /usr/bin/python
from osgeo import ogr
import os, sys, zipfile

#ogr2ogr -t_srs EPSG:4269 -f geoJSON Neighbourhoods.json Neighbourhoods.shp
#ogr2ogr -f "file_format" destination_data source_data

fileName = os.path.basename(sys.argv[1])
fileName = os.path.splitext(fileName)[0]

zf = zipfile.ZipFile(sys.argv[1], 'r')
# Get the four mandatory files of .shp, .shx, .prj and .dbf
sourceZip = zipfile.ZipFile(sys.argv[1], 'r')
for filename in zf.namelist():
	if os.path.splitext(filename)[1]=='.shp':
		shpFile = filename
		sourceZip.extract(shpFile,os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp')
	if os.path.splitext(filename)[1]=='.shx':
		shxFile = filename
		sourceZip.extract(shxFile,os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp')
	if os.path.splitext(filename)[1]=='.dbf':
		dbfFile = filename
		sourceZip.extract(dbfFile,os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp')		
	if os.path.splitext(filename)[1]=='.prj':
		prjFile = filename
		sourceZip.extract(dbfFile,os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp')		

# original shp2wkt:
# fileName = os.path.basename(sys.argv[1])
driver = ogr.GetDriverByName("ESRI Shapefile")
# dataSource = driver.Open(os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp/'+fileName)
dataSource = driver.Open(os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp/'+shpFile)
layer = dataSource.GetLayer()

for feature in layer:
    geom = feature.GetGeometryRef()
geoJSON = geom.ExportToJson()
print geoJSON