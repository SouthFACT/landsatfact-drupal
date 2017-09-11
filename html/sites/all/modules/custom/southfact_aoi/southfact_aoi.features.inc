<?php
/**
 * @file
 * southfact_aoi.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function southfact_aoi_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function southfact_aoi_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function southfact_aoi_node_info() {
  $items = array(
    'aoi' => array(
      'name' => t('AOI'),
      'base' => 'node_content',
      'description' => t('Notification system for an area of interest'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'aoi_notification' => array(
      'name' => t('AOI notification'),
      'base' => 'node_content',
      'description' => t('Autogenerating content type that will be created when an AOI has enough changes to trigger creation'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'aoi_subscription' => array(
      'name' => t('AOI Subscription'),
      'base' => 'node_content',
      'description' => t('Manages a user\'s subscription to an AOI'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
