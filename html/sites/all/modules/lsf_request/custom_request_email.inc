#!/usr/bin/env drush

require_once drupal_get_path('module', 'user_profile_comments') . '/user_profile_comments.module';

/**
 * Generates an object formatted to be a comment.
 *
 * @param integer $nid id of node attached to user
 * @param string $subject
 * @param string $body
 * @return object New comment to attach to user
 */
function _lsf_subscription_generate_comment($uid, $nid, $subject, $body) {
    $comment = new stdClass();
    $comment->nid = $nid;
    $comment->cid = 0;
    $comment->pid = 0;
    $comment->uid;
    $comment->mail = 'info@landsatfact.com';
    $comment->created = time();
    $comment->is_anonymous = 0;
    $comment->homepage = '';
    $comment->status = COMMENT_PUBLISHED;
    $comment->language = LANGUAGE_NONE;
    $comment->subject = $subject; 
    $comment->comment_body[$comment->language][0]['value'] = $body;
    $comment->comment_body[$comment->language][0]['format'] = 'filtered_html'; 
    return $comment;
}

/**
 * Appends a comment to a user to generate a notification email.
 *
 * @param integer $uid id of user to append a comment to
 */
function _lsf_subscription_add_comment_to_user($uid) {
    $nid = user_profile_comments_get_profile_entity($uid)->nid;
    $subject = 'Test subject for auto sending email';
    $body = 'Test body for auto sending email';
    
    $comment = _lsf_subscription_generate_comment($nid, $subject, $body);
    comment_submit($comment);
    comment_save($comment);
}

/**
 * Initializes a connection to the remote postgres database.
 */
/*
function _lsf_subscription_set_database_connection() {
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
}
*/

/**
 * Resets database connection to drupal database.
 */
function _lsf_subscription_reset_database_connection() {
    db_set_active();
}

/**
 * Gets metadata for all users that have an aoi with new data for this day.
 */
function _lsf_subscription_get_user_notification_records() {
    $table_name = 'test_vw_user_notification';

    _lsf_subscription_set_database_connection();
    $query = db_select($table_name, 'un')
           -> fields('un', array('user_id', 'lsf_url','node_id','aoi_name'));

    //get records
    $results = $query->execute()->fetchAll();


    _lsf_subscription_reset_database_connection();
    return $results;
}

/**
 * Gets metadata for all users that have an CR where the status is processing complete - ready for email
 */
function _lsf_custom_request_get_user_notification_records() {

    _lsf_subscription_set_database_connection();
    $results = db_query("SELECT * FROM get_processcompletecustomrequests()");
    db_set_active();
    return $results;

}

function _lsf_custom_request_update_status($aoi_id) {

    _lsf_subscription_set_database_connection();
    $results = db_query("SELECT * FROM update_custom_request_status('$aoi_id', 4)");
    db_set_active();
    return $results;

}

/**
* Gets the zip file (request_id) of a specific custom request (aoi_id)
 * @param string $aoi_id
 * @return object request_id which is the file.
*/
function _lsf_custom_request_get_request_id($aoi_id) {
  $table_name = 'custom_requests'; 
  
   //setup db connection 
   _lsf_subscription_set_database_connection();

  //setup; query for getting zip file (request id) 
  $query = db_select($table_name, 'un')
      -> condition('aoi_id', $aoi_id,'=')
      -> groupBy('un.request_id')
      -> fields('un', array('request_id'));
  
   //get all records
   $results = $query->execute()->fetchAll();

   //reset db connection to Drupal DB
   _lsf_subscription_reset_database_connection();

  //return zip file
   return $results;

}

/**
* prepares and sends the custom request email
 * 
*/
function _lsf_make_custom_request_email(){
  //get all users with a custom request set as processing complete - which means it's ready to be sent via email
  $customRequests = _lsf_custom_request_get_user_notification_records();

  //loop all users and gather info for custom request email
  foreach ($customRequests as $request){

      //get field values for CR
      $user_id = $request->user_id;
      $status = $request->status;
      $node_id = $request->node_id;
      $aoi_name = $request->aoi_name;
      $aoi_id = $request->aoi_id;

      //get the zip file contain all products for the CR
      $request_id = _lsf_custom_request_get_request_id($aoi_id);
      foreach ($request_id as $r){
          $req = $r->request_id;
          // print_r($req . PHP_EOL);
      }

      //create email subject 
      $subject = 'SouthFACT custom request complete. (' . $node_id .')';

      // add 3 days to date
      $expireDate=Date('l, F jS, Y', strtotime("+45 days"));
     
      //creare email body - link to file on s3
      $body = 'Download your custom request data here:  https://s3.amazonaws.com/landsat-cr-products/' . $req . PHP_EOL . 'Please note that this data link will expire on ' . $expireDate . '.';
      $comment = _lsf_subscription_generate_comment($user_id, $node_id,$subject, $body);

      //send CR email
      comment_submit($comment);
      comment_save($comment);
      _lsf_custom_request_update_status($aoi_id);
  }
  
}

//call CR
_lsf_make_custom_request_email();
