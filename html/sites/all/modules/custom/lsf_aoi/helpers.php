<?php


function _lsf_aoi_build_node_url_alias_by_nid($nid, $query_string_params=false) {
  global $base_url;
  $url = $base_url . url('node/'.$nid);
  if ($query_string_params) {
    $url .= '?';
    foreach ($query_string_params as $key => $value) {
      $url .= $key . '=' . $value . '&';
    }
  }
  return $url;
}