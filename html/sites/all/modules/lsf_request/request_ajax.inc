<?php

/**
 * General purpose handler to get data/vaidation from the postgres database
 * without creating a plethora of endpoints
 *
 * Parameters are passed to this endpoint in POST requests, and will be
 * documented for each subhandler. 
 */
function _lsf_request_ajax() {
    if ($_REQUEST['type'] === 'county_geoid') {
        $result = _lsf_request_county_geoid($_POST['geoid']);
    } else if ($_REQUEST['type'] === 'wrs2_request') {
        $result = _lsf_request_scenes_by_geojson_date($_POST['geojson'], $_POST['year'], $_POST['month'], $_POST['day']);
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
function _lsf_request_county_geoid($geoid) {
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

/**
 * Gets scenes for an area of geojson for a specific date
 *
 * @param string $geojson;
 * @param string $year;
 * @param string $month;
 * @param string $day;
 * @return array Array containing the WRS2 codes for the initial scenes
 */
function _lsf_request_scenes_by_geojson_date($geojson, $year, $month, $day) {
    try {
        geophp_load();
        $geom = geophp::load($geojson);
        $geojson_writer = new GeoJSON();
        _lsf_request_set_database_connection();
        $date = $year . '-' . $month . '-' . $day;

        $result = db_query('SELECT * FROM get_scenesMostRecent(:geojson, :date)', array(
            ':geojson' => $geojson_writer->write($geom),
            ':date' => $date
        ))->fetchAll();

        db_set_active();
        return $result;
    } catch (Exception $e) {
        db_set_active();
        return $e;
    }
}