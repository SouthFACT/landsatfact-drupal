#! /usr/bin/python
#**********************************************************************
# Description:
#    Simplify the geometry with a target of less then 10,000 vertices or 10 attempts, whichever comes first. The first
#       attempt at simplification is with a distance tolerance of 0.000001. Units for distance tolerance is not specified in the
#       OGRGeometry reference. According to: http://gis.stackexchange.com/questions/144015/how-does-ogr2ogr-simplify-work,
#       The tolerance units are whatever the units the shp layer are. If the layer is EPSG 43260, .000001 is about a meter.
#       For each iteration, the tolerance will be increased fivefold.
# Note: the algorithm used preserves topology per feature, in particular for polygon geometries, but not for a whole layer.
# Arguments:
#  0 - Input file (inShp)
#  1 - Distance tolerance (default = 0.000001)
#**********************************************************************
import osgeo, ogr, os, sys
import traceback

def createTmpShapefile(outShp, inFeature, srs):
    # follow the cookbook
    # https://pcjericks.github.io/py-gdalogr-cookbook/vector_layers.html
    outDriver = ogr.GetDriverByName("ESRI Shapefile")

    # Remove output shapefile if it already exists
    if os.path.exists(outShp):
        outDriver.DeleteDataSource(outShp)

    # Create the output shapefile
    outDataSource = outDriver.CreateDataSource(outShp)
    outLayer = outDataSource.CreateLayer("Clean_poly", srs, geom_type=ogr.wkbPolygon)

    # Add an ID field
#    idField = ogr.FieldDefn("clean", ogr.OFTInteger)
#    outLayer.CreateField(idField)

    # Create the feature and set values
    featureDefn = outLayer.GetLayerDefn()
    feature = ogr.Feature(featureDefn)
    feature.SetGeometry(inFeature.GetGeometryRef())
#    feature.SetField("clean", 1)
    outLayer.CreateFeature(feature)

    # Close DataSource, mixed signals on Destroy (https://trac.osgeo.org/gdal/wiki/PythonGotchas)
    outDataSource.Destroy()

def simplifyShp(inShp, tolerance=None):
    driver = ogr.GetDriverByName("ESRI Shapefile")
    dataSource = driver.Open(inShp, 1)
    layer = dataSource.GetLayer()
    source_srs = layer.GetSpatialRef()
    print ('Should be only one layer and there is {} layer(s)'.format(dataSource.GetLayerCount()))
    layer = dataSource.GetLayer(0)
    print layer.GetName(), ' contains ', layer.GetFeatureCount(), ' features'
    feature = layer.GetFeature(0)
    geom = feature.GetGeometryRef()
    # Get Geometry inside Geometry
    ring = geom.GetGeometryRef(0)
    print geom.GetGeometryName(), ' contains the Geometry', ring.GetGeometryName()

    ring = geom.GetGeometryRef(0)
    print 'It contains', ring.GetPointCount(), ' points in a ', ring.GetGeometryName()
    pc = ring.GetPointCount()
    iteration = 1
    while pc > 10000 and iteration < 11:
            print 'Simplify on iteration {} with a tolerance of {:.6f}'.format(iteration, tolerance)
#            import pdb
#            pdb.set_trace()
            newGeom = geom.Simplify(tolerance)
            if newGeom is None:
                print 'Error return from OGR Geometry Simplify on iteration {} with a tolerance of {:.6f}'.format(iteration, tolerance)
                break
            else:
                feature.SetGeometry(newGeom)
            geom = feature.GetGeometryRef()
            ring = geom.GetGeometryRef(0)
            pc = ring.GetPointCount()
            iteration = iteration + 1
            tolerance = tolerance*5
            print 'Feature contains', ring.GetPointCount(), ' points in a ', ring.GetGeometryName()

    # have to overwrite the shapefile. apparently updating a shapefile's geometry correctly is not available til 2.0
    # put TMP_ shapefile in the same directory as inShp
    outShp = os.path.join( os.path.split( inShp )[0],'TMP_' + os.path.basename(inShp))
    createTmpShapefile(outShp, feature, source_srs)
    dataSource=outDS=None
    layer=feature=geom=newGeom=ring=None
    # then move TMP_ shapefile to inShp
    driver.DeleteDataSource(inShp)
    dataSource = driver.Open(outShp)
    outDS=driver.CopyDataSource(dataSource, inShp)
    driver.DeleteDataSource(outShp)
    dataSource=outDS=None


inShpFile = os.path.basename(sys.argv[1])
if len(sys.argv) > 2:
    tolerance=float(sys.argv[2])
else:
    tolerance= 0.000001
try:
    simplifyShp(inShpFile, tolerance)
except:
    tb = sys.exc_info()[2]
    tbinfo = traceback.format_tb(tb)[0]
    pymsg = "PYTHON ERRORS:\nTraceback Info:\n" + tbinfo + "\nError Info:\n    " + \
            str(sys.exc_type)+ ": " + str(sys.exc_value) + "\n"
    print pymsg

