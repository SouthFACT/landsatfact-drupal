#! /usr/bin/python
#**********************************************************************
# Description:
#    Check that the input tar is valid and has all the required files.
#    Returns a return code of 1 for True and 0 for False. Removes the tar if false.
#    A negative return code indicates an error.
#
# Arguments:
#  0 - Input file (inTar)
#
#**********************************************************************
import sys, traceback, localLib, logging

inTar = sys.argv[1]
try:
    missing=localLib.validTar(inTar)
except:
    tb = sys.exc_info()[2]
    tbinfo = traceback.format_tb(tb)[0]
    pymsg = "PYTHON ERRORS:\nTraceback Info:\n" + tbinfo + "\nError Info:\n    " + \
            str(sys.exc_type)+ ": " + str(sys.exc_value) + "\n"
    logging.error(pymsg)
    sys.exit(-1)

if missing:
    localLib.removeTar(inTar)
    sys.exit(0)
else:
    sys.exit(1)


