<?php
	// get the HTTP method, path and body of the request
	$method = $_SERVER['REQUEST_METHOD'];
	$request = explode('/', trim($_SERVER['PATH_INFO'],'/'));
	$input = json_decode(file_get_contents('php://input'),true);

	// Setup Server and MongoDB configuration
	$user = "ogrady";
	require '/var/composer/vendor/autoload.php';
	$manager = new MongoDB\Driver\Manager("mongodb://localhost:27017");
	$collection = new MongoDB\Collection($manager, $user, 'DSNdata');

	// Prep data to be sent to the database
	$ts = new MongoDB\BSON\UTCDateTime();
	$data = ['Node_ID'=>$input["Node_ID"], 'data'=>$input["data"], 'ts'=>$ts];

	// Send the data to the server
	try {
		$collection->insertOne($data);
		var_dump($data);
	} catch (Exception $e) {
		print("<p>Insert failed.</p>");
	}
?>
