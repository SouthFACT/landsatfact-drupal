#! /usr/bin/python
#**********************************************************************
# Description:
#    Deletes extracted zip
#
# Arguments:
#  0 - Target directory (trDir)
#
#**********************************************************************
import sys, shutil

trDir = sys.argv[1]

shutil.rmtree(trDir)

sys.exit(1);
