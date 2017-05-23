(function ($) {
    "use strict";

    $(document).ready(buildSubButton);

    var nid;

    function buildSubButton () {
	var aoi_settings = window.Drupal.settings.aoi_subscription;

	nid = aoi_settings.nid;

	var button = $("<button></button>")
	    .addClass("subscription-button")
	    .toggleClass("subscribed", aoi_settings.subscribed)
	    .on("click", handleSubButtonClick);

	var buttonSub = $("<span></span>")
	    .addClass("subscribe-text")
	    .text("+ Subscribe");

	var buttonUnsub = $("<span></span>")
	    .addClass("unsubscribe-text")
	    .text("- Unsubscribe");

	button.append(buttonSub);
	button.append(buttonUnsub);

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
		toggleButtonType();
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

    function toggleButtonType () {
	$(".subscription-button").toggleClass("subscribed");
    }
}(window.jQuery));
