<?php

/**
 * General purpose handler to get data/vaidation from the postgres database
 * without creating a plethora of endpoints
 *
 * Parameters are passed to this endpoint in POST requests, and will be
 * documented for each subhandler. 
 */
function _lsf_subscription_ajax() {
    if ($_REQUEST['type'] === 'county_geoid') {
        $result = _lsf_subscription_county_geoid($_POST['geoid']);
    }

    drupal_json_output($result);
    exit();
}

/**
 * Gets geojson for a county from its geoid.
 *
 * @param string $geoid;
 * @return object Object with key of `get_countybygeoid` that contains the geojson
 */
function _lsf_subscription_county_geoid($geoid) {
    try {
        _lsf_request_set_database_connection();
        $result = db_query('SELECT * FROM get_countyByGEOID(:geoid)', array(
            ':geoid' => $geoid,
        ))->fetch();
        db_set_active();
        return $result;
    } catch (Exception $e) {
        db_set_active();
        return $e;
    }
}

