<?php
    require '/var/composer/vendor/autoload.php';

    // Setup  Server and MongoDB configuration

    $user = "ogrady";
    $manager = new MongoDB\Driver\Manager("mongodb://localhost:27017");
    $collection = new MongoDB\Collection($manager, $user, 'DSNdata');

    // Create query for database
    // There will be two types of queries coming into this file.
    // One with no query parameters. (The very first time it is called)
    // And one with a timestamp of the last data sent to the GUI

    $ts = new MongoDB\BSON\UTCDateTime($_GET["last_timestamp"]);

    if ($_GET["last_timestamp"]){
     // Where $_GET["last_timestamp"] greater than $ts
     $filter = ['ts' => ['$gt' => $ts]];
    }else{
     $filter = [];
    }
    $options = [];
    $query = new MongoDB\Driver\Query($filter, $options);
    $cursor = $manager->executeQuery("$user.DSNdata", $query);

    // Send Data to Client
    $JSONResponse = json_encode($cursor->toArray());
    echo $JSONResponse;

    // Long Polling Setup
    // This line is just there to check is a file has been modified.
    //$filename= dirname(__FILE__)."/data.txt";
    // We should use this line to receive the last timestamp from the client
    $last_timestamp = isset( $_GET['timestamp'])? $_GET['timestamp']: 0 ;
    // we need to change this line to get the last timestamp in the mongo server NOT the client
    $current_timestamp = get_timestamp();
    //$currentmodif=filemtime($filename);
    while ($currentmodif <= $lastmodif) {
    usleep(10000);
    clearstatcache();
    $currentmodif =filemtime($filename);
    }
    $response = array();
    $response['msg'] =Date("h:i:s")." ".file_get_contents($filename);
    $response['timestamp']= $currentmodif;
    echo json_encode($response);
?>
