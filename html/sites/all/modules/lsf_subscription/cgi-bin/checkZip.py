#! /usr/bin/python
#**********************************************************************
# Description:
#    Check that the input zip has all the required files.
#    Returns a return code of 1 for True and 0  for False. Removes the zip if false.
#    A negative return code indicates an error.
#
# Arguments:
#  0 - Input file (inZip)
#
#**********************************************************************
import sys, traceback, localLib, logging

inZipFile = sys.argv[1]
try:
    missing=localLib.checkZip(inZipFile)
except:
    tb = sys.exc_info()[2]
    tbinfo = traceback.format_tb(tb)[0]
    pymsg = "PYTHON ERRORS:\nTraceback Info:\n" + tbinfo + "\nError Info:\n    " + \
            str(sys.exc_type)+ ": " + str(sys.exc_value) + "\n"
    logging.error(pymsg)
    sys.exit(-1)

if missing:
    localLib.removeZip(inZipFile)
    sys.exit(0)
else:
    sys.exit(1)


