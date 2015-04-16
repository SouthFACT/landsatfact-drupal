#! /usr/bin/python
from osgeo import ogr, osr
import os, sys, zipfile

#ogr2ogr -t_srs EPSG:4269 -f geoJSON Neighbourhoods.json Neighbourhoods.shp
#ogr2ogr -f "file_format" destination_data source_data

# 1. Extract the zip File-------------------------------------------------------------------
inZipFile = os.path.basename(sys.argv[1])
inZipFile = os.path.splitext(inZipFile)[0]
inZipFileList = zipfile.ZipFile(sys.argv[1], 'r')
sourceZip = zipfile.ZipFile(sys.argv[1], 'r')
# Get the four mandatory files of .shp, .shx, .prj and .dbf
for inFile in inZipFileList.namelist():
	if os.path.splitext(inFile)[1]=='.shp':
		shpFile = inFile
		sourceZip.extract(shpFile,os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp')
	if os.path.splitext(inFile)[1]=='.shx':
		shxFile = inFile
		sourceZip.extract(shxFile,os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp')
	if os.path.splitext(inFile)[1]=='.dbf':
		dbfFile = inFile
		sourceZip.extract(dbfFile,os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp')		
	if os.path.splitext(inFile)[1]=='.prj':
		prjFile = inFile
		sourceZip.extract(prjFile,os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp')		

# 2. Verify the projection and fix if necessary---------------------------------------------
try:
	driver = ogr.GetDriverByName('ESRI Shapefile')
	dataset = driver.Open(os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp/'+shpFile)
	# from Layer
	layer = dataset.GetLayer()
	spatialRef = layer.GetSpatialRef()
	# from Geometry
	feature = layer.GetNextFeature()
	geom = feature.GetGeometryRef()
	inSpatialRef = geom.GetSpatialReference()
	# output SpatialReference
	outSpatialRef = osr.SpatialReference()
	outSpatialRef.ImportFromEPSG(4326)
	# create the CoordinateTransformation
	coordTrans = osr.CoordinateTransformation(inSpatialRef, outSpatialRef)
	# get the input layer
	inDataSet = driver.Open(os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp/'+shpFile)
	inLayer = inDataSet.GetLayer()
	# create the output layer
	outputShapefile = os.path.realpath(os.path.dirname(sys.argv[0]))+'/shp_tmp/'+shpFile.rsplit( ".", 1 )[ 0 ]+'_4326.shp'
	if os.path.exists(outputShapefile):
		driver.DeleteDataSource(outputShapefile)
	outDataSet = driver.CreateDataSource(outputShapefile)
	outLayer = outDataSet.CreateLayer("basemap_4326", geom_type=ogr.wkbMultiPolygon)
	# add fields
	inLayerDefn = inLayer.GetLayerDefn()
	for i in range(0, inLayerDefn.GetFieldCount()):
		fieldDefn = inLayerDefn.GetFieldDefn(i)
		outLayer.CreateField(fieldDefn)
	# get the output layer's feature definition
	outLayerDefn = outLayer.GetLayerDefn()
	# loop through the input features
	inFeature = inLayer.GetNextFeature()
	while inFeature:
		# get the input geometry
		geom = inFeature.GetGeometryRef()
		# reproject the geometry
		geom.Transform(coordTrans)
		# create a new feature
		outFeature = ogr.Feature(outLayerDefn)
		# set the geometry and attribute
		outFeature.SetGeometry(geom)
		for i in range(0, outLayerDefn.GetFieldCount()):
			outFeature.SetField(outLayerDefn.GetFieldDefn(i).GetNameRef(), inFeature.GetField(i))
		# add the feature to the shapefile
		outLayer.CreateFeature(outFeature)
		# destroy the features and get the next input feature
		outFeature.Destroy()
		inFeature.Destroy()
		inFeature = inLayer.GetNextFeature()
	# close the shapefiles
	inDataSet.Destroy()
	outDataSet.Destroy()
except:
    print "Unexpected error:", sys.exc_info()[0]
    raise

# 3. Get the GeoJSON and send it back-------------------------------------------------------		
driver = ogr.GetDriverByName("ESRI Shapefile")
dataSource = driver.Open(outputShapefile)
layer = dataSource.GetLayer()
for feature in layer:
    geom = feature.GetGeometryRef()
geoJSON = geom.ExportToJson()
print geoJSON