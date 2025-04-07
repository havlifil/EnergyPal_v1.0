<?php
    require_once('includes/db.php');

    $email = 'havlifil@gmail.com';
    $password = 'hesloheslo';
    $rights = 1;

    $passwordHash = password_hash($password, PASSWORD_DEFAULT);

    $result = executeSql($users_db, 'INSERT INTO users (email, password_hash, rights) VALUES (:email, :password_hash, :rights)', [
        ':email' => $email,
        ':password_hash' => $passwordHash,
        ':rights' => $rights
    ]);
    if($result['success'] === true){
        echo 'Successfully added user!';
    } else {
        echo 'Failed to add user!';
    }
?>