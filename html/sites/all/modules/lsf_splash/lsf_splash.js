+function ($) {
    var width = 500;
    var height = 600;
    var ratio = 1.2;

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
	draggable: false
    });
}(jQuery);
