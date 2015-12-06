#! /bin/bash

cd /var/vsites/landsatfact-dev.nemac.org/project/html/sites/all/modules/lsf_subscription  > /var/vsites/landsatfact-dev.nemac.org/sub.log 2>&1
drush  /var/vsites/landsatfact-dev.nemac.org/project/html/sites/all/modules/lsf_subscription/email.inc >> /var/vsites/landsatfact-dev.nemac.org/sub.log 2>&1 
