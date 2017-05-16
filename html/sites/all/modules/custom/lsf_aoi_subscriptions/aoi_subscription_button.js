(function ($) {
    "use strict";

    $(document).ready(buildSubButton);

    var nid;

    function buildSubButton () {
	nid = window.Drupal.settings.aoi_subscription.nid;

	var button = $("<button></button>")
	    .addClass("subscription-button")
	    .text("+ Subscribe")
	    .on("click", handleSubButtonClick);

	$(".node-aoi").before(button);
    }

    var xhr;

    function handleSubButtonClick (e) {
	e.preventDefault();
	console.log(nid);
	xhr = $.ajax({
	    type : "POST",
	    url  : "/aoisub/ajax",
	    data : {
		"type" : "subscription_add",
		"nid"  : nid
	    },
	    success : function (result) {
		console.log(result);
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
}(window.jQuery));
