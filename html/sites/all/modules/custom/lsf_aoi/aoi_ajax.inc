<?php

/**
 * General purpose handler to get data/vaidation from the postgres database
 * without creating a plethora of endpoints
 *
 * Parameters are passed to this endpoint in POST requests, and will be
 * documented for each subhandler. 
 */
function _lsf_aoi_ajax() {
    if ($_REQUEST['type'] === 'geo_acres') {
        $result = _lsf_aoi_geo_acres($_POST['geojson']);
    }

    drupal_json_output($result);
    exit();
}

function _lsf_aoi_geo_acres($geojson) {
    try {
        geophp_load();
        $geom = geophp::load($geojson);
        $geojson_writer = new GeoJSON();

        _lsf_aoi_set_database_connection();

        $result = db_query('SELECT * FROM get_acres_from_geojson(:geojson)', array(
            ':geojson' => $geojson_writer->write($geom),
        ))->fetch();

        db_set_active();
        return $result;
    } catch (Exception $e) {
        db_set_active();
        return $e;
    }
}
