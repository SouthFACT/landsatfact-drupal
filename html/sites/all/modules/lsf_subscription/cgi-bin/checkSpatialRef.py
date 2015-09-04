#! /usr/bin/python
#**********************************************************************
# Description:
#    Check that the input shapefile is WGS 84
#    Returns 0 return code for False and one for True. A negative return code indicates an error.
#
# Arguments:
#  0 - Input file (inShp)
#
#**********************************************************************
import sys, gdal, traceback, localLib, logging

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
    bool=localLib.checkSpatialRef(inShpFile)
except:
    tb = sys.exc_info()[2]
    tbinfo = traceback.format_tb(tb)[0]
    pymsg = "PYTHON ERRORS:\nTraceback Info:\n" + tbinfo + "\nError Info:\n    " + \
            str(sys.exc_type)+ ": " + str(sys.exc_value) + "\n"
    logging.error(pymsg)
    sys.exit(-1)

if bool:
    sys.exit(1)
else:
    sys.exit(0)

