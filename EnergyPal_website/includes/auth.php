<?php
    // make sure the script is running as module
	if(__FILE__ === realpath($_SERVER['SCRIPT_FILENAME'])){
		return;
	}

    require_once(__DIR__ . '/../config.php'); // require config file

    // check if user is logged
    function isUserLogged(){
        session_start();
        if(isset($_SESSION['userID'])){
            session_write_close();
            return true;
        } else {
            session_write_close();
            return false;
        }
    }

    function checkUserLogged(){
        if(isUserLogged()){
            return true;
        } else {
            header('Location:' . LOGIN_URL);
            return false;
        }
    }

    function logout(){
        session_start();
        session_destroy();
        header('Location:' . LOGIN_URL);
        exit;
    }
?>
