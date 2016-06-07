/**
 * The functions within handle the interactive elements of custom requests
 */
(function () {
    "use strict";

    var $ = $ || jQuery;
    var xhr;
    var geojson;
    var alt_scenes = {}; // caches alternate scenes keyed by id.

    // caches selectors used for the svg scene maps
    var initial_table_selector = "#map-d3";

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
		add_svg_aoi(geojson);

		get_initial_scenes();
		get_end_scenes();
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
	if (area_wkt === "") return;

	if (xhr) {
	    xhr.abort();
	    xhr = undefined;
	}

	if (!wellknown) return;

	var area_geojson = wellknown.parse(area_wkt);

	geojson = JSON.stringify(area_geojson);
	$("#edit-field-area-geojson-und-0-geom").val(geojson);
	add_svg_aoi(geojson);
	get_initial_scenes();
	get_end_scenes();
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

	populate_scene_input_fields(dates, input_selector);
    }

    function get_end_scenes () {
	var dates = get_end_dates();
	var input_selector = "#field-end-scene-values";

	populate_scene_input_fields(dates, input_selector);
    }

    /**
     * Gets the current wrs2 for a scene and inserts the UI for picking an alternate version,
     * inserts the wrs2 value into the appropriate input fields and kicks off the population
     * of alternate wrs2 id's for a scene.
     *
     * @arg date Object - day, month and year of the initial or end date
     * @arg input_selector String - id of the parent of the input fields for the initial or end date
     */
    function populate_scene_input_fields (date, input_selector) {
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
		var container;
		var scene;
		var i;
		var $input_fields = $(input_selector + " .form-text");
		var $input_field;

		$input_fields.val("");
		container = $input_fields.siblings(".scene-container");
		container.children(".alt-prev-button").off("click", button_left_handler);
		container.children(".alt-next-button").off("click", button_right_handler);
		container.remove();

		for (i = 0; i < result.length; i++) {
		    scene = result[i];
		    populate_alternate_scenes(scene.scene_id, date);

		    $input_field = $($input_fields[i]);
		    $input_field.val(scene.scene_id);
		    container = create_scene_container(scene);
		    container.insertBefore($input_field);
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

    /**
     * Caches metadata for the alternate dates of a scene
     *
     * @arg scene_id String
     * @arg date Object - mostly deprecated but still required by other functions, so it is required.
     */
    function populate_alternate_scenes (scene_id, date) {
	var year = date.year;
	var month = date.month;
	var day = date.day;

	var wrs2 = get_wrs2_from_scene(scene_id);
	
	if (!wrs2 || !year || !month || !day) {
	    return;
	}

	if (alt_scenes[wrs2]) {
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
		if (!alt_scenes[wrs2]) alt_scenes[wrs2] = result;
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
     * Creates inner container for a scene that displays the image & metadata
     *
     * @arg scene Object - Object that contains metadata for scene. Needs the keys
     *    - scene_id
     *    - browse_url
     *    - acquistion_date
     *    - cc_full
     * @return $container jQuery Object - jQuery element that represents the container dom object
     */
    function create_inner_scene_container (scene) {
	var $container = $("<div></div>").addClass("inner-scene-container").data("id", scene.scene_id);
	$container.append($("<img/>").attr("src", scene.browse_url));
	$container.append($("<p><span>Date</span>: " + scene.acquistion_date + "</p>"));
	$container.append($("<p><span>Cloud Cover</span>: " + scene.cc_full + "%</p>"));
	$container.append($("<p><span>ID</span>: " + scene.scene_id + "</p>"));

	return $container;
    }

    /**
     * Creates overall wrapper for each scene. Sets up arrows and inner container.
     */
    function create_scene_container (scene) {
	var innerContainer = create_inner_scene_container(scene);

	var leftButton = $("<button></button>")
	    .addClass("alt-prev-button").addClass("alt-button")
	    .click(button_left_handler);

	var rightButton = $("<button></button>")
	    .addClass("alt-next-button").addClass("alt-button")
	    .click(button_right_handler);

	var scene_date = get_date_from_scene(scene.scene_id);
	var wrs2 = get_wrs2_from_scene(scene.scene_id);
	if (alt_scenes[wrs2]) {
	    var current_index = find_current_scene_index(alt_scenes[wrs2], scene_date);
	    if (current_index === 0) {
		leftButton.css("opacity", "0");
	    }

	    if (current_index === (alt_scenes[wrs2].length - 1)) {
		rightButton.css("opacity", "0");
	    }
	}

	var $megacontainer = $("<div></div>").addClass("scene-container");

	$megacontainer.prepend(leftButton);
	$megacontainer.append(innerContainer);
	$megacontainer.append(rightButton);

	return $megacontainer;
    }

    function add_svg_basemaps () {
	var initial_svg = create_svg_elem(initial_table_selector)

	d3.json("/sites/all/modules/lsf_request/geojson/lsf_states.json", function (json) {
	    var $svg = $(initial_table_selector + " svg");
	    var width = parseInt($svg.width(), 10);
	    var height = parseInt($svg.height(), 10);

	    var path = generate_d3_geopath(width, height);
	    initial_svg.insert("path", ":first-child")
		.datum(json)
		.attr("d", path);

	});
    }

    function create_svg_elem (selector) {
	var WIDTH_HEIGHT_RATIO = 4/7;
        
	var $td = $("<td></td>").attr("colspan", "2").addClass("map-wrapper")
	var $tr = $("<tr></tr>").append($td);
        var $div = $("<div></div>").addClass("field-group-format-wrapper map-wrapper");
 
	$(selector + " tbody").prepend($tr);
        $(selector).append($div);
	var svg = d3.select(selector + " .map-wrapper").append("svg");

	var $svg = $(selector + " svg");

	var width = parseInt($svg.width(), 10);
	var height = Math.floor(width * WIDTH_HEIGHT_RATIO);

        height = 250;
	//if (height > 400) {
	//    height = 400;
	//}

	$svg.css("height", height + "px");
	
	return svg;
    }

    function generate_d3_geopath (width, height) {
	var projection = d3.geo.mercator()
            .center([-91, 32.5])
            .scale(800)
	    .translate([width / 2, height / 2]);

	var path = d3.geo.path()
            .projection(projection);

	return path;
    }

    function add_svg_aoi (aoi) {
	var $svg = $(initial_table_selector + " svg");
	var width = parseInt($svg.width(), 10);
	var height = parseInt($svg.height(), 10);

	var path = generate_d3_geopath(width, height);

	var initial_svg = d3.select(initial_table_selector + " svg");

	initial_svg.selectAll(".aoi").remove();

        aoi = JSON.parse(aoi);
        initial_svg.append("path")
	    .datum(aoi)
	    .attr("d", path)
	    .attr("class", "aoi");
	
	$.ajax({
	    type : "POST",
	    url  : "/custom-request/ajax",
	    data : {
		"type" : "scene_json",
		"geojson" : geojson
	    },
	    success : function (result) {
		var $svg = $(initial_table_selector + " svg");
		var width = parseInt($svg.width(), 10);
		var height = parseInt($svg.height(), 10);

		var path = generate_d3_geopath(width, height);

		var initial_svg = d3.select(initial_table_selector + " svg");
		initial_svg.selectAll(".scene").remove();

		var scene, i;
		for (i = 0; i < result.length; i++) {
		    scene = result[i];
		    initial_svg.insert("path", ":last-child")
			.datum(JSON.parse(scene.geojson))
			.attr("d", path)
			.attr("scene", scene.wrs2_code)
			.attr("class", "scene");
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

    function button_handler (e) {
	e.preventDefault();
    }

    function button_left_handler (e) {
	e.preventDefault();

	var $this = $(this);
	var checkScene = $this.next();

	var scene_id = checkScene.data("id");
	var scene_date = get_date_from_scene(scene_id);
	var wrs2 = get_wrs2_from_scene(scene_id);
	if (alt_scenes[wrs2]) {
	    var possible_scenes = alt_scenes[wrs2];
	} else {
	    return;
	}

	var current_index = find_current_scene_index(possible_scenes, scene_date);
	var next_index = current_index - 1;

	if (possible_scenes[next_index]) {
	    var next_image = create_inner_scene_container(possible_scenes[next_index]);
	    checkScene.replaceWith(next_image);
	    $this.parent().siblings("input").val(possible_scenes[next_index].scene_id);
	}
	
	if (next_index === 0 || current_index === 0) {
	    $this.css("opacity", "0")
	}

	$this.siblings("button").css("opacity", "1");
    }

    function button_right_handler (e) {
	e.preventDefault();

	var $this = $(this);
	var checkScene = $this.prev();

	var scene_id = checkScene.data("id");
	var scene_date = get_date_from_scene(scene_id);
	var wrs2 = get_wrs2_from_scene(scene_id);
	if (alt_scenes[wrs2]) {
	    var possible_scenes = alt_scenes[wrs2];
	} else {
	    return;
	}

	var current_index = find_current_scene_index(possible_scenes, scene_date);
	var next_index = current_index + 1;

	if (possible_scenes[next_index]) {
	    var next_image = create_inner_scene_container(possible_scenes[next_index]);
	    checkScene.replaceWith(next_image);
	    $this.parent().siblings("input").val(possible_scenes[next_index].scene_id);
	}
	
	if (next_index === possible_scenes.length - 1 || current_index === possible_scenes.length - 1) {
	    $this.css("opacity", "0")
	}

	$this.siblings("button").css("opacity", "1");
    }

    function highlight_scene_enter_handler () {
	$("path.scene.active").attr("class", "scene");

	var $this = $(this);
	var scene_id = $this.find("input").val();
	if (!scene_id) {
	    scene_id = $this.data("id");
	}
	if (!scene_id) {
	    return;
	}

	var wrs2 = get_wrs2_from_scene(scene_id);
        var path = $(".map-wrapper").find(".scene[scene='" + wrs2 + "']");
	
 	 path.insertBefore(path.siblings().last());

	// jQuery's addClass does not work for svg elements
	path.attr("class", "scene active");
    }

    function highlight_scene_exit_handler () {
	var $this = $(this);
	var scene_id = $this.find("input").val();
	if (!scene_id) {
	    scene_id = $this.data("id");
	}
	if (!scene_id) {
	    return;
	}

	var wrs2 = get_wrs2_from_scene(scene_id);
	var path = $(".map-wrapper").find(".scene[scene='" + wrs2 + "']");
	path.attr("class", "scene");
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

    function add_draw_area_titles () {
	$(".olControlDrawFeaturePolygonItemInactive").attr("title", "Draw area of interest");
	$(".olControlModifyFeatureItemActive").attr("title", "Pan/Zoom");
    }

    function clearAOISVG(){

      var initial_svg = d3.select(initial_table_selector + " svg");

      initial_svg.selectAll(".aoi").remove();
    }

    function clearSceneSVG(){

      var initial_svg = d3.select(initial_table_selector + " svg");

      initial_svg.selectAll(".scene").remove();

    } 

    function deleteShapes() {
      var draw_area = $(".field-name-field-custom-area");
      var map_selector = ".openlayers-map";
      var layer_id = "openlayers_behavior_geofield";
    
      var layer = draw_area.find(map_selector).data("openlayers").openlayers.getLayersBy("drupalID", layer_id)[0];
    
      //clear all
      layer.removeAllFeatures();
      layer.destroyFeatures();
      layer.addFeatures([]);

      $("#edit-field-area-geojson-und-0-geom").val ('');
      //force change
      $("#edit-field-area-geojson-und-0-geom").change();    

      clearAOISVG();
      clearSceneSVG();
    };
   
   function shapefile_error(msg){
      $('#shapefile-upload-error').remove();
      deleteShapes();
      $('.scene-container').empty()
      $('.field-name-field-area-shapefile ').prepend('<div id="shapefile-upload-error" class="alert alert-danger" role="alert"><strong>Error getting shapefile: </strong>' + msg + '</dv>'); 
      console.log(msg);
      throw new Error(msg);
   }

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

      function convertToGeoJSON(data){
        shp(data).then(function(geoJson){
          geojson = JSON.stringify(geoJson);
          var errors = geojsonhint.hint(geojson); 
          if(geoJson.features.length === 0){
            shapefile_error('No Features in shapefile');
          }else{
            //good shape file add and find scenes.
	    $("#edit-field-area-geojson-und-0-geom").val(geojson);
	    console.log(geojson);
            add_svg_aoi(geojson);
	    get_initial_scenes();
	    get_end_scenes();
         }
        });
      }

      function inspectZipFile(file){
        return JSZip.loadAsync(file)
            .then(function(zip) {
              var needsExt = checkfile(zip);
              if (needsExt.length >= 1){
                shapefile_error("The zip file is missing files with these extensions: " + needsExt);
              }else{
                convertToGeoJSON(file)
              }
            }, function (e) {
                   shapefile_error("Error reading " + file.name + " : " + e.message); 
            });
      }

      function readerLoad() {
          if (this.readyState !== 2 || this.error) {
              return;
          }
          else {
              inspectZipFile(this.result);
          }
      }

      function handleZipFile(file) {
          var reader = new FileReader();
          reader.onload = readerLoad;
          return reader.readAsArrayBuffer(file);
      }

    function handle_shp_upload(){
        $('#shapefile-upload-error').remove();
        $('#shapefile-upload-error').remove();
        $('#shapefile-upload-error').remove();
        var self = $(this);
        var file = self[0].files[0]
        if (file.name.slice(-3) === 'zip') {
            var f =  handleZipFile(file);
            //console.log(f)
        } else {
          shapefile_error('shapefiles must be in zip file');
       }
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

        $("#edit-field-area-shapefile-und-0-upload").on("change", handle_shp_upload);


        $("li#deleteShapes").on('click',deleteShapes);

	$(".geofield_wkt").on("change", handle_draw_area_change)

	add_svg_basemaps();
	add_openlayers_change_listeners();
	add_draw_area_titles();
	$("#field-initial-scene-values .form-type-textfield").hover(highlight_scene_enter_handler, highlight_scene_exit_handler);
	$("#field-end-scene-values .form-type-textfield").hover(highlight_scene_enter_handler, highlight_scene_exit_handler);


    });

}());
