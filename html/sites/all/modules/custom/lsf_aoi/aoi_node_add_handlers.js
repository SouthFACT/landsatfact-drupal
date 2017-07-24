/**
 * The functions within handle the interactive elements of custom requests
 */
(function () {
    "use strict";

    var $ = $ || jQuery;
    var xhr;
    var geojson;

    /**
     * Handles any county select list being changed. Hits postgres to get geojson
     * of that counties boundry. Populates field_area_geojson once it has been
     * returned.
     */
    function handle_county_change () {
	var geoid = $(this).val();

	xhr = $.ajax({
	    type : "POST",
	    url  : "/subscription/ajax",
	    data : {
		"type"  : "county_geoid",
		"geoid" : geoid
	    },
	    success : function (result) {
		geojson = result["get_countybygeoid"];
		$("#edit-field-area-geojson-und-0-geom").val(geojson).change();

		xhr = undefined;
	    },
	    error : function (jqXHR, textStatus, errorThrown) {
		console.log("ERROR");
		console.log(jqXHR);
		console.log(textStatus);
		console.log(errorThrown);
	    }
	});
    }

    /**
     * Handles any draw area map being changed. Hits postgres to get geojson
     * of that counties boundry. Populates field_area_geojson once it has been
     * returned.
     */
    function handle_draw_area_change () {
	var area_wkt = $(this).val();
//        console.log(area_wkt + ' - handle_draw_area_change');

	if (area_wkt === "") return;

	if (xhr) {
	    xhr.abort();
	    xhr = undefined;
	}

	if (!wellknown) return;

	var area_geojson = wellknown.parse(area_wkt);

	geojson = JSON.stringify(area_geojson);
	$("#edit-field-area-geojson-und-0-geom").val(geojson).change();
    }

    function add_openlayers_change_listeners () {
	var draw_area = $(".field-name-field-custom-area");
	var map_selector = ".openlayers-map";
	var layer_id = "openlayers_behavior_geofield";

        var $wkt = draw_area.find('input.geofield_wkt');
	var layer = draw_area.find(map_selector).data("openlayers").openlayers.getLayersBy("drupalID", layer_id)[0];

	layer.events.register('featureadded', $wkt, openlayers_change_listener);
        layer.events.register('featureremoved', $wkt, openlayers_change_listener);
        layer.events.register('afterfeaturemodified', $wkt, openlayers_change_listener);
    }

    function openlayers_change_listener () {
	this.change();
    }

    /**
     * reports shapefile upload errors to the user.
     *
     * @arg msg - text containing error message
     *
     * @return nothing
     */
    function shapefile_error(msg){
	$('#shapefile-upload-error').remove();
	$('.scene-container').empty()
	$('.field-name-field-area-shapefile ').prepend('<div id="shapefile-upload-error" class="alert alert-danger" role="alert"><strong>Error getting shapefile: </strong>' + msg + '</dv>');
	$("#edit-submit").prop('disabled', true);
	console.log(msg);
	throw new Error(msg);
    }

    /**
     * checks the zip file for all required files which are .prj, .dbf, .shp
     *
     * @arg zip - the zip file object
     *
     * @return needsExt - returns an array of the files missing.
     */
    function checkfile(zip){
	var MustHaveExt = ['prj','dbf','shp'];
	var hasExt = [];
	var needsExt = [];
	zip.forEach(function (relativePath, zipEntry) {
            var ext = zipEntry.name.slice(-3).toLowerCase();
            hasExt.push(ext);
	});
	needsExt = MustHaveExt.filter(function(val) {
            return hasExt.indexOf(val) == -1;
	});
	return needsExt;
    }

    /**
     * converts the shapefile to GeoJSON
     *
     * @arg data - the shapefile data object
     *
     * @return nothing but does add geojson data to the hidden input
     */
    function convertToGeoJSON(data){
	shp(data).then(function(geoJson){
            geojson = JSON.stringify(geoJson);
            var errors = geojsonhint.hint(geojson);
            if (geoJson.features.length === 0) {
		shapefile_error('No Features in shapefile');
            } else {
		// good shape file add and find scenes.
		$("#edit-field-area-geojson-und-0-geom").val(geojson).change();
            }
	});
    }

    /**
     * inspects the zip fle to make sure its valid and actually a zip file
     *
     * @arg file - the file object
     *
     * @return nothing but uses promises to start the chain of events of unpacking and converthing the shapefile to GeoJSON
     */
    function inspectZipFile(file){
	return JSZip.loadAsync(file)
	    .then(function (zip) {
		var needsExt = checkfile(zip);
		if (needsExt.length >= 1){
		    shapefile_error("The zip file is missing files with these extensions: " + needsExt);
		} else {
		    convertToGeoJSON(file)
		}
	    }, function (e) {
		shapefile_error("Error reading " + file.name + " : " + e.message);
	    });
    }

    /**
     * starts the reading of the zipfile after the Jquery event was triggered clicked upload
     *
     * @arg nothing
     *
     * @return nothing but passes the zip file to next step - inspeting the zipfile
     */
    function readerLoad() {
	if (this.readyState !== 2 || this.error) {
            return;
	}
	else {
            inspectZipFile(this.result);
	}
    }

    /**
     * handle event when user clicks upload buttn
     *
     * @arg file - the file object
     *
     * @return nothing sends the zip file to start reading
     */
    function handleZipFile(file) {
	var reader = new FileReader();
	reader.onload = readerLoad;
	return reader.readAsArrayBuffer(file);
    }

    /**
     * inspects the zip fle to make sure its valid and actually a zip file
     *
     * @arg nothing
     *
     * @return nothing but uses promises to start the chain of events of unpacking and converthing the shapefile to GeoJSON
     */
    function handle_shp_upload(){
	$('#shapefile-upload-error').remove();
	$('#shapefile-upload-error').remove();
	$('#shapefile-upload-error').remove();
	$('#shapefile-upload-error-submit').remove();
	$("#edit-submit").prop('disabled', false);
	var self = $(this);
	var file = self[0].files[0]
	if (file.name.slice(-3) === 'zip') {
            var f =  handleZipFile(file);
            //console.log(f)
	} else {
            shapefile_error('shapefiles must be in zip file');
	}
    }

    function handle_geojson_change () {
	var geojson = $(this).val();
	console.log("hey");
	console.log(geojson)
	if (geojson === "") return;

	xhr = $.ajax({
	    type : "POST",
	    url  : "/aoi/ajax",
	    data : {
		"type"  : "geo_acres",
		"geojson" : geojson
	    },
	    success : function (result) {
		var MAX_ACRES = 50000.0;
		var acres = result["get_acres_from_geojson"];

		if (parseFloat(acres) > MAX_ACRES) {
		    handleAreaTooLarge(acres);
		} else {
		    handleAreaWithinLimit(acres);
		}

		$("#edit-field-aoi-area-acres-und-0-value").val(parseFloat(acres).toFixed(3));

		xhr = undefined;
	    },
	    error : function (jqXHR, textStatus, errorThrown) {
		console.log("ERROR");
		console.log(jqXHR);
		console.log(textStatus);
		console.log(errorThrown);
	    }
	});
    }

    function handleAreaTooLarge (acres) {
        removeAlertPopup();
	insertAlertPopup(acres);
	disableAoiCheckbox();
    }

    function handleAreaWithinLimit () {
	removeAlertPopup();
	enableAoiCheckbox();
    }

    function removeAlertPopup () {
	$(".group-aoi-location .alert").remove();
    }

    function insertAlertPopup (acres) {
	var popup = createAlertPopup(acres);
	$(".group-aoi-location .fieldset-wrapper").prepend(popup);
	$(".group-aoi-location .panel-body").prepend(popup);
    }

    function createAlertPopup (acres) {
	var alertStart = $(document.createElement("strong"));
	var alertText = $(document.createElement("span"));
	var alertPopup = $(document.createElement("div"));

	// trims the decimal and adds in commas at the thousands markers
	acres = acres.replace(/\..*/, "").replace(/\B(?=(\d{3})+(?!\d))/g, ",");

	alertStart.text("Heads up! ");
	alertText.html("The area you selected is <strong>" + acres + "</strong> acres. We can only notify you when change occurs in an area this large. If you require zonal statistics to be generated for you please reduce the area to one with fewer than <strong>50,000</strong> acres.");
	alertPopup.append(alertStart);
	alertPopup.append(alertText);
	alertPopup.addClass("alert").addClass("alert-info");

	return alertPopup;
    }

    function disableAoiCheckbox () {
	var $checkbox = $("#edit-field-generate-zonal-stats-und");
	$checkbox.attr("disabled", true);

	// cache for re-enabling
	var checked = $checkbox.prop("checked");
	$checkbox.data("checked", checked);
	$checkbox.prop("checked", false);
    }

    function enableAoiCheckbox () {
	var $checkbox = $("#edit-field-generate-zonal-stats-und");
	$checkbox.attr("disabled", false);

	var checked = $checkbox.data("checked");
	$checkbox.prop("checked", checked);
    }

    /**
     * google event tracker
     *  see google anatlyics events at https://developers.google.com/analytics/devguides/collection/analyticsjs/events
     * @arg category - the category of the google analytics event
     *      action - the action of the google analytics event
     *      label - the label of the google analytics event
     *
     * @return nothing
     */
    function ga_function(category, action, label){
        ga('send', 'event', category, action, label);
    }

    $(document).ready(function () {
	$("#edit-field-al-counties-und").on("change", handle_county_change);
	$("#edit-field-ar-counties-und").on("change", handle_county_change);
	$("#edit-field-fl-counties-und").on("change", handle_county_change);
	$("#edit-field-ga-counties-und").on("change", handle_county_change);
	$("#edit-field-ky-counties-und").on("change", handle_county_change);
	$("#edit-field-la-counties-und").on("change", handle_county_change);
	$("#edit-field-ms-counties-und").on("change", handle_county_change);
	$("#edit-field-nc-counties-und").on("change", handle_county_change);
	$("#edit-field-ok-counties-und").on("change", handle_county_change);
	$("#edit-field-sc-counties-und").on("change", handle_county_change);
	$("#edit-field-tn-counties-und").on("change", handle_county_change);
	$("#edit-field-tx-counties-und").on("change", handle_county_change);
	$("#edit-field-va-counties-und").on("change", handle_county_change);

        $("#edit-field-area-shapefile-und-0-upload").on("change", handle_shp_upload);
        $(".geofield_wkt").on("change", handle_draw_area_change);

	$("#edit-field-area-geojson-und-0-geom").on("change", handle_geojson_change);

        add_openlayers_change_listeners(); 
    });

}());
