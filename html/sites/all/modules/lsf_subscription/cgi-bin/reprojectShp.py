#! /usr/bin/python
#**********************************************************************
# Description:
#    Reproject inShp to WGS84. Assumes inShp is in a different projection (i.e., it doesn't check).
#    Assumes inShp has only one polygon shape.
#
# Arguments:
#  0 - Input file (inShp)
#
#**********************************************************************
import sys, gdal, traceback, localLib, logging

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


inShpFile = sys.argv[1]

try:
    localLib.reprojectShp(inShpFile)
except:
    tb = sys.exc_info()[2]
    tbinfo = traceback.format_tb(tb)[0]
    pymsg = "PYTHON ERRORS:\nTraceback Info:\n" + tbinfo + "\nError Info:\n    " + \
            str(sys.exc_type)+ ": " + str(sys.exc_value) + "\n"
    logging.error(pymsg)

