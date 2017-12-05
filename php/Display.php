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
   $options = ['sort' => ['Node_ID' => 1]];
   $query = new MongoDB\Driver\Query($filter, $options);
   $cursor = $manager->executeQuery("$user.DSNdata", $query);

   // Send Data to Client
   $JSONResponse = json_encode($cursor->toArray());
   echo $JSONResponse;
?>
