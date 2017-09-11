<?php
/**
 * @file
 * southfact_aoi.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function southfact_aoi_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_aoi_config|node|aoi|form';
  $field_group->group_name = 'group_aoi_config';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'aoi';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Choose How You Want Your Area of Interest to be Configured',
    'weight' => '3',
    'children' => array(
      0 => 'field_receive_email_notifcations',
      1 => 'field_public',
      2 => 'field_generate_zonal_stats',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-aoi-config field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_aoi_config|node|aoi|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_aoi_location|node|aoi|form';
  $field_group->group_name = 'group_aoi_location';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'aoi';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Select the Location for Your Area of Interest',
    'weight' => '2',
    'children' => array(
      0 => 'field_area_geojson',
      1 => 'field_custom_area',
      2 => 'field_area_type',
      3 => 'field_area_shapefile',
      4 => 'field_state',
      5 => 'field_al_counties',
      6 => 'field_ar_counties',
      7 => 'field_fl_counties',
      8 => 'field_ga_counties',
      9 => 'field_ky_counties',
      10 => 'field_nc_counties',
      11 => 'field_ok_counties',
      12 => 'field_tx_counties',
      13 => 'field_sc_counties',
      14 => 'field_la_counties',
      15 => 'field_tn_counties',
      16 => 'field_va_counties',
      17 => 'field_ms_counties',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Select the Location for Your Area of Interest',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'group-aoi-location field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_aoi_location|node|aoi|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_aoi_notification_header|node|aoi|aoi_notification';
  $field_group->group_name = 'group_aoi_notification_header';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'aoi';
  $field_group->mode = 'aoi_notification';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '0',
    'children' => array(
      0 => 'field_aoi_area_acres',
      1 => 'title',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => '',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-aoi-notification-header',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_aoi_notification_header|node|aoi|aoi_notification'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_aoi_notification_header|node|aoi|full';
  $field_group->group_name = 'group_aoi_notification_header';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'aoi';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '0',
    'children' => array(
      0 => 'field_aoi_area_acres',
      1 => 'title',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => '',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-aoi-notification-header',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_aoi_notification_header|node|aoi|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_aoi_notification_metadata|node|aoi_notification|full';
  $field_group->group_name = 'group_aoi_notification_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'aoi_notification';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '1',
    'children' => array(
      0 => 'field_percent_changed',
      1 => 'field_smallest_patch',
      2 => 'field_largest_patch',
      3 => 'field_patch_indicator',
      4 => 'field_url',
      5 => 'field_change_area',
      6 => 'field_period_of_change',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => '',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-aoi-notification-metadata',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_aoi_notification_metadata|node|aoi_notification|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_aoi_title|node|aoi|form';
  $field_group->group_name = 'group_aoi_title';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'aoi';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Select a Name for Your Area of Interest',
    'weight' => '0',
    'children' => array(
      0 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Select a Name for Your Area of Interest',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'group-aoi-title field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_aoi_title|node|aoi|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Choose How You Want Your Area of Interest to be Configured');
  t('Select a Name for Your Area of Interest');
  t('Select the Location for Your Area of Interest');

  return $field_groups;
}
