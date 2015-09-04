#!/bin/bash                                                                                                                                 
./checkSpatialRef.py ~/PostGIS_test.shp
if [ $? -eq 1 ]
then
        ./checkVertices.py ~/PostGIS_test.shp
        if [ $? -eq 0 ]
        then
                ./shpToGeoJSON.py ~/PostGIS_test.shp
        fi
fi
