#! /bin/bash

cd /var/vsites/www.landsatfact.com/project/html/sites/all/modules/lsf_subscription  > /var/vsites/www.landsatfact.com/sub.log 2>&1
drush  /var/vsites/www.landsatfact.com/project/html/sites/all/modules/lsf_subscription/email.inc >> /var/vsites/www.landsatfact.com/sub.log 2>&1 
