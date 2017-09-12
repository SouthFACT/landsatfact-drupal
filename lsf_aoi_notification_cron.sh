#! /bin/bash

DIRECTORY=`dirname $0`
echo $DIRECTORY

#get the config file and make sure it will not do something delete all...
configfile=$DIRECTORY/bash_config.cfg
configfile_secured=$DIRECTORY/tmp_bash_config.cfg

# check if the file contains something we don't want
if egrep -q -v '^#|^[^ ]*=[^;]*' "$configfile"; then
  #filter the original to a new file
  egrep '^#|^[^ ]*=[^;&]*'  "$configfile" > "$configfile_secured"
  configfile="$configfile_secured"
fi

#now source it, either the original or the filtered variant
source "$configfile"

cd $path_website/project/html/sites/all/modules/custom/lsf_aoi > $path_website/aoi.log 2>&1
drush $path_website/project/html/sites/all/modules/custom/lsf_aoi/build_aoi_event_nodes.inc >> $path_website/aoi.log 2>&1 
drush $path_website/project/html/sites/all/modules/custom/lsf_aoi/send_notification_emails.inc >> $path_website/aoi.log 2>&1