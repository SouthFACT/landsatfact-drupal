<?php

// Implements hook_node_insert
//
// @param array node
function lsf_aoi_subscriptions_node_insert($node) {
    if ($node->type === 'aoi_subscription') {
        _insert_subscription_in_postgres($node);
    }
}

// Implements hook_node_delete
//
// @param array node
function lsf_aoi_subscriptions_node_delete($node) {
    if ($node->type === 'aoi_subscription') {
        _remove_subscription_in_postgres($node);
    }
}

function _insert_subscription_in_postgres($node) {
    try {
        $aoi_id = _get_parent_aoi_id($node);

        _lsf_aoi_set_database_connection();
        $result = db_query('SELECT * FROM insert_aoi_alert_subscription(:aoi, :uid)',
                           array(
                               ':aoi' => $aoi_id,
                               ':uid' => $node->uid,
                           ));
    } catch (Exception $e) {
        drupal_set_message('Exception: ' . $e);
    }
    db_set_active();
}

function _remove_subscription_in_postgres($node) {
    try {
        $aoi_id = _get_parent_aoi_id($node);

        if (!$aoi_id) {
            return;
        }

        _lsf_aoi_set_database_connection();
        $result = db_query('SELECT * FROM remove_aoi_alert_subscription(:aoi, :uid)',
                           array(
                               ':aoi' => $aoi_id,
                               ':uid' => $node->uid,
                           ));
    } catch (Exception $e) {
        drupal_set_message('Exception: ' . $e);
    }
    db_set_active();
}

function _get_parent_aoi_id($node) {
    $aoi_nid = $node->field_parent_aoi[LANGUAGE_NONE][0]['target_id'];
    $result = db_query('select field_aoi_id_value from field_data_field_aoi_id where entity_id = :nid', 
                       array(
                           ':nid' => $aoi_nid,
                       ));

    $aoi_id = $result->fetchAssoc()['field_aoi_id_value'];

    return $aoi_id;
}