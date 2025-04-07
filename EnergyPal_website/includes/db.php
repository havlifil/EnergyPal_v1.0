<?php
	// make sure the script is running as module
	if(__FILE__ === realpath($_SERVER['SCRIPT_FILENAME'])){
		return;
	}

    // require config file
    require_once(__DIR__ . '/../config.php');

    // require DB creadentials file
    require_once('db_credentials.php');

	// energypal DB connection information
    $energypal_dbName = DB_NAME_ENERGYPAL;
    $energypal_dbUser = DB_USER_ENERGYPAL;
    $energypal_dbPassword = DB_PASSWORD_ENERGYPAL;
    $energypal_dbHost = DB_HOST_ENERGYPAL;

    // users DB connection information
    $users_dbName = DB_NAME_USERS;
    $users_dbUser = DB_USER_USERS;
    $users_dbPassword = DB_PASSWORD_USERS;
    $users_dbHost = DB_HOST_USERS;

    // establish DB connections
    try{
        $energypal_db = new PDO(
            'mysql:host='.$energypal_dbHost.';dbname='.$energypal_dbName,$energypal_dbUser,$energypal_dbPassword,
            [
                PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
                PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
                PDO::MYSQL_ATTR_INIT_COMMAND => 'SET NAMES utf8'
            ]
        );
        $users_db = new PDO(
            'mysql:host='.$users_dbHost.';dbname='.$users_dbName,$users_dbUser,$users_dbPassword,
            [
                PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
                PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
                PDO::MYSQL_ATTR_INIT_COMMAND => 'SET NAMES utf8'
            ]
        );
    } catch(PDOException $e) {
        error_log(date("Y-m-d H:i:s") . " [DB] Connection failed: " . $e->getMessage() . PHP_EOL, 3, LOG_FILE_DIR);
    }

    // execute SQL query
    function executeSql($db, $sql, $data = []){
        try {
            // prepare SQL query
            $statement = $db->prepare($sql);
            // exectue SQL query
            $success = $statement->execute($data);
            // get result
            $result = $statement->fetchAll();
            // check if result exist
            $resultExists = !empty($result);
            // return result
            return['success' => $success, 'result' => $result, 'resultExists' => $resultExists];
        } catch(PDOException $e){
            error_log(date("Y-m-d H:i:s") . " [DB] SQL query execution failed: " . $e->getMessage() . PHP_EOL, 3, LOG_FILE);
            return['success' => false, 'result' => [], 'resultExists' => false, 'error' => $e->getMessage()];
        }
    }
?>