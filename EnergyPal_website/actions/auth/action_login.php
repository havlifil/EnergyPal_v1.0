<?php
    header("Cache-Control: no-cache");
    header("X-Content-Type-Options: nosniff");
    header("Content-Type: application/json");

    require_once('../../includes/db.php');

    $email = null;
    $password = null;

    // get eamil and password
    if(isset($_POST['email'])) {
        $email = $_POST['email'];
    }
    if(isset($_POST['password'])){
        $password = $_POST['password'];
    }

    // verifie login
    if(!is_null($email) and !empty($email) and !is_null($password) and !empty($password)){
        $result = executeSql($users_db, 'SELECT ID, password_hash FROM users WHERE email = :email', [':email' => $email]);
        if($result['success']){
            if($result['resultExists']){
                $passwordHash = $result['result'][0]['password_hash'];
                $passwordCorrect = password_verify($password, $passwordHash);
                if($passwordCorrect){
                    session_start();
                    $_SESSION['userID'] = $result['result'][0]['ID'];
                    session_write_close();
                    $data['success'] = true;
                    echo json_encode($data);
                    exit;
                } else {
                    $data['success'] = false;
                    $data['error'] = 'Nesprávné heslo.';
                    echo json_encode($data);
                    exit;
                }
            } else {
                $data['success'] = false;
                $data['error'] = 'Email není registrovaný.';
                echo json_encode($data);
            exit;
            }
        } else {
            $data['success'] = false;
            $data['error'] = 'Přihlášení se nezdařilo';
            echo json_encode($data);
            exit;
        }
    } else {
        $data['success'] = false;
        $data['error'] = 'Vyplňte všechny povinné položky.';
        echo json_encode($data);
        exit;
    }
?>