<?php
/**
 * @file
 * southfact_aoi.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function southfact_aoi_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|aoi|aoi_notification';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'aoi';
  $ds_fieldsetting->view_mode = 'aoi_notification';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'inline',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '1',
        'wrapper' => '',
        'class' => '',
      ),
    ),
  );
  $export['node|aoi|aoi_notification'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|aoi|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'aoi';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'add_subscription' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'aoi_notification_table' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'title' => array(
      'weight' => '1',
      'label' => 'inline',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '0',
        'wrapper' => '',
        'class' => '',
      ),
    ),
  );
  $export['node|aoi|full'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function southfact_aoi_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'add_subscription';
  $ds_field->label = 'Add Subscription';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'aoi|full';
  $ds_field->properties = array(
    'block' => 'subscriptions_ui|0',
    'block_render' => '3',
  );
  $export['add_subscription'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'aoi_notification_table';
  $ds_field->label = 'AOI Notification Table';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'aoi|full';
  $ds_field->properties = array(
    'block' => 'views|aoi_notification_table-block',
    'block_render' => '3',
  );
  $export['aoi_notification_table'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function southfact_aoi_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|aoi_notification|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'aoi_notification';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_parent_aoi',
        1 => 'field_period_of_change',
        2 => 'group_aoi_notification_metadata',
        3 => 'field_change_area',
        4 => 'field_percent_changed',
        5 => 'field_smallest_patch',
        6 => 'field_largest_patch',
        7 => 'field_patch_indicator',
        8 => 'field_url',
      ),
    ),
    'fields' => array(
      'field_parent_aoi' => 'ds_content',
      'field_period_of_change' => 'ds_content',
      'group_aoi_notification_metadata' => 'ds_content',
      'field_change_area' => 'ds_content',
      'field_percent_changed' => 'ds_content',
      'field_smallest_patch' => 'ds_content',
      'field_largest_patch' => 'ds_content',
      'field_patch_indicator' => 'ds_content',
      'field_url' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|aoi_notification|full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|aoi|aoi_notification';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'aoi';
  $ds_layout->view_mode = 'aoi_notification';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'group_aoi_notification_header',
        1 => 'title',
        2 => 'field_aoi_area_acres',
        3 => 'field_area_geojson',
      ),
    ),
    'fields' => array(
      'group_aoi_notification_header' => 'ds_content',
      'title' => 'ds_content',
      'field_aoi_area_acres' => 'ds_content',
      'field_area_geojson' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|aoi|aoi_notification'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|aoi|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'aoi';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'group_aoi_notification_header',
        1 => 'add_subscription',
        2 => 'title',
        3 => 'field_aoi_area_acres',
        4 => 'field_area_geojson',
        5 => 'body',
        6 => 'aoi_notification_table',
      ),
    ),
    'fields' => array(
      'group_aoi_notification_header' => 'ds_content',
      'add_subscription' => 'ds_content',
      'title' => 'ds_content',
      'field_aoi_area_acres' => 'ds_content',
      'field_area_geojson' => 'ds_content',
      'body' => 'ds_content',
      'aoi_notification_table' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|aoi|full'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function southfact_aoi_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'aoi_notification';
  $ds_view_mode->label = 'AOI Notification';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['aoi_notification'] = $ds_view_mode;

  return $export;
}
