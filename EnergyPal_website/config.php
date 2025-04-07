<?php
    // make sure the script is running as module
	if(__FILE__ === realpath($_SERVER['SCRIPT_FILENAME']))
	{
		return;
	}

	// define DIRs
    define("LOG_FILE_DIR", __DIR__ . '/logs/log.txt');

	// define URLs
	define('LOGIN_URL', 'http://'. $_SERVER['HTTP_HOST'] . '/login');
?>