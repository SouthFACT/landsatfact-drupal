"use strict";

(function ($) {
    $.get('/sites/all/modules/lsf_subscription/mockup.csv', function(data) {
	var products = processFileData(data);
	var $table = buildTable(products);
	$table.on("click", "a.date-loader", loadLayer);
	$.ready(insertTable($table));
	console.log(products);
    });

    function processFileData(data) {
	var lines = data.split("\n");
	var products = [];
	var bbox;
	lines.forEach(function (e) {
	    var i;

	    var line = e.split(",");

	    bbox = bbox ? bbox : line[3];

	    var product = {
		"base": [],
		"comparison": []
	    };
	    for (i = 0; i < products.length; i++) {
		if (products[i].date === line[0]) {
		    product = products[i];
		    break;
		}
	    }

	    product.base.push(line[1]);
	    product.comparison.push(line[2]);

	    if (!product.date) {
		product.date = line[0];
		product.viewer = makeViewerLink(product.date, bbox);
		products.push(product);
	    }
	})

	return products.reverse();
    }

    function makeViewerLink(date, bbox) {
	date = date.replace(/\-/g, "");
	bbox = bbox.replace(" BOX(", "").replace(")", "").replace(/\s/g, ",");
	var link = "http://www.landsatfact.com/maps/?theme=SE&layers=TSHSWIR" + date + ",AA&mask=Forest,CloudGap&alphas=1,1&accgp=G02&basemap=Basic&extent=" + bbox;
	return link;
    };

    function buildTable(products) {
	var $table = $('<table></table>').addClass("table");
	$table.append(buildTableHeader())
	    .append(buildTableBody(products));
	return $table;
    }

    function buildTableHeader() {
	var header = $('<thead></thead>');
	var headerRow = $('<tr></tr>');
	headerRow.append($('<th>Date</th>'));
	headerRow.append($('<th>More Data</th>'));
	headerRow.append($('<th>Base Scene(s)</th>'));
	headerRow.append($('<th>Comparison</th>'));
	header.append(headerRow);

	return header;
    }

    function buildTableBody(products) {
	var i;
	var body = $('<tbody></tbody>');
	for (i = 0; i < products.length; i++) {
	    body.append(buildBodyRow(products[i]));
	}
	return body;
    }

    function buildBodyRow(product) {
	var row = $('<tr></tr>');
	row.append($('<td><a class="date-loader">' + product.date + '</a></td>'));
	row.append($('<td><a href="' + product.viewer + '" target="_blank">Display in viewer</a></td>'));
	row.append($('<td>' + product.base.join('<br>') + '</td>'));
	row.append($('<td>' + product.comparison.join('<br>') + '</td>'));
	return row;
    }

    function insertTable(table) {
	$('.node-subscription').append(table);
    }

    function loadLayer(event) {
	event.preventDefault();
	var date = $(this).text();
	var map = $('.openlayers-map').data('openlayers');
	var layer = $(this).data('layer') ? $(this).data('layer') : createLayer(date, $(this));
	console.log(map)

	map.openlayers.addLayer(layer);
    }

    function createLayer(date, elem) {
	var layer = new OpenLayers.Layer.WMS(
            "SWIR Threshold for " + date,
            "http://landsatfact-data.nemac.org/lsf-swir-threshold",
            {
                projection  : new OpenLayers.Projection("EPSG:900913"),
                units       : "m",
                layers      : "SWIR-archiveMaskForForestCloudGap",
                transparent : true,
		time        : date
            }
        );

	elem.data('layer', layer);
	return layer;
    }
}(jQuery));
