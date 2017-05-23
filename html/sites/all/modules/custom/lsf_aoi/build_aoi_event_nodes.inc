#!/usr/bin/env drush

<?php
/*
	This script checks for new AOI events in the Postgres database.
	Drupal nodes are created for new change events and all subscribed users are
	sent a notification email.
*/

// Script Start
_lsf_aoi_build_all_aoi_event_nodes();


function _lsf_aoi_set_database_connection() {
    $config_info = parse_ini_file(DRUPAL_ROOT . '/../lsf_config.ini', true);
    $username = $config_info['pgsql_connection']['username'];
    $password = $config_info['pgsql_connection']['password'];
    $host = $config_info['pgsql_connection']['host'];
    $port = $config_info['pgsql_connection']['port'];
    $driver = $config_info['pgsql_connection']['driver'];
    $database = $config_info['pgsql_connection']['database'];
    $lsf_database = array(
        'database' => $database,
        'username' => $username,
        'password' => $password,
        'host' => $host,
        'port' => $port,
        'driver' => $driver,
    );

    Database::addConnectionInfo($database, 'default', $lsf_database);
    db_set_active($database);
}

function _lsf_aoi_build_all_aoi_event_nodes() {
	$aoi_events = _lsf_aoi_get_new_aoi_events();
	foreach ($aoi_events as $row) {
		_lsf_aoi_build_aoi_event_node($row);
	}
}

function _lsf_aoi_get_new_aoi_events() {
	_lsf_aoi_set_database_connection();
	$query = db_query('SELECT * FROM get_new_aoi_events()');
	$aoi_events = $query->fetchAll();
	db_set_active();
	return $aoi_events;
}

function _lsf_aoi_build_aoi_event_node ($aoi_event_row) {

	$aoi_parent_node_id = _lsf_aoi_get_aoi_parent_node_id_by_aoi_id(
		$aoi_event_row->aoi_id
	);
	$aoi_parent_node = _lsf_aoi_get_parent_aoi_node_by_node_id(
		$aoi_parent_node_id
	);
	if ($aoi_parent_node == FALSE) { return; }
	
	$aoi_parent_uid = $aoi_parent_node['uid'];
	$aoi_parent_patch_indicator_name = _lsf_aoi_get_parent_aoi_patch_indicator_name(
		$aoi_event_row->patch_indicator_id
	);

	$values = array(
		'type' => 'aoi_notification',
		'uid' => $aoi_parent_uid,
		'status' => 1,
		'comment' => 1,
		'promote' => 0,
	);

	$entity = entity_create('node', $values);

	// The entity is now created, but we have not yet simplified use of it.
	// Now create an entity_metadata_wrapper around the new node entity
	// to make getting and setting values easier
	$ewrapper = entity_metadata_wrapper('node', $entity);

	$ewrapper->title->set($aoi_parent_node->title.' AOI Event '.$aoi_event_row->event_date);

	$ewrapper->field_patch_indicator->set($aoi_parent_patch_indicator_name);
	$ewrapper->field_percent_changed->set($aoi_event_row->percent_change);
	$ewrapper->field_smallest_patch->set($aoi_event_row->smallest_patch);
	$ewrapper->field_largest_patch->set($aoi_event_row->largest_patch);
	$ewrapper->field_date_detected->set($aoi_event_row->date_detected);
	$ewrapper->field_parent_aoi->set(intval($aoi_parent_node_id));
	$ewrapper->field_change_area->set($aoi_event_row->acres_analyzed);

	$event_date = new DateTime($aoi_event_row->event_date);
	$entity->field_date_detected[LANGUAGE_NONE][0] = array(
		'value' => $event_date->format('Y-m-d'),
		'timezone' => 'UTC',
		'timezone_db' => 'UTC',
	);

	// Now just save the wrapper and the entity
	// There is some suggestion that the 'true' argument is necessary to
	// the entity save method to circumvent a bug in Entity API. If there is
	// such a bug, it almost certainly will get fixed, so make sure to check.
	try {
		$ewrapper->save();
		_lsf_aoi_email_event_info_to_subscribed_users($aoi_event_row, $ewrapper);
		_lsf_aoi_set_aoi_event_node_id_in_postgres($aoi_event_row->aoi_event_id, $ewrapper->getIdentifier());
	} catch (Exception $e) {
		echo 'Caught exception: ', $e->getMessage(), "\n";
	}
}

function _lsf_aoi_email_event_info_to_subscribed_users($aoi_event_row, $ewrapper) {
	$uids = _lsf_aoi_get_uids_for_users_subscribed_to_aoi($aoi_event_row);
	foreach ($uids as $user_id) {
		$user_info = _lsf_aoi_get_user_info_by_uid($user_id)
		drupal_mail('lsf_aoi', 'aoi_notification', $user_info['mail'], language_default(), $params=array('username' => $user_info['name']));		
	}
}

// Implements hook_mail
function lsf_aoi_mail($key, &$message, $params) {
	$email_config = require_once(drupal_get_path('module', 'lsf_aoi') . '/aoi_event_email_config.php');
	$message['from'] = $email_config['from'];
	$message['subject'] = t($email_config['subject']);
	$message['body'][] = t($email_config['body']);
}



// Postgres database helpers

function _lsf_aoi_get_uids_for_users_subscribed_to_aoi($aoi_event_row) {
	_lsf_aoi_set_database_connection();
	$query = db_query('SELECT user_id FROM user_aoi_alerts WHERE aoi_id='.$aoi_event_row['aoi_id']);
	$user_ids = $query->fetchAll();
	db_set_active();
	return $user_ids;
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
		array(':aoi_id' => $aoi_id)
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

function _lsf_aoi_get_user_info_by_uid($uid) {
	$query = db_query('SELECT name, mail FROM users WHERE uid='.$uid);
	$results = $query->fetchAll();
	return $results;
}

function _lsf_aoi_get_parent_aoi_node_by_node_id($node_id) {
	$query = db_query(
		'SELECT * FROM {node} WHERE nid=:node_id',
		array(':node_id'=>intval($node_id))
	);
	$results = $query->fetchAssoc();
	return $results;
}




