(function ($) {
	"use strict";

	var settings

	// Using Drupal behaviors so preview/event buttons are rebuilt 
	Drupal.behaviors.aoiNotificationTable = {
		attach: function (context, settings) {
			setupTable(settings)
		}
	}

	function setupTable(drupalSettings) {
		settings = drupalSettings
		var previewBtnCells = $('td.views-field-field-preview-button')
		var eventPageCells = $('td.views-field-field-go-to-aoi-event-page-btn')
		previewBtnCells.each(setupPreviewButton)
		eventPageCells.each(setupEventPageLink)
	}

	function setupPreviewButton(i, elem) {
		// Only add the button if it doesn't already exist
		if (!settings.aoi_events[i] || $(elem).children().length) {
			return
		}
		var button = $('<button>Preview</button>')
			.addClass('aoi-event-button')
			.on('click', function (e) {
				loadLayer(e, settings.aoi_events[i].date_detected)
			})
		$(elem).append(button)
	}

	function setupEventPageLink(i, elem) {
		if (!settings.aoi_events[i] || $(elem).children().length) {
			return
		}
		var button = $('<a href="'+settings.aoi_events[i].url+'">Event</a>')
			.addClass('aoi-event-button')
		$(elem).append(button)
	}

	function loadLayer (event, date) {
		var $this = $(this);
		toggleRowClasses($this);
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

	function createLayer (date, elem) {
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
	elem.data('layer', layer);
		return layer;
	}
}(window.jQuery));
