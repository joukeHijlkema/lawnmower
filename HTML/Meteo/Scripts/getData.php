<?php
function getData($myquery) {
    // echo $myquery."<br>";
    $username = "Meteo"; 
    $password = "!Meteo";   
    $host = "localhost";
    $database="Meteo";

    $server = mysql_connect($host, $username, $password);
    $connection = mysql_select_db($database, $server);
    $query = mysql_query($myquery);
    
    if ( ! $query ) {
        echo mysql_error();
        die;
    }
    
    $data = array();
    
    for ($x = 0; $x < mysql_num_rows($query); $x++) {
        $data[] = mysql_fetch_assoc($query);
    }

    mysql_close($server);

    return $data;
   
}

// print_r($_GET)."<br>";

if ($_GET['what'] == "actual") {
    $data = getData("SELECT Temperature,Humidity,Pressure,WindSpeed,WindDirection FROM `Mesurements` ORDER BY Time ASC LIMIT 1");
    $rain = getData("SELECT MAX(Rain)-MIN(Rain) AS Rain FROM `Mesurements` WHERE Time > DATE_SUB(NOW(), INTERVAL 1 DAY)");
    $data[0]['Rain']=$rain[0]['Rain'];
   
} else {
    $myquery ="";
}

// echo $myquery."<br>";

 echo json_encode($data);     
?>