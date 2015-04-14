jQuery(document).ready(function populate_geojson() { 
	var geojson = Drupal.settings.lsf_subscription.geojson;
	jQuery("#edit-field-area-geojson-und-0-geom").val(geojson);	
});