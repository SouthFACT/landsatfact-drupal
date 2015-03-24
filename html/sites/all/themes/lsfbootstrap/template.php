<?php

/**
 * @file
 * template.php
 */
/**
 * Implements hook_preprocess_region().
 */
function lsfbootstrap_preprocess_region(&$variables) {
  switch ($variables['region']) {
    case 'sub_footer':
    case 'footer':
      $variables['classes_array'][] = 'row';
      break;
  }
}
