<?php

function _lsf_aoi_get_user_info_by_uid($uid) {
  $query = db_query(
    'SELECT name, mail FROM users WHERE uid=:uid',
    array(':uid' => intval($uid))
  );
  $result = $query->fetchAssoc();
  return $result;
}


// Postgres database helpers

function _lsf_update_aoi_event_alert_status($aoi_event_id, $status) {
  _lsf_aoi_set_database_connection();
  $query = db_query(
    'UPDATE aoi_events SET alert_status_id=:status WHERE aoi_event_id=:id',
    array(':status' => $status, ':id' => $aoi_event_id)
  );
  db_set_active();
}

function _lsf_aoi_get_uids_of_users_subscribed_to_aoi($aoi_event_row) {
  _lsf_aoi_set_database_connection();
  $query = db_query(
    'SELECT user_id FROM user_aoi_alerts WHERE aoi_id=:aoi_id',
    array(':aoi_id' => $aoi_event_row->aoi_id)
  );
  $user_ids = $query->fetchAll();
  db_set_active();
  return $user_ids;
}

function _lsf_aoi_get_aoi_parent_name_by_aoi_id($aoi_id) {
  _lsf_aoi_set_database_connection();
  $query = db_query(
    'SELECT aoi_name FROM aoi_alerts WHERE aoi_id=:aoi_id',
    array(':aoi_id' => $aoi_id)
  );
  $results = $query->fetchAssoc();
  db_set_active();
  return $results['aoi_name'];
}

function _lsf_aoi_get_aoi_events_ready_for_notification() {
  _lsf_aoi_set_database_connection();
  $query = db_query('SELECT * FROM aoi_events WHERE alert_status_id=3 AND node_id IS NOT NULL');
  #$query = db_query('SELECT * FROM aoi_events WHERE aoi_id=1000');
  $results = $query->fetchAll();
  db_set_active();
  return $results;
}

function _lsf_aoi_get_new_aoi_events() {
  _lsf_aoi_set_database_connection();
  $query = db_query('SELECT * FROM aoi_events WHERE node_id IS NULL');
  #$query = db_query('SELECT * FROM aoi_events WHERE aoi_id=1000');
  $aoi_events = $query->fetchAll();
  db_set_active();
  return $aoi_events;
}

function _lsf_aoi_set_aoi_event_node_id_in_postgres($aoi_event_id, $node_id) {
  _lsf_aoi_set_database_connection();
  $query = db_update('aoi_events')
    ->fields(array('node_id' => $node_id))
    ->condition('aoi_event_id', $aoi_event_id, '=')
    ->execute();
  db_set_active();
}

function _lsf_aoi_get_aoi_parent_node_id_by_aoi_id($aoi_id) {
  _lsf_aoi_set_database_connection();
  $query = db_query(
    'SELECT node_id FROM aoi_alerts WHERE aoi_id=:aoi_id',
    array(':aoi_id' => intval($aoi_id))
  );
  $results = $query->fetchAssoc();
  db_set_active();
  return $results['node_id'];
}

function _lsf_aoi_get_parent_aoi_patch_indicator_name($id) {
  _lsf_aoi_set_database_connection();
  $query = db_query(
    'SELECT patch_indicator_name FROM forest_patch_indicator WHERE patch_indicator_id=:id',
    array(':id' => $id)
  );
  $result = $query->fetchAssoc();
  db_set_active();
  return $result['patch_indicator_name'];
}


// Drupal database helpers

function _lsf_aoi_get_parent_aoi_node_by_node_id($node_id) {
  $query = db_query(
    'SELECT * FROM node WHERE nid=:node_id',
    array(':node_id'=>$node_id)
  );
  $results = $query->fetchAssoc();
  return $results;
}






