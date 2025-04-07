<?php
    require_once("../../includes/db.php");

    $unixtime = null;
    $datetimeString = null;
    $in[6] = [null, null, null, null, null, null];
    $out[4] = [null, null, null, null];

    $payload = file_get_contents("php://input");
    $decodedPayload = json_decode($payload, true);

    // extract data from each measuremnt in the payload and INSERTS them into DB
    foreach($decodedPayload as $states){
        if(isset($states['timestamp'])){
            $unixtime = intval($states['timestamp'], 10);
            $datetimeString = gmdate("Y-m-d H:i:s", $unixtime);
        }
        // get INPUT states
        for($i = 0; $i < 6; $i++){
            $key = "IN_" . ($i+1);
            if(isset($states[$key])){
                $in[$i] = $states[$key];
            }
        }
        // get OUTPUT states
        for($i = 0; $i < 4; $i++){
            $key = "OUT_" . ($i+1);
            if(isset($states[$key])){
                $out[$i] = $states[$key];
            }
        }

        $success = executeSql($energypal_db, "INSERT INTO states (states_datetime, states_unixtime, IN_1, IN_2, IN_3, IN_4, IN_5, IN_6, OUT_1, OUT_2, OUT_3, OUT_4) VALUES (:measurement_datetime, :measurement_unixtime, :IN_1, :IN_2, :IN_3, :IN_4, :IN_5, :IN_6, :OUT_1, :OUT_2, :OUT_3, :OUT_4)", [
            ":measurement_datetime"=>$datetimeString,
            ":measurement_unixtime"=>$unixtime,
            ":IN_1"=>$in[0],
            ":IN_2"=>$in[1],
            ":IN_3"=>$in[2],
            ":IN_4"=>$in[3],
            ":IN_5"=>$in[4],
            ":IN_6"=>$in[5],
            ":OUT_1"=>$out[0],
            ":OUT_2"=>$out[1],
            ":OUT_3"=>$out[2],
            ":OUT_4"=>$out[3]
        ]);

        if($success){
            echo "Data successfully received!";
        } else {
            echo "Failed to receive data!";
        }
    }
?>