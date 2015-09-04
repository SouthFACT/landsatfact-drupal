#! /usr/bin/python

import os, sys

inZipFile = sys.argv[1]

print os.path.getsize(inZipFile)
