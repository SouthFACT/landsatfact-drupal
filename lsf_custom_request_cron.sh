#! /bin/bash

cd /var/vsites/www.landsatfact.com/project/html/sites/all/modules/lsf_request > /var/vsites/www.landsatfact.com/cr.log 2>&1
drush /var/vsites/www.landsatfact.com/project/html/sites/all/modules/lsf_request/custom_request_email.inc >> /var/vsites/www.landsatfact.com/cr.log 2>&1
