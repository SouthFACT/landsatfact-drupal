#!/usr/bin/env drush
<?php

/*
	This script checks for new AOI events in the Postgres database,
	creates drupal nodes for them, and sends a notification email
	to all users subscribed to the email.
*/

include_once(drupal_get_path('module', 'lsf_aoi') . '/db_helpers.php');

// Main
_lsf_aoi_build_all_aoi_event_nodes();


function _lsf_aoi_build_all_aoi_event_nodes() {
	$aoi_events = _lsf_aoi_get_new_aoi_events();
	foreach ($aoi_events as $row) {
		_lsf_aoi_build_aoi_event_node($row);
	}
}

function _lsf_aoi_build_aoi_event_node ($aoi_event_row) {

	$aoi_event_node_title = 'Change Event ('.$aoi_event_row->event_date .')';

	$aoi_parent_node_id = _lsf_aoi_get_aoi_parent_node_id_by_aoi_id(
		$aoi_event_row->aoi_id
	);
	$aoi_parent_node = _lsf_aoi_get_parent_aoi_node_by_node_id(
		$aoi_parent_node_id
	);	
	if ($aoi_parent_node == FALSE) {
		watchdog(
			'lsf_aoi',
			t('Error: unable to create drupal node for aoi event (id: :aoi_id): '
				. 'the drupal node for the aoi parent either does not exist or the aoi event'
				. 'is improperly referenced in the postgres database. Good luck!'
			),
			array(':aoi_id' => $aoi_event_row->aoi_id),
			WATCHDOG_ERROR
		);
		return;
	}
	
	$aoi_parent_uid = $aoi_parent_node['uid'];
	$aoi_parent_patch_indicator_name = _lsf_aoi_get_parent_aoi_patch_indicator_name(
		$aoi_event_row->patch_indicator_id
	);

	$aoi_event_period_of_change = _lsf_aoi_get_aoi_event_date_range($aoi_event_row->aoi_event_id);

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

	$ewrapper->title->set($aoi_event_node_title);

	$ewrapper->field_patch_indicator->set($aoi_parent_patch_indicator_name);
	$ewrapper->field_percent_changed->set($aoi_event_row->percent_change);
	$ewrapper->field_smallest_patch->set($aoi_event_row->smallest_patch);
	$ewrapper->field_largest_patch->set($aoi_event_row->largest_patch);
	$ewrapper->field_date_detected->set($aoi_event_row->date_detected);
	$ewrapper->field_parent_aoi->set(intval($aoi_parent_node_id));
	$ewrapper->field_change_area->set($aoi_event_row->acres_change);

	// Cannot use metadata wrapper for date types
	$event_date = new DateTime($aoi_event_row->event_date);
	$entity->field_date_detected[LANGUAGE_NONE][0] = array(
		'value' => $event_date->format('Y-m-d'),
		'timezone' => 'UTC',
		'timezone_db' => 'UTC',
	);
	$entity->field_period_of_change[LANGUAGE_NONE][0] = array(
		'value' => $aoi_event_period_of_change['start_date']->format('Y-m-d H:i:s'),
		'value2' => $aoi_event_period_of_change['end_date']->format('Y-m-d H:i:s'),
		'timezone' => 'UTC',
		'timezone_db' => 'UTC',
	);

	try {
		$ewrapper->save();
		$aoi_event_node_id = $ewrapper->getIdentifier();
		_lsf_aoi_set_aoi_event_node_id_in_postgres($aoi_event_row->aoi_event_id, $aoi_event_node_id);
		watchdog('lsf_aoi', t('Created AOI event node for AOI: ' . $aoi_parent_node['title']), array(), WATCHDOG_INFO);
	} catch (Exception $e) {
		watchdog('lsf_aoi', t($e->getMessage()), array(), WATCHDOG_ERROR);
	}
}


