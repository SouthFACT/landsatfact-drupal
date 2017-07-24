(function ($) {
	"use strict";

	$(document).ready(loadLayer);

	function loadLayer () {
		var map = $('#openlayers-map').data('openlayers').openlayers;
		var date = Drupal.settings.date_detected
		var layer = createLayer(date)
		map.addLayer(layer)
	}

	function createLayer (date) {
		var layer = new OpenLayers.Layer.WMS(
			"SWIR Threshold for " + date,
			"http://landsatfact-data-dev.nemac.org/lsf-vrt-swir-threshold",
			{
				projection  : new OpenLayers.Projection("EPSG:900913"),
				units       : "m",
				layers      : "SWIR-archiveCloudGap",
				transparent : true,
				time        : date
			}
		);

		return layer;
	}
}(window.jQuery));
