<?php
    header("Cache-Control: no-cache");
    header("X-Content-Type-Options: nosniff");
    header("Content-Type: application/json");
    header("Charset: UTF-8");

    require_once('../../includes/db.php');

    $result = executeSql($energypal_db, "SELECT measurement_datetime ,measurement_unixtime, temp1, temp2, temp3, temp4, temp5, temp6 FROM measurements ORDER BY measurement_unixtime DESC LIMIT 1;");
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