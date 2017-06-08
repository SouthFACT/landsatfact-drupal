#!/usr/bin/env drush
<?php

drupal_mail(
  'lsf_aoi', // must be name of the module
  'test', // $key argument in hook_mail
  'mgeiger@unca.edu', // user's email address
  language_default()
);

function lsf_aoi_mail($key, &$message, $params) {
  if ($key === 'test') {
    $message['from'] = 'info@southfact.com';
    $message['body'][] = 'test';
  }
}