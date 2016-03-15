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
  


     $node_id = $row->{$view->field['nid']->field_alias};
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

     /* if is viewname custom_request_status_all then do all view otherwise do public.get_customrequest_status_bynode */  
     if ($view->name === "custom_request_status_all") {
       $result = db_query("SELECT status || ' on ' || to_char(status_date ,'Mon DD, YYYY at HH12:MI PM')  as status  FROM public.vw_customrequets_all_status WHERE node_id = :n ORDER BY status_date desc limit 1", array(':n' => $node_id));
     } else {
       $result = db_query("SELECT status || ' on ' || to_char(status_date ,'Mon DD, YYYY at HH12:MI PM')  as status  FROM public.get_customrequest_status_bynode(:n) ORDER BY status_date desc limit 1", array(':n' => $node_id));
     }
 
     $status = 'Status is Unknown';
     
     foreach($result as $item) {
       $status = $item->status;
       break;
     }

     db_set_active();

     $output = $status;

?>
<?php /*  dpm($view); */  ?>
<?php print $output; ?>
