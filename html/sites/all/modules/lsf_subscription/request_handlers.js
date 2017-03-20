/**
 * The functions within handle the interactive elements of custom requests
 */
(function () {
    "use strict";

    var $ = $ || jQuery;
    var xhr;
    var geojson;

    /**
     * reports shapefile upload errors to the user.
     *
     * @arg msg - text containing error message
     *
     * @return nothing
     */
    function shapefile_error(msg){
      $('#shapefile-upload-error').remove();
      deleteShapes();
      $('.scene-container').empty()
      $('.field-name-field-area-shapefile ').prepend('<div id="shapefile-upload-error" class="alert alert-danger" role="alert"><strong>Error getting shapefile: </strong>' + msg + '</dv>');
      $('#edit-actions').prepend('<div id="shapefile-upload-error-submit" class="alert alert-danger" role="alert"><strong>Error getting shapefile: </strong>' + msg + '.  Try to upload the shapefile again.</dv>');
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
        if(geoJson.features.length === 0){
          shapefile_error('No Features in shapefile');
        }else{
          //good shape file add and find scenes.
          $("#edit-field-area-geojson-und-0-geom").val(geojson);
          console.log(geojson);
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
      $("#edit-field-area-shapefile-und-0-upload").on("change", handle_shp_upload);
    });

}());
