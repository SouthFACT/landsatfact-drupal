<?php
/**
 * @file
 * southfact_aoi.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function southfact_aoi_default_rules_configuration() {
  $items = array();
  $items['rules_aoi_subscription_email'] = entity_import('rules_config', '{ "rules_aoi_subscription_email" : {
      "LABEL" : "AOI Subscription email",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert--aoi_notification" : { "bundle" : "aoi_notification" } },
      "DO" : []
    }
  }');
  return $items;
}
