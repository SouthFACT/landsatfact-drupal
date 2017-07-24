<?php

// functions which let users subscribe to aoi's that only send email notifications

// Determines if aoi node is a legacy aoi. Returns TRUE if it is, FALSE if new aoi.
//
// @param int $nid NID of target aoi node
function _lsf_aoi_subscription_check_legacy($nid) {
    $AREA_LIMIT = 50000;
    $node = node_load($nid);
    if (
        intval($node->field_generate_zonal_stats[LANGUAGE_NONE][0]['value']) === 0 ||
        intval($node->field_aoi_area_acres[LANGUAGE_NONE][0]['value'], 10) > $AREA_LIMIT) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// Creates or deletes subscription depending on if one exists
//
// @param int $uid Current user id
// @param int $nid NID of target aoi node
function _handle_legacy_aoi_subscription($uid, $nid) {
    if (_check_if_user_is_subscribed($uid, $nid) === FALSE) {
        return _subscribe_user_to_legacy_aoi($uid, $nid);
    } else {
        return _unsubscribe_user_from_legacy_aoi($uid, $nid);
    }
}

function _subscribe_user_to_legacy_aoi($uid, $nid) {
    $code = _create_aoi_subscription_node($uid, $nid);
    _lsf_insert_legacy_aoi_subscription($uid, $nid);
    return $code;
}

function _unsubscribe_user_from_legacy_aoi($uid, $nid) {
    $subscription_nid = _get_subscription_nid($uid, $nid);
    _lsf_remove_legacy_aoi_subscription($subscription_nid);
    node_delete($subscription_nid);
    return 'unsubscribed';
}

// Inserts legacy aoi subscription to the postgres db
//
// @param int $uid Current user id
// @param int $nid NID of target aoi node
function _lsf_insert_legacy_aoi_subscription($uid, $nid) {
    $subscription_nid = _get_subscription_nid($uid, $nid);
    $aoi_node = node_load($nid);

    geophp_load();
    $geom = geophp::load($aoi_node->field_area_geojson[LANGUAGE_NONE][0]['geom']);
    $geojson_writer = new GeoJSON();

    _lsf_aoi_set_database_connection();

    try {
        $result = db_query('SELECT * FROM insert_user_aoi_by_geojson(:nid, :uid, :title, :type, :geojson)',
                           array(
                               ':nid' => $subscription_nid,
                               ':uid' => $uid,
                               ':title' => $aoi_node->title,
                               ':type' => 'subscription',
                               ':geojson' => $geojson_writer->write($geom)
                           ));
    } catch (Exception $e) {
        drupal_set_message('Exception: ' . $e);
    }

    // Sets the db back to the default one
    db_set_active();
}

// Removes legacy aoi subscription from the postgres db
//
// @param object node
function _lsf_remove_legacy_aoi_subscription($nid) {
    _lsf_aoi_set_database_connection();
    try {
        $result = db_query('SELECT * FROM delete_user_aoi_by_nid(:nid)',
                           array(
                               ':nid' => $nid,
                           ));
    } catch (Exception $e) {
        drupal_set_message('Exception: ' . $e);
    }
    // Sets the db back to the default one
    db_set_active();
}
