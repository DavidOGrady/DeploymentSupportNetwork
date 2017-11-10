<?php
   $user = "ogrady";
   require '/var/composer/vendor/autoload.php';
   print("<p>This is a test php/mongodb script delivered from /home/$user/www</p>");
   $manager = new MongoDB\Driver\Manager("mongodb://localhost:27017");
   $collection = new MongoDB\Collection($manager, $user, 'testData');
   $ts = new MongoDB\BSON\Timestamp(0,0);
   $data = ['id'=>'Demo1', 'value'=>88, 'ts'=>$ts];
   try {
      $collection->insertOne($data);
   } catch (\Exception $e) {
      print("<p>Insert failed.</p>");
   }
   $filter = [];
   $options = [];
   $query = new MongoDB\Driver\Query($filter, $options);
   $cursor = $manager->executeQuery("$user.testData", $query);
   print("<p>The contents of the collection $user.testData are:</p>");
   print("<pre>");
   print_r($cursor->toArray());
   print("</pre></body></html>");
?>
