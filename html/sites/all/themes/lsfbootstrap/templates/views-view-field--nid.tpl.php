<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */

     if ($view->name === 'custom_request_status') {
         $node_id = $row->{$view->field['nid']->field_alias};
         $drupalUser = $row->{$view->field['name']->field_alias};
         $postDate = $row->{$view->field['changed']->field_alias};

         $config_info = parse_ini_file(DRUPAL_ROOT . '/../lsf_config.ini', true);
         $username = $config_info['pgsql_connection']['username'];
         $password = $config_info['pgsql_connection']['password'];
         $host = $config_info['pgsql_connection']['host'];
         $port = $config_info['pgsql_connection']['port'];
         $driver = $config_info['pgsql_connection']['driver'];
         $database = $config_info['pgsql_connection']['database'];
         $lsf_database = array(
             'database' => $database,
             'username' => $username,
             'password' => $password,
             'host' => $host,
             'port' => $port,
             'driver' => $driver,
         );

         Database::addConnectionInfo($database, 'default', $lsf_database);
         db_set_active($database);

         //get the aoi_id for the Custom Request 
         //   the download files uses the aoi_id in the file name. which is in postgres database
         //   retrieve to concat the URL
         $result = db_query('select * from get_aoi_id_by_nodeid(:nid)',
                            array(
                                ':nid' => $node_id,
                            ));   
     
         $aoi_id = 0;

         //retreive aoi_id from results
         foreach($result as $item) {
             $aoi_id = $item->get_aoi_id_by_nodeid;
             break;
         }

         if (strlen($aoi_id) > 0){
             $message = $aoi_id;
         } else {
             $message = 'Not Available';
         }

         db_set_active();

         //$output replaces field with our custom message
         $output = $message;
     }

?>
<?php /* dpm( current( (Array)$view->field) );*/   ?>
<?php  print $output; ?>
