(function ($) {
    "use strict";

    $(document).ready(loadLayer);

    function loadLayer () {
        var map = $('#openlayers-map').data('openlayers').openlayers;
        var date = formatDate();
        var layer = createLayer(date);
        map.addLayer(layer);
    }

    function formatDate () {
	var date = $(".field-name-field-date-detected .field-items").text().trim().split("/");
	var dateString = date.splice(2, 1).concat(date).join("-");
	return dateString;
    }

    function createLayer (date) {
        var layer = new OpenLayers.Layer.WMS(
            "SWIR Threshold for " + date,
            "http://landsatfact-data.nemac.org/lsf-vrt-swir-threshold",
            {
		projection  : new OpenLayers.Projection("EPSG:900913"),
		units       : "m",
		layers      : "SWIR-archiveMaskForForestCloudGap",
		transparent : true,
		time        : date
            }
        );

        return layer;
    }
}(window.jQuery));
