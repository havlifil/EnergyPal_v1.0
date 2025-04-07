<?php
    require_once("../../includes/db.php");

    $unixtime = null;
    $datetimeString = null;
    $temp1 = null;
    $temp2 = null;
    $temp3 = null;
    $temp4 = null;
    $temp5 = null;
    $temp6 = null;

    $payload = file_get_contents("php://input");
    $decodedPayload = json_decode($payload, true);

    // extract data from each measuremnt in the payload and INSERTS them into DB
    foreach($decodedPayload as $measurement){
        if(isset($measurement['timestamp'])){
            $unixtime = intval($measurement['timestamp'], 10);
            $datetimeString = gmdate("Y-m-d H:i:s", $unixtime);
        }
        if(isset($measurement['temp1'])){
            $temp1 = floatval($measurement['temp1']);
        }
        if(isset($measurement['temp2'])){
            $temp2 = floatval($measurement['temp2']);
        }
        if(isset($measurement['temp3'])){
            $temp3 = floatval($measurement['temp3']);
        }
        if(isset($measurement['temp4'])){
            $temp4 = floatval($measurement['temp4']);
        }
        if(isset($measurement['temp5'])){
            $temp5 = floatval($measurement['temp5']);
        }
        if(isset($measurement['temp6'])){
            $temp6 = floatval($measurement['temp6']);
        }

        $success = executeSql($energypal_db, "INSERT INTO measurements (measurement_datetime, measurement_unixtime, temp1, temp2, temp3, temp4, temp5, temp6) VALUES (:measurement_datetime, :measurement_unixtime, :temp1, :temp2, :temp3, :temp4, :temp5, :temp6)", [
            ":measurement_datetime"=>$datetimeString,
            ":measurement_unixtime"=>$unixtime,
            ":temp1"=>$temp1,
            ":temp2"=>$temp2,
            ":temp3"=>$temp3,
            ":temp4"=>$temp4,
            ":temp5"=>$temp5,
            ":temp6"=>$temp6
        ]);

        if($success){
            echo "Data successfully received!";
        } else {
            echo "Failed to receive data!";
        }
    }
?>