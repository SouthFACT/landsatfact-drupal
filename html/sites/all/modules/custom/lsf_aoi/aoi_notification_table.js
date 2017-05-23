(function ($) {
    "use strict";

    $(document).ready(bindClickHandlers);

    function bindClickHandlers () {
        var $table = $(".field-name-aoi-notification-table");
        $table.on("click", ".table tbody tr", loadLayer);
    }

    function loadLayer (event) {
	var $this = $(this);
	toggleRowClasses($this);
        var date = formatDate($this);
        var olMap = $('#openlayers-map');
        var map = olMap.data('openlayers').openlayers;
        var currentLayer = olMap.data('layer');
        if (currentLayer) {
            map.removeLayer(currentLayer);
        }

        var layer = $this.data('layer') || createLayer(date, $this);
        map.addLayer(layer);
        olMap.data('layer', layer);
    }

    function toggleRowClasses ($elem) {
        $elem.siblings(".aoi-layer-loaded").removeClass("aoi-layer-loaded");
        $elem.addClass("aoi-layer-loaded");
    }

    function formatDate ($elem) {
	var date = $elem.find(".views-field-field-date-detected").text().trim().split("/");
	var dateString = date.splice(2, 1).concat(date).join("-");
	return dateString;
    }

    function createLayer (date, elem) {
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
	elem.data('layer', layer);
        return layer;
    }
}(window.jQuery));
