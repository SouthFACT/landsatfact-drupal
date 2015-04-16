#! /usr/bin/python
from osgeo import ogr, osr
import os, sys, zipfile

driver = ogr.GetDriverByName('ESRI Shapefile')
dataset = driver.Open('shp_tmp/CherokeeCounty.shp')

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
inDataSet = driver.Open('shp_tmp/CherokeeCounty.shp')
inLayer = inDataSet.GetLayer()

# create the output layer
outputShapefile = r'shp_tmp/CherokeeCounty_4326.shp'
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