<?php
function getData($myquery) {
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
    return json_encode($data);     
}

// print_r($_GET)."<br>";

$col   = $_GET['col'];
$start = $_GET['start'];
$end   = $_GET['end'];

if ($_GET['period'] == "day") {
    $myquery ="SELECT Time,$col as Value FROM Mesurements WHERE Time BETWEEN '$start' AND '$end'";
} else  if ($_GET['period']=='month' &&  $_GET['type'] =='avg') {
    $myquery ="SELECT `Time`, AVG($col) as Value FROM Mesurements WHERE Time BETWEEN '$start' AND '$end' GROUP BY YEAR(Time), MONTH(Time), DAY(Time)";
} else {
    $myquery ="";
}

// echo $myquery."<br>";

echo getData($myquery);

?>