#! /usr/bin/python
#**********************************************************************
# Description:
#   Convert GeoJSON to shape.
#   Creates '/var/vsites/landsatfact-dev.nemac.org/project/html/sites/all/modules/lsf_subscription/cgi-bin/shp_tmp/tmp.shp
#   Returns the result of invoking checkVertices on the tmp.shp
#   that is True (1) if the shp has greater than 10,000 vertices and 0 return code for False. A negative return code indicates an error.
#
#  0 - Input file (inJSON)
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


inJSON = sys.argv[1]

try:
    count=localLib.geoJSONToShp(inJSON)
except:
    tb = sys.exc_info()[2]
    tbinfo = traceback.format_tb(tb)[0]
    pymsg = "PYTHON ERRORS:\nTraceback Info:\n" + tbinfo + "\nError Info:\n    " + \
            str(sys.exc_type)+ ": " + str(sys.exc_value) + "\n"
    logging.error(pymsg)
    sys.exit(-1)

if count > 10000:
    sys.exit(1)
else:
    sys.exit(0)



















