<?php
/**
 * @file
 * southfact_aoi.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function southfact_aoi_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'aoi_notification_table';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'AOI Notification Table';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'AOI Notification Table';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'view_node' => 'view_node',
    'field_date_detected' => 'field_date_detected',
    'field_change_area' => 'field_change_area',
    'field_percent_changed' => 'field_percent_changed',
    'field_smallest_patch' => 'field_smallest_patch',
    'field_largest_patch' => 'field_largest_patch',
    'field_patch_indicator' => 'field_patch_indicator',
    'field_url' => 'field_url',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'view_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_date_detected' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_change_area' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_percent_changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_smallest_patch' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_largest_patch' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_patch_indicator' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_url' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No Results Message';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<br>
<div class="alert alert-info">There have not been any change products generated for this Area of Interest yet.</div>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_parent_aoi_target_id']['id'] = 'field_parent_aoi_target_id';
  $handler->display->display_options['relationships']['field_parent_aoi_target_id']['table'] = 'field_data_field_parent_aoi';
  $handler->display->display_options['relationships']['field_parent_aoi_target_id']['field'] = 'field_parent_aoi_target_id';
  $handler->display->display_options['relationships']['field_parent_aoi_target_id']['required'] = TRUE;
  /* Field: Content: Preview Button */
  $handler->display->display_options['fields']['field_preview_button']['id'] = 'field_preview_button';
  $handler->display->display_options['fields']['field_preview_button']['table'] = 'field_data_field_preview_button';
  $handler->display->display_options['fields']['field_preview_button']['field'] = 'field_preview_button';
  $handler->display->display_options['fields']['field_preview_button']['label'] = 'Map Preview';
  $handler->display->display_options['fields']['field_preview_button']['element_label_colon'] = FALSE;
  /* Field: Content: Event Page */
  $handler->display->display_options['fields']['field_go_to_aoi_event_page_btn']['id'] = 'field_go_to_aoi_event_page_btn';
  $handler->display->display_options['fields']['field_go_to_aoi_event_page_btn']['table'] = 'field_data_field_go_to_aoi_event_page_btn';
  $handler->display->display_options['fields']['field_go_to_aoi_event_page_btn']['field'] = 'field_go_to_aoi_event_page_btn';
  $handler->display->display_options['fields']['field_go_to_aoi_event_page_btn']['element_label_colon'] = FALSE;
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['absolute'] = TRUE;
  /* Field: Content: Period of Change */
  $handler->display->display_options['fields']['field_period_of_change']['id'] = 'field_period_of_change';
  $handler->display->display_options['fields']['field_period_of_change']['table'] = 'field_data_field_period_of_change';
  $handler->display->display_options['fields']['field_period_of_change']['field'] = 'field_period_of_change';
  $handler->display->display_options['fields']['field_period_of_change']['alter']['path'] = '[path]';
  $handler->display->display_options['fields']['field_period_of_change']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_period_of_change']['empty'] = 'Unknown';
  $handler->display->display_options['fields']['field_period_of_change']['settings'] = array(
    'format_type' => 'month_day_year',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Change Area */
  $handler->display->display_options['fields']['field_change_area']['id'] = 'field_change_area';
  $handler->display->display_options['fields']['field_change_area']['table'] = 'field_data_field_change_area';
  $handler->display->display_options['fields']['field_change_area']['field'] = 'field_change_area';
  $handler->display->display_options['fields']['field_change_area']['label'] = 'Change Area (Acres)';
  $handler->display->display_options['fields']['field_change_area']['settings'] = array(
    'thousand_separator' => ',',
    'decimal_separator' => '.',
    'scale' => '0',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Percent Changed */
  $handler->display->display_options['fields']['field_percent_changed']['id'] = 'field_percent_changed';
  $handler->display->display_options['fields']['field_percent_changed']['table'] = 'field_data_field_percent_changed';
  $handler->display->display_options['fields']['field_percent_changed']['field'] = 'field_percent_changed';
  $handler->display->display_options['fields']['field_percent_changed']['label'] = 'Percent of AOI with Changed Detected';
  $handler->display->display_options['fields']['field_percent_changed']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_percent_changed']['settings'] = array(
    'thousand_separator' => '',
    'decimal_separator' => '.',
    'scale' => '0',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Smallest Patch */
  $handler->display->display_options['fields']['field_smallest_patch']['id'] = 'field_smallest_patch';
  $handler->display->display_options['fields']['field_smallest_patch']['table'] = 'field_data_field_smallest_patch';
  $handler->display->display_options['fields']['field_smallest_patch']['field'] = 'field_smallest_patch';
  $handler->display->display_options['fields']['field_smallest_patch']['label'] = 'Smallest Forest Change Patch Size (Acres)';
  $handler->display->display_options['fields']['field_smallest_patch']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_smallest_patch']['settings'] = array(
    'thousand_separator' => ',',
    'decimal_separator' => '.',
    'scale' => '0',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Largest Patch */
  $handler->display->display_options['fields']['field_largest_patch']['id'] = 'field_largest_patch';
  $handler->display->display_options['fields']['field_largest_patch']['table'] = 'field_data_field_largest_patch';
  $handler->display->display_options['fields']['field_largest_patch']['field'] = 'field_largest_patch';
  $handler->display->display_options['fields']['field_largest_patch']['label'] = 'Largest Forest Change Patch Size (Acres)';
  $handler->display->display_options['fields']['field_largest_patch']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_largest_patch']['settings'] = array(
    'thousand_separator' => ',',
    'decimal_separator' => '.',
    'scale' => '0',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Patch Indicator */
  $handler->display->display_options['fields']['field_patch_indicator']['id'] = 'field_patch_indicator';
  $handler->display->display_options['fields']['field_patch_indicator']['table'] = 'field_data_field_patch_indicator';
  $handler->display->display_options['fields']['field_patch_indicator']['field'] = 'field_patch_indicator';
  $handler->display->display_options['fields']['field_patch_indicator']['label'] = 'Forest Change Patch Indicator';
  $handler->display->display_options['fields']['field_patch_indicator']['element_label_colon'] = FALSE;
  /* Field: Content: Layer Link */
  $handler->display->display_options['fields']['field_layer_link']['id'] = 'field_layer_link';
  $handler->display->display_options['fields']['field_layer_link']['table'] = 'field_data_field_layer_link';
  $handler->display->display_options['fields']['field_layer_link']['field'] = 'field_layer_link';
  $handler->display->display_options['fields']['field_layer_link']['label'] = 'View Data';
  $handler->display->display_options['fields']['field_layer_link']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_layer_link']['alter']['text'] = '<button class="btn-aoi-notification-layer" data-layer="[field_layer_link-url]">Load Data into Map</button>';
  $handler->display->display_options['fields']['field_layer_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_layer_link']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_layer_link']['type'] = 'link_url';
  /* Field: Content: Download Link */
  $handler->display->display_options['fields']['field_url']['id'] = 'field_url';
  $handler->display->display_options['fields']['field_url']['table'] = 'field_data_field_url';
  $handler->display->display_options['fields']['field_url']['field'] = 'field_url';
  $handler->display->display_options['fields']['field_url']['label'] = 'Download';
  $handler->display->display_options['fields']['field_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_url']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_url']['type'] = 'link_url';
  /* Sort criterion: Content: Period of Change (field_period_of_change:value2) */
  $handler->display->display_options['sorts']['field_period_of_change_value2']['id'] = 'field_period_of_change_value2';
  $handler->display->display_options['sorts']['field_period_of_change_value2']['table'] = 'field_data_field_period_of_change';
  $handler->display->display_options['sorts']['field_period_of_change_value2']['field'] = 'field_period_of_change_value2';
  $handler->display->display_options['sorts']['field_period_of_change_value2']['order'] = 'DESC';
  $handler->display->display_options['sorts']['field_period_of_change_value2']['expose']['label'] = 'Period of Change (field_period_of_change:value2)';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_parent_aoi_target_id';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'aoi_notification' => 'aoi_notification',
  );

  /* Display: AOI Notification Table */
  $handler = $view->new_display('block', 'AOI Notification Table', 'block');
  $handler->display->display_options['display_description'] = 'Table of AOI Notifications, used on the AOI landing page';
  $export['aoi_notification_table'] = $view;

  $view = new view();
  $view->name = 'public_aoi_listing';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Public AOI listing';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'All Areas of Interest';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area_1']['id'] = 'area_1';
  $handler->display->display_options['header']['area_1']['table'] = 'views';
  $handler->display->display_options['header']['area_1']['field'] = 'area';
  $handler->display->display_options['header']['area_1']['label'] = 'Header Tabs';
  $handler->display->display_options['header']['area_1']['empty'] = TRUE;
  $handler->display->display_options['header']['area_1']['content'] = '<p class="header-tab-wrapper"><a href="/aoi" class="aoi-browse-view header-tab">Your Areas of Interest</a><a href="/aoi-all" class="aoi-browse-view header-tab header-tab-active">All Areas of Interest</a></p>';
  $handler->display->display_options['header']['area_1']['format'] = 'lsf_html';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['label'] = 'Add AOI Link sections';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<a href="/node/add/aoi" class="aoi-add-view aoi-button">+ Add new Area of Interest</a>';
  $handler->display->display_options['header']['area']['format'] = 'lsf_html';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_parent_aoi_node']['id'] = 'reverse_field_parent_aoi_node';
  $handler->display->display_options['relationships']['reverse_field_parent_aoi_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_parent_aoi_node']['field'] = 'reverse_field_parent_aoi_node';
  $handler->display->display_options['relationships']['reverse_field_parent_aoi_node']['label'] = 'Notification: Content referencing Content from field_parent_aoi';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Date Detected */
  $handler->display->display_options['fields']['field_date_detected']['id'] = 'field_date_detected';
  $handler->display->display_options['fields']['field_date_detected']['table'] = 'field_data_field_date_detected';
  $handler->display->display_options['fields']['field_date_detected']['field'] = 'field_date_detected';
  $handler->display->display_options['fields']['field_date_detected']['relationship'] = 'reverse_field_parent_aoi_node';
  $handler->display->display_options['fields']['field_date_detected']['label'] = 'Last Change Detected';
  $handler->display->display_options['fields']['field_date_detected']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date_detected']['empty'] = 'No Change Products have been generated for this area';
  $handler->display->display_options['fields']['field_date_detected']['settings'] = array(
    'format_type' => 'month_day_year',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: AOI Area (acres) */
  $handler->display->display_options['fields']['field_aoi_area_acres']['id'] = 'field_aoi_area_acres';
  $handler->display->display_options['fields']['field_aoi_area_acres']['table'] = 'field_data_field_aoi_area_acres';
  $handler->display->display_options['fields']['field_aoi_area_acres']['field'] = 'field_aoi_area_acres';
  $handler->display->display_options['fields']['field_aoi_area_acres']['label'] = 'Area (acres)';
  $handler->display->display_options['fields']['field_aoi_area_acres']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_aoi_area_acres']['settings'] = array(
    'thousand_separator' => ',',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Content: AOI Subscribe Button */
  $handler->display->display_options['fields']['field_aoi_subscribe_button']['id'] = 'field_aoi_subscribe_button';
  $handler->display->display_options['fields']['field_aoi_subscribe_button']['table'] = 'field_data_field_aoi_subscribe_button';
  $handler->display->display_options['fields']['field_aoi_subscribe_button']['field'] = 'field_aoi_subscribe_button';
  $handler->display->display_options['fields']['field_aoi_subscribe_button']['label'] = 'Subscribe';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Sort criterion: Content: Date Detected (field_date_detected) */
  $handler->display->display_options['sorts']['field_date_detected_value']['id'] = 'field_date_detected_value';
  $handler->display->display_options['sorts']['field_date_detected_value']['table'] = 'field_data_field_date_detected';
  $handler->display->display_options['sorts']['field_date_detected_value']['field'] = 'field_date_detected_value';
  $handler->display->display_options['sorts']['field_date_detected_value']['relationship'] = 'reverse_field_parent_aoi_node';
  $handler->display->display_options['sorts']['field_date_detected_value']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'aoi' => 'aoi',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'aoi-all';
  $export['public_aoi_listing'] = $view;

  $view = new view();
  $view->name = 'user_aoi_listing';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'User AOI Listing';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Your Areas of Interest';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area_1']['id'] = 'area_1';
  $handler->display->display_options['header']['area_1']['table'] = 'views';
  $handler->display->display_options['header']['area_1']['field'] = 'area';
  $handler->display->display_options['header']['area_1']['label'] = 'Header Tabs';
  $handler->display->display_options['header']['area_1']['empty'] = TRUE;
  $handler->display->display_options['header']['area_1']['content'] = '<p class="header-tab-wrapper"><a href="/aoi" class="aoi-browse-view header-tab header-tab-active">Your Areas of Interest</a><a href="/aoi-all" class="aoi-browse-view header-tab">All Areas of Interest</a></p>';
  $handler->display->display_options['header']['area_1']['format'] = 'lsf_html';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['label'] = 'Add AOI Link sections';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<a href="/node/add/aoi" class="aoi-add-view aoi-button add-new-aoi-button">+ Add new Area of Interest</a>';
  $handler->display->display_options['header']['area']['format'] = 'lsf_html';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No Results Message';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'It looks like you have not specified any Areas of Interest you would like to receive notifications from when new change products are generated for them. You can either <a href="/aoi-all" class="aoi-all-no-results-link">browse existing Areas of Interest</a> or <a href="/node/add/aoi" class="aoi-add-no-results-link">create one</a>.';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_parent_aoi_target_id']['id'] = 'field_parent_aoi_target_id';
  $handler->display->display_options['relationships']['field_parent_aoi_target_id']['table'] = 'field_data_field_parent_aoi';
  $handler->display->display_options['relationships']['field_parent_aoi_target_id']['field'] = 'field_parent_aoi_target_id';
  $handler->display->display_options['relationships']['field_parent_aoi_target_id']['label'] = 'AOIs - Content entity referenced from field_parent_aoi';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_parent_aoi_node']['id'] = 'reverse_field_parent_aoi_node';
  $handler->display->display_options['relationships']['reverse_field_parent_aoi_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_parent_aoi_node']['field'] = 'reverse_field_parent_aoi_node';
  $handler->display->display_options['relationships']['reverse_field_parent_aoi_node']['relationship'] = 'field_parent_aoi_target_id';
  $handler->display->display_options['relationships']['reverse_field_parent_aoi_node']['label'] = 'Notification: Content referencing Content from field_parent_aoi';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_parent_aoi_target_id';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Date Detected */
  $handler->display->display_options['fields']['field_date_detected']['id'] = 'field_date_detected';
  $handler->display->display_options['fields']['field_date_detected']['table'] = 'field_data_field_date_detected';
  $handler->display->display_options['fields']['field_date_detected']['field'] = 'field_date_detected';
  $handler->display->display_options['fields']['field_date_detected']['relationship'] = 'reverse_field_parent_aoi_node';
  $handler->display->display_options['fields']['field_date_detected']['label'] = 'Last Change Detected';
  $handler->display->display_options['fields']['field_date_detected']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date_detected']['empty'] = 'No Change Products have been generated for this area';
  $handler->display->display_options['fields']['field_date_detected']['settings'] = array(
    'format_type' => 'month_day_year',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: AOI Area (acres) */
  $handler->display->display_options['fields']['field_aoi_area_acres']['id'] = 'field_aoi_area_acres';
  $handler->display->display_options['fields']['field_aoi_area_acres']['table'] = 'field_data_field_aoi_area_acres';
  $handler->display->display_options['fields']['field_aoi_area_acres']['field'] = 'field_aoi_area_acres';
  $handler->display->display_options['fields']['field_aoi_area_acres']['relationship'] = 'field_parent_aoi_target_id';
  $handler->display->display_options['fields']['field_aoi_area_acres']['label'] = 'Area (acres)';
  $handler->display->display_options['fields']['field_aoi_area_acres']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_aoi_area_acres']['settings'] = array(
    'thousand_separator' => ',',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Content: AOI Subscribe Button */
  $handler->display->display_options['fields']['field_aoi_subscribe_button']['id'] = 'field_aoi_subscribe_button';
  $handler->display->display_options['fields']['field_aoi_subscribe_button']['table'] = 'field_data_field_aoi_subscribe_button';
  $handler->display->display_options['fields']['field_aoi_subscribe_button']['field'] = 'field_aoi_subscribe_button';
  $handler->display->display_options['fields']['field_aoi_subscribe_button']['relationship'] = 'field_parent_aoi_target_id';
  $handler->display->display_options['fields']['field_aoi_subscribe_button']['label'] = 'Subscribe';
  $handler->display->display_options['fields']['field_aoi_subscribe_button']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Sort criterion: Content: Date Detected (field_date_detected) */
  $handler->display->display_options['sorts']['field_date_detected_value']['id'] = 'field_date_detected_value';
  $handler->display->display_options['sorts']['field_date_detected_value']['table'] = 'field_data_field_date_detected';
  $handler->display->display_options['sorts']['field_date_detected_value']['field'] = 'field_date_detected_value';
  $handler->display->display_options['sorts']['field_date_detected_value']['relationship'] = 'reverse_field_parent_aoi_node';
  $handler->display->display_options['sorts']['field_date_detected_value']['order'] = 'DESC';
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'aoi_subscription' => 'aoi_subscription',
  );
  /* Filter criterion: Content: Author uid */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'node';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';

  /* Display: User AOI's */
  $handler = $view->new_display('page', 'User AOI\'s', 'page');
  $handler->display->display_options['path'] = 'aoi';
  $export['user_aoi_listing'] = $view;

  $view = new view();
  $view->name = 'user_areas_of_interest';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'User areas of interest';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Notifications';
  $handler->display->display_options['css_class'] = 'user-add-aoi';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'edit_node' => 'edit_node',
    'delete_node' => 'delete_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => 'views-align-right',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => 'views-align-right',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '  [title] ';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['text'] = 'Edit';
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = '';
  $handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['delete_node']['text'] = 'Unsubscribe';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'user';
  $handler->display->display_options['arguments']['uid']['default_argument_options']['user'] = FALSE;
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['uid']['validate']['type'] = 'user';
  $handler->display->display_options['arguments']['uid']['validate_options']['type'] = 'either';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'subscription' => 'subscription',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['user_areas_of_interest'] = $view;

  return $export;
}
