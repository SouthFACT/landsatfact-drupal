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
function _lsf_subscription_generate_comment($nid, $subject, $body) {
    $comment = new stdClass();
    $comment->nid = $nid;
    $comment->cid = 0;
    $comment->pid = 0;
    $comment->uid = 1;
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
*function to get each user that has a valid subscription
*/
function _lsf_subscription_get_users(){
  $table_name = 'vw_user_notification'; 
  
   _lsf_subscription_set_database_connection(); 
  $query = db_select($table_name, 'un')
     ->groupBy('un.user_id')
      -> fields('un', array('user_id'));
   
   $results = $query->execute()->fetchAll();

   _lsf_subscription_reset_database_connection();
   return $results;
  
}

/**
 * Gets metadata for all users that have an aoi with new data for this day.
 */
function _lsf_subscription_get_user_notification_records($user_id) {
    $table_name = 'vw_user_notification';

    _lsf_subscription_set_database_connection();
    $query = db_select($table_name, 'un')
           -> condition('user_id', $user_id,'=')
           -> fields('un', array('user_id', 'lsf_url','node_id','aoi_name','product_type'));

    $results = $query->execute()->fetchAll();

    _lsf_subscription_reset_database_connection();
    return $results;
}


/*
*looks for a list of current valid subscriptions
*/
function _lsf_subscriptions_send() {
  //get the days subscritions
  //$usersWithSubscription = _lsf_subscription_get_user_notification_records();
  $usersWithSubscription = _lsf_subscription_get_users();
  $user_id = '';

  //loop each record and send there 
  //this needs to loop each user and send all users subscriptions so not quite right yet
  foreach ($usersWithSubscription as $key=>$value){
    $user_id = $value->user_id;
    
    $Subscriptions = _lsf_subscription_get_user_notification_records($user_id);
    
    foreach ($Subscriptions as $keyB=>$valueB){ 

      $lsf_url = $valueB->lsf_url;
      $node_id = $valueB->node_id;
      $aoi_name = $valueB->aoi_name;
      $product = $valueB->product_type;
      $body = $body . $aoi_name . ' for  ' . $product . '  view: ' . $lsf_url. '.' . PHP_EOL . PHP_EOL;

      //build the  custom comment.  this will trigger the email
      $nid = user_profile_comments_get_profile_entity($user_id)->nid;

      $subject =' New LandsatFACT products have been generated'; 
    }

    //generate the comment object
    $comment = _lsf_subscription_generate_comment($nid, $subject, $body);
    comment_submit($comment);
    comment_save($comment);

    $lsf_url = '';
    $node_id = 0;
    $body = '';
    $aoi_name = '';
    $subject = '';

  }

}

_lsf_subscriptions_send();
