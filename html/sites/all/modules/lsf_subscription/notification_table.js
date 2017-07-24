"use strict";

(function ($) {

	$(document).ready(function () {
		$.get('/sites/all/modules/lsf_subscription/mockup.csv', function(data) {
			var products = processFileData(data);
			var $table = buildTable(products);
			$table.on("click", "tbody tr", loadLayer);
			insertTable($table);
		});
	})

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
	headerRow.append($('<th>Date (click to see data)</th>'));
	headerRow.append($('<th>More Context</th>'));
	headerRow.append($('<th>Initial Scene(s)</th>'));
	headerRow.append($('<th>End Scene(s)</th>'));
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
	var row = $('<tr style="cursor:pointer;"></tr>');
	row.append($('<td><span class="date-loader" data-date="' + product.date + '">' + product.date + '</span></td>'));
	row.append($('<td><a href="' + product.viewer + '" style="text-decoration: underline;" target="_blank">Explore in Forest Change Viewer</a></td>'));
	row.append($('<td>' + product.base.join('<br>') + '</td>'));
	row.append($('<td>' + product.comparison.join('<br>') + '</td>'));
	return row;
    }

    function insertTable(table) {
	$('.node-subscription').append(table);
    }

    function loadLayer(event) {
	$(this).siblings(".success").removeClass("success");
	$(this).addClass("success");
	var date = $(this).find("span.date-loader").data('date');
	var olMap = $('.openlayers-map');
	var map = olMap.data('openlayers').openlayers;
	var currentLayer = olMap.data('layer');
	if (currentLayer) {
	    map.removeLayer(currentLayer);
	}
	
	var layer = $(this).data('layer') ? $(this).data('layer') : createLayer(date, $(this));
	map.addLayer(layer);
	olMap.data('layer', layer);
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
