cription:
#   Convert shapefile to format suitable for insert into PostGIS
#   Use shp2pgsql utility and the PostgreSQL "dump" format for the output data.
#   Parse the output for the PostGIS internal geometry input format, and return a lost
#   containing that along with the GeoJSON as output on stdout as well as an exit code
#
# Example output from shp2pgsql:
#SET CLIENT_ENCODING TO UTF8;
#SET STANDARD_CONFORMING_STRINGS TO ON;
#BEGIN;
#CREATE TABLE "user_aoi" (gid serial,
#"id" int4);
#ALTER TABLE "user_aoi" ADD PRIMARY KEY (gid);
#SELECT AddGeometryColumn('','user_aoi','geom','0','MULTIPOLYGON',2);
#COPY "user_aoi" ("id",geom) FROM stdin;
#0	010600000001000000010300000001000000050000002C453EEB06435CC0FCAC1B4C913F584008A6C867DDC049C0FCAC1B4C913F584008A6C867DDC049C0907CD60DA66846402C453EEB06435CC0907CD60DA66846402C453EEB06435CC0FCAC1B4C913F5840
#\.
#COMMIT;


# Arguments:
#  0 - Input file (inShp)
#
#**********************************************************************
import os, sys, gdal, localLib
import traceback, logging

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
    gdal.Error(1, 2, 'test error')
    results=localLib.shpToPostGIS(inShpFile)
    print results
except:
    tb = sys.exc_info()[2]
    tbinfo = traceback.format_tb(tb)[0]
    pymsg = "PYTHON ERRORS:\nTraceback Info:\n" + tbinfo + "\nError Info:\n    " + \
            str(sys.exc_type)+ ": " + str(sys.exc_value) + "\n"
    logging.error(pymsg)


















