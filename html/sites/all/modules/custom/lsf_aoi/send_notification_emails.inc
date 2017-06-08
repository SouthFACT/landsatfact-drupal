#!/usr/bin/env drush
<?php

include(drupal_get_path('module', 'lsf_aoi') . '/db_helpers.php');

// Main
_lsf_aoi_notify_users_of_new_events();

function _lsf_aoi_notify_users_of_new_events() {
  // The global $base_url is needed to build URLs
  // that are embedded in notification emails.
  // If it is not defined, log a critical error
  // and exit the script.
  _lsf_aoi_make_sure_base_url_is_defined();

  $events = _lsf_aoi_get_aoi_events_ready_for_notification();
  foreach ($events as $row) {
    _lsf_aoi_email_event_info_to_subscribed_users($row);
  }
}

function _lsf_aoi_email_event_info_to_subscribed_users($aoi_event_row) {
  $aoi_parent_node_id = _lsf_aoi_get_aoi_parent_node_id_by_aoi_id($aoi_event_row->aoi_id);
  $uids = _lsf_aoi_get_uids_of_users_subscribed_to_aoi($aoi_event_row);
  $ALERT_STATUS_COMPLETE = 4;
  try {
    foreach ($uids as $user_id) {
      $user_info = _lsf_aoi_get_user_info_by_uid($user_id->user_id);
      $aoi_name = _lsf_aoi_get_aoi_parent_name_by_aoi_id($aoi_event_row->aoi_id);
      $event_date = new DateTime($aoi_event_row->event_date);
      $params = array(
        'user' => $user_info['name'],
        'aoi_event_nid' => $aoi_event_row->node_id,
        'aoi_name' => $aoi_name,
        'aoi_parent_nid' => $aoi_parent_node_id,
        'aoi_event_date' => $event_date->format('m/d/Y'),
        'aoi_event_day' => $event_date->format('D'),
      );
      drupal_mail(
        'lsf_aoi', // must be name of the module
        'aoi_notification', // $key argument in hook_mail
        $user_info['mail'], // user's email address
        language_default(),
        $params
      );
      _lsf_update_aoi_event_alert_status($aoi_event_row->aoi_event_id, $ALERT_STATUS_COMPLETE);
    }
  } catch (Exception $e) {
    watchdog('lsf_aoi', t($e->getMessage()), array(), WATCHDOG_ERROR);
  }
}

// Implements hook_mail
function lsf_aoi_mail($key, &$message, $params) {
  if ($key === 'aoi_notification') {
    $email_config = include(drupal_get_path('module', 'lsf_aoi') . '/aoi_event_email_config.php');
    $email_config = _lsf_aoi_format_email_config($email_config, $params);
    $message['from'] = $email_config['from'];
    $message['subject'] = t($email_config['subject']);
    $message['body'][] = t($email_config['body']);
    $message['headers']['Content-Type'] = 'text/html';    
  }
}

function _lsf_aoi_format_email_config($email_config, $params) {
  $email_body_keys = array(
    '{USER}',
    '{AOI_NAME}',
    '{AOI_EVENT_URL}',
    '{AOI_PARENT_URL}',
    '{AOI_EVENT_DATE}',
    '{AOI_EVENT_DAY}'
  );
  $email_body_values = array(
    $params['user'],
    $params['aoi_name'],
    _lsf_aoi_build_node_url_alias_by_nid($params['aoi_event_nid'], TRUE),
    _lsf_aoi_build_node_url_alias_by_nid($params['aoi_parent_nid'], TRUE),
    $params['aoi_event_date'],
    $params['aoi_event_day'],
  );
  $email_config['body'] = str_replace($email_body_keys, $email_body_values, $email_config['body']);
  $email_config['subject'] = str_replace($email_body_keys, $email_body_values, $email_config['subject']);
  return $email_config;
}

function _lsf_aoi_build_node_url_alias_by_nid($nid, $is_email) {
  global $base_url;
  $url = $base_url . url('node/'.$nid)
  if ($is_email) {
    $url = $url . '?source=email';
  }
  return $url;
}

function _lsf_aoi_make_sure_base_url_is_defined() {
  global $base_url;
  if (!$base_url) {
    watchdog(
      'lsf_aoi',
      t('Error: $base_url is not defined in settings.php. '
        . 'This global must be set before drupal nodes are created '
        . 'for new AOI events!'
      ),
      array(),
      WATCHDOG_EMERGENCY
    );
    exit();
  }
}




