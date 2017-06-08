(function ($) {
    "use strict";

    var nid;

    var settings = window.Drupal.settings;

    $(document).ready(function () {
      if (settings.is_node) {
        buildSubButton(true, settings.aoi_subscription.subscribed, settings.aoi_subscription.nid);
      } else {
        var subStates = settings.aoi_subscription;
        var tableCells = $("td.views-field-field-aoi-subscribe-button");
        tableCells.each(function (i, elem) {
          if (subStates[i] === undefined) {
            return;
          }
          buildSubButton(false, subStates[i].subscribed, subStates[i].nid, elem);
        });
      }
    })

    function buildSubButton (is_node, is_subbed, nid, elem) {
    	var aoi_settings = window.Drupal.settings.aoi_subscription;

    	var button = $("<button></button>")
    	    .addClass("subscription-button")
    	    .toggleClass("subscribed", is_subbed)
    	    .on("click", function (e) {
		handleSubButtonClick(e, nid, this)
            });

	if (is_node) {
	    button.addClass("aoi-button");
	}

    	var buttonSub = $("<span></span>")
    	    .addClass("subscribe-text")
    	    .text("+ Subscribe");

    	var buttonUnsub = $("<span></span>")
    	    .addClass("unsubscribe-text")
    	    .text("- Unsubscribe");

    	button.append(buttonSub);
    	button.append(buttonUnsub);

    	if (is_node) {
	    var wrapper = $("<div></div>")
		.addClass("aoi-node-buttons-wrapper");
	    wrapper.append(button);
	    wrapper.append(buildBackButton());

            $(".node-aoi").before(wrapper);
	} else {
            $(elem).append(button);
	}
    }

    function buildBackButton() {
	var button = $("<a></a>")
	    .text("Browse Your Areas of Interest")
	    .attr("href", "/aoi")
            .on("click", function (e) {
                handleBackButtonClick(e, nid, this)
            })
	    .addClass("aoi-button")
	    .addClass("aoi-browse-view")
	    .addClass("aoi-browse-view-from-node");
 
	return button;
    }

    function handleSubButtonClick (e, nid, btn) {
	e.preventDefault();
	if (!Drupal.settings.aoi_subscription.logged_in) {
	    if (window.location && window.location.href) {
		var path = window.location.pathname;
		window.location.href = "/user/register?destination=" + path;
	    }
	    return;
	}
      var xhr;
      xhr = $.ajax({
        type : "POST",
        url  : "/aoisub/ajax",
        data : {
          "type" : "subscription_add",
          "nid"  : nid
        },
        success : function (result) {
          console.log(result);
          toggleButtonType(btn);
          ga_function('AOI Alerts', result === 'success' ? 'subscribed' : 'unsubscribed' , nid); 
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

   function handleBackButtonClick(e, nid, btn) {
     ga_function('AOI Alerts', 'click' , 'View My AOIS from node');
   }

   function ga_function(category, action, label){
       ga('send', 'event', category, action, label);
   } 
    
    function toggleButtonType (btn) {
      $(btn).toggleClass("subscribed");
    }

}(window.jQuery));
