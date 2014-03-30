<?php
include_once "weather_db.php";

$db = new weather_db(array('host' => 'localhost','user' => 'root','password' => 'raspberry','dbname' => 'weather'));


if (isset($_GET["from"]) && isset($_GET["to"]) ){

	print_r($db->retrieveValues(array('from' =>  htmlspecialchars($_GET["from"]), 'to' =>  htmlspecialchars($_GET["to"]))));

}elseif (isset($_GET["from"])){

	print_r($db->retrieveValues(array('from' =>  htmlspecialchars($_GET["from"]))));

}elseif (isset($_GET["to"])){

	print_r($db->retrieveValues(array('to' => htmlspecialchars($_GET["to"]))));

}else{

	print_r($db->retrieveValues());	
}

?>