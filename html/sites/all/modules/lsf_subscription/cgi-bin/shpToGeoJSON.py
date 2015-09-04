#! /usr/bin/python
#**********************************************************************
# Description:
#   Convert shapefile to GeoJSON.
#   Returns GeoJSON as output on stdout as well as an exit code, non-zero in the case of error
#
#  0 - Input file (inShp)
#
#**********************************************************************
import gdal, sys, traceback, localLib, logging

logging.basicConfig(stream=sys.stderr, level=logging.INFO)

# GDAL error handler function
# http://pcjericks.github.io/py-gdalogr-cookbook/gdal_general.html#install-gdal-ogr-error-handler
def gdal_error_handler(err_class, err_num, err_msg):
    errtype = {
            gdal.CE_None:'None',
            gdal.CE_Debug:'Debug',
            gdal.CE_Warning:'Warning',
            gdal.CE_Failure:'Failure',
            gdal.CE_Fatal:'Fatal'
    }
    err_msg = err_msg.replace('\n',' ')
    err_class = errtype.get(err_class, 'None')
    logging.error('Error Number: %s' % (err_num))
    logging.error('Error Type: %s' % (err_class))
    logging.error('Error Message: %s' % (err_msg))

# install error handler
gdal.UseExceptions()
gdal.PushErrorHandler(gdal_error_handler)


inShpfile = sys.argv[1]

try:
    geoJSON=localLib.shpToGeoJSON(inShpfile)
    print geoJSON
except:
    tb = sys.exc_info()[2]
    tbinfo = traceback.format_tb(tb)[0]
    pymsg = "PYTHON ERRORS:\nTraceback Info:\n" + tbinfo + "\nError Info:\n    " + \
            str(sys.exc_type)+ ": " + str(sys.exc_value) + "\n"
    logging.error(pymsg)
    sys.exit(-1)

sys.exit(0)



















