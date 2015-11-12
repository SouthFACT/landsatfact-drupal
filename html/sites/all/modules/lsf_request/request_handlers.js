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
		$("#edit-field-area-geojson-und-0-geom").val(geojson);
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

    function get_initial_dates () {
	var year = $("#edit-field-select-dates-und-0-value-year").val();
	var month = $("#edit-field-select-dates-und-0-value-month").val();
	var day = $("#edit-field-select-dates-und-0-value-day").val();

	return  {
	    "year"  : year,
	    "month" : month,
	    "day"   : day
	}
    }

    function get_end_dates () {
	var year = $("#edit-field-end-date-und-0-value-year").val();
	var month = $("#edit-field-end-date-und-0-value-month").val();
	var day = $("#edit-field-end-date-und-0-value-day").val();

	return  {
	    "year"  : year,
	    "month" : month,
	    "day"   : day
	}
    }

    function get_initial_scenes () {
	var dates = get_initial_dates();
	var input_selector = "#field-initial-scene-values";
	var alternate_handler = get_initial_alternate_scenes;

	populate_scene_input_fields(dates, input_selector, alternate_handler);
    }

    function get_end_scenes () {
	var dates = get_end_dates();
	var input_selector = "#field-end-scene-values";
	var alternate_handler = get_end_alternate_scenes;

	populate_scene_input_fields(dates, input_selector, alternate_handler);
    }

    function populate_scene_input_fields (date, input_selector, alternate_handler) {
	var year = date.year;
	var month = date.month;
	var day = date.day;

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
		var scene;
		var i;
		var $input_fields = $(input_selector + " .form-text");
		var $input_field;
		for (i = 0; i < result.length; i++) {
		    scene = result[i];
		    $input_field = $($input_fields[i]);
		    $input_field.val(scene.scene_id);
		    if ($input_field.siblings("img").length === 0) {
			$("<img src='" + scene.browse_url + "' style='width: 200px; height: 200px; display: block;'>")
			    .insertBefore($input_field)
			    .click(alternate_handler);
		    } else {
			$input_field.siblings("img").attr("src", scene.browse_url);
		    }
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

    function get_wrs2_from_scene (scene) {
	return scene.substring(3, 9);
    }

    function get_date_from_scene (scene) {
	return scene.substring(9, 16);
    }

    /**
     * Performs a binary search on the list of scenes to find the index of a scene with
     * a particular date.
     */
    function find_current_scene_index (scenes, current_date) {
	var min = 0,
            max = scenes.length - 1,
	    mid, date;
      
	for (;;) {
            // does a linear search if the list is small enough
            if (min + 11 > max) {
		var i;
		for (i = min; i <= max; i++) {
                    if (current_date === get_date_from_scene(scenes[i].scene_id)) {
			return i;
                    }
		}

		return -1;
	    }

	    // gets midpoint by doing a bitshift 1 bit to the right. Equivalent to
	    //    Math.floor((min + max) / 2)
	    // but is much faster
            mid = (min + max) >> 1;
            date = get_date_from_scene(scenes[mid].scene_id);
            if (current_date === date) {
		return mid;
            } else if (current_date > date) {
		min = mid + 1;
            } else {
		max = mid - 1;
            }
	}
    }

    function get_initial_alternate_scenes () {
	var dates = get_initial_dates();
	populate_alternate_scenes(dates, this);
    }

    function get_end_alternate_scenes () {
	var dates = get_end_dates();
	populate_alternate_scenes(dates, this);
    }

    function populate_alternate_scenes (date, elem) {
	var year = $("#edit-field-end-date-und-0-value-year").val();
	var month = $("#edit-field-end-date-und-0-value-month").val();
	var day = $("#edit-field-end-date-und-0-value-day").val();

	var year = date.year;
	var month = date.month;
	var day = date.day;

	var $parent = $(elem).parent();
	var $input = $(elem).siblings("input"); 
	var scene = $input.val();
	var wrs2 = get_wrs2_from_scene(scene);
	
	if (!wrs2 || !year || !month || !day) {
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
		"type" : "alternate_images",
		"wrs" : wrs2,
		"year" : year,
		"month" : month,
		"day" : day
	    },
	    success : function (result) {
		var scene_date = get_date_from_scene(scene);
		var current_index = find_current_scene_index(result, scene_date);
		var current_image = create_alternate_image_container(result[current_index], $input);
		var prev_image, next_image;
		if (result[current_index - 1]) {
		    prev_image = create_alternate_image_container(result[current_index - 1], $input);
		}
		if (result[current_index + 1]) {
		    next_image = create_alternate_image_container(result[current_index + 1], $input);
		}

		var alt_img_container = $("<div></div>");
		if (prev_image) alt_img_container.append(prev_image);
		alt_img_container.append(current_image);
		if (next_image) alt_img_container.append(next_image);

		if ($input.siblings("div").length === 0) {
		    $parent.append(alt_img_container);
		} else {
		    $input.siblings("div").replaceWith(alt_img_container);
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

    function create_alternate_image_container (scene, $input) {
	var $container = $("<div></div>").data("id", scene.scene_id)
	    .hover(function () {
		$(this).css("background-color", "rgba(0,0,0,.2)")
		    .css("cursor", "pointer");
	    }, function () {
		$(this).css("background-color", "rgba(0,0,0,0)");
	    })
	    .css("display", "inline-block").css("margin-right", "10px").css("padding", "10px").css("border-radius", "1em");
	$container.append($("<img/>").attr("src", scene.browse_url).css({
	    "display": "block",
	    "height": "200px",
	    "width": "200px"
	}));
	$container.append($("<p style='margin: 0;'><span style='font-weight: bold;'>ID</span>: " + scene.scene_id + "</p>"));
	$container.append($("<p style='margin: 0;'><span style='font-weight: bold;'>Date</span>: " + scene.acquistion_date + "</p>"));
	$container.append($("<p style='margin: 0;'><span style='font-weight: bold;'>Cloud Cover</span>: " + scene.cc_full + "%</p>"));
	$container.click(function () {
	    $input.val(scene.scene_id);
	    $input.siblings("img").attr("src", scene.browse_url);
	    $container.parent().remove();
	});

	return $container;
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
