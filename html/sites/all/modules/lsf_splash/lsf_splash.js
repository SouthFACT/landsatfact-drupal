+function ($) {
    var width = 500;
    var height = 600;
    var ratio = 1.2;
    var autoOpen = false;
    // If no cookie, then show disclaimer
    if (!Cookies.get('showdisclaimer') || Cookies.get('showdisclaimer') !== "false") {
        autoOpen = true;
    }

    if ($(window).width() < 520) {
	width = $(window).width() - 20;
	height = parseInt(width * ratio, 10);
    }

    $("#disclaimer").dialog({
        show: 'fade',
        hide: 'fade',
        modal: true,
        width: width,
        height: height,
        maxWidth: 600,
        maxHeight: 600,
	draggable: false,
	closeText: 'close',
	autoOpen : autoOpen
    });

    $("#disclaimer_seen").change(setDisclaimerCookie);

    function setDisclaimerCookie() {
        if ($(this).prop("checked") === true) {
            Cookies.set("showdisclaimer", "false", { expires: 365 });
            $("#disclaimer").dialog("close");
        }
    };
}(jQuery);
