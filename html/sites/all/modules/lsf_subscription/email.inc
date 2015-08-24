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
           -> fields('un', array('user_id', 'quad_id'));
    $results = $query->execute()->fetchAll();
    print_r($results);
    _lsf_subscription_reset_database_connection();
}

_lsf_subscription_add_comment_to_user(3);
//_lsf_subscription_get_user_notification_records();
