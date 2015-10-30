/**
 * The functions within handle the interactive elements of custom requests
 */
(function () {
    "use strict";

    // caches jQuery
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
	    url  : "/custom-request/ajax",
	    data : {
		"type"  : "county_geoid",
		"geoid" : geoid
	    },
	    success : function (result) {
		geojson = result["get_countybygeoid"];
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

    function get_initial_scenes () {
	var year = $("#edit-field-select-dates-und-0-value-year").val();
	var month = $("#edit-field-select-dates-und-0-value-month").val();
	var day = $("#edit-field-select-dates-und-0-value-day").val();
	if (!geojson || !year || !month || !day) {
	    return;
	}

	if (month.length === 1) {
	    month = "0" + month;
	}

	if (day.length === 1) {
	    day = "0" + day;
	}

	$.ajax({
	    type : "POST",
	    url  : "/custom-request/ajax",
	    data : {
		"type"  : "wrs2_request",
		"geojson" : geojson,
		"year" : year,
		"month" : month,
		"day" : day
	    },
	    success : function (result) {
		console.log(result);
		var scene;
		var i;
		var $input_fields = $("#field-initial-scene-values .form-text");
		var $input_field;
		console.log($input_fields);
		for (i = 0; i < result.length; i++) {
		    scene = result[i];
		    $input_field = $($input_fields[i]);
		    $input_field.val(scene.scene_id);
		    $("<img src='" + scene.browse_url + "' style='width: 200px; height: 200px;'>").insertBefore($input_field);
		}
	    },
	    error : function (jqXHR, textStatus, errorThrown) {
		console.log("ERROR");
		console.log(jqXHR);
		console.log(textStatus);
		console.log(errorThrown);
	    }
	});	
    }

    function get_end_scenes () {
	var year = $("#edit-field-end-date-und-0-value-year").val();
	var month = $("#edit-field-end-date-und-0-value-month").val();
	var day = $("#edit-field-end-date-und-0-value-day").val();
	if (!geojson || !year || !month || !day) {
	    return;
	}

	if (month.length === 1) {
	    month = "0" + month;
	}

	if (day.length === 1) {
	    day = "0" + day;
	}

	$.ajax({
	    type : "POST",
	    url  : "/custom-request/ajax",
	    data : {
		"type"  : "wrs2_request",
		"geojson" : geojson,
		"year" : year,
		"month" : month,
		"day" : day
	    },
	    success : function (result) {
		console.log(result);
		var scene;
		var i;
		var $input_fields = $("#field-end-scene-values .form-text");
		var $input_field;
		console.log($input_fields);
		for (i = 0; i < result.length; i++) {
		    scene = result[i];
		    $input_field = $($input_fields[i]);
		    $input_field.val(scene.scene_id);
		    $("<img src='" + scene.browse_url + "' style='width: 200px; height: 200px;'>").insertBefore($input_field);
		}
	    },
	    error : function (jqXHR, textStatus, errorThrown) {
		console.log("ERROR");
		console.log(jqXHR);
		console.log(textStatus);
		console.log(errorThrown);
	    }
	});	
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

	$("#edit-field-select-dates-und-0-value-year").on("change", get_initial_scenes);
	$("#edit-field-select-dates-und-0-value-month").on("change", get_initial_scenes);
	$("#edit-field-select-dates-und-0-value-day").on("change", get_initial_scenes);

	$("#edit-field-end-date-und-0-value-year").on("change", get_end_scenes);
	$("#edit-field-end-date-und-0-value-month").on("change", get_end_scenes);
	$("#edit-field-end-date-und-0-value-day").on("change", get_end_scenes);
    });
}());
