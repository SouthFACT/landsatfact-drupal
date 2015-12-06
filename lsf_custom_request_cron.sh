#! /bin/bash

cd /var/vsites/landsatfact-dev.nemac.org/project/html/sites/all/modules/lsf_request > /var/vsites/landsatfact-dev.nemac.org/cr.log 2>&1
drush /var/vsites/landsatfact-dev.nemac.org/project/html/sites/all/modules/lsf_request/custom_request_email.inc >> /var/vsites/landsatfact-dev.nemac.org/cr.log 2>&1
