<?php
    header("Cache-Control: no-cache");
    header("X-Content-Type-Options: nosniff");
    header("Content-Type: application/json");
    header("Charset: UTF-8");

    require_once('../../includes/db.php');

    $result = executeSql($energypal_db, "SELECT states_unixtime, OUT_1, OUT_2, OUT_3, OUT_4, IN_1, IN_2, IN_3, IN_4, IN_5, IN_6 FROM states ORDER BY states_unixtime DESC LIMIT 1;");
    if($result['success'] and $result['resultExists']){
        $data['success'] = true;
        $data['data'] = $result['result'][0];
        echo json_encode($data);
    } else {
        $data['success'] = false;
        $data['data'] = null;
        echo json_encode($data);
    }
?>