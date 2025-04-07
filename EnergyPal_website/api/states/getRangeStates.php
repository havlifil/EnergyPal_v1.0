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
        $query = "SELECT states_datetime, IN_1, IN_2, IN_3, IN_4, IN_5, IN_6, OUT_1, OUT_2, OUT_3, OUT_4 
        FROM states 
        WHERE states_unixtime BETWEEN :unixFrom AND :unixTo
        UNION ALL
        SELECT states_datetime, IN_1, IN_2, IN_3, IN_4, IN_5, IN_6, OUT_1, OUT_2, OUT_3, OUT_4 
        FROM states 
        WHERE states_unixtime = (
            SELECT states_unixtime FROM states 
            WHERE states_unixtime < :unixFrom 
            ORDER BY states_unixtime DESC 
            LIMIT 1
        )
        UNION ALL
        SELECT states_datetime, IN_1, IN_2, IN_3, IN_4, IN_5, IN_6, OUT_1, OUT_2, OUT_3, OUT_4 
        FROM states 
        WHERE states_unixtime = (
            SELECT states_unixtime FROM states 
            WHERE states_unixtime > :unixTo 
            ORDER BY states_unixtime ASC 
            LIMIT 1
        );";
        $result = executeSql($energypal_db, $query,[
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