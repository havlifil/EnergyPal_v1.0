<?php
    header("Cache-Control: no-cache");
    header("X-Content-Type-Options: nosniff");
    header("Content-Type: application/json");
    header("Charset: UTF-8");

    require_once('../../includes/db.php');

    $unixFrom = null;
    $unixTo = null;

    if(isset($_GET['from'])){
        $unixFrom = $_GET['from'];
    }
    if(isset($_GET['to'])){
        $unixTo = $_GET['to'];
    }

    if(!is_null($unixFrom) and !empty($unixFrom) and !is_null($unixTo) and !empty($unixTo)){
        $result = executeSql($energypal_db, "SELECT measurement_datetime, temp1, temp2, temp3, temp4, temp5, temp6 FROM measurements WHERE measurement_unixtime BETWEEN :unixFrom AND :unixTo;",[
            ":unixFrom" => $unixFrom,
            ":unixTo" => $unixTo
        ]);
        if($result['success'] and $result['resultExists']){
            $data['success'] = true;
            $data['data'] = $result['result'];
            echo json_encode($data);
        } else {
            $data['success'] = false;
            $data['data'] = null;
            echo json_encode($data);
        }
    } else {
        $data['success'] = false;
        $data['data'] = null;
        echo json_encode($data);
    }
?>