#! /usr/bin/python
#**********************************************************************
# Description:
#    Extracts the neccesary files for processing a shapefile into the designated directory.
#    Returns 0 return code for False and 1 for True. A negative return code indicates an error.
#
# Arguments:
#  0 - Input Zip (inZip)
#  1 - Target directory (trDir)
#
#**********************************************************************
import sys, zipfile

inZip = file(sys.argv[1])
zippedFile = zipfile.ZipFile(inZip)

if zipfile.is_zipfile(inFile):
    ret=zippedFile.testzip()
    if ret is not None:
        return ret
    else:
        contents=zippedFile.namelist()
        if (len(contents) >= 4):
            contentStr=' '.join(contents)

            m = re.search('(\w+)(\.shp)', contentStr)
            base=m.group().split('.')[0]
            if (base+'.dbf' in contentStr and base+'.shp' in contentStr and base+'.shx' in contentStr and base+'.prj' in contentStr):
                return ''
