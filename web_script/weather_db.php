<?php
class weather_db{

	private $link 		;
	private $host 		;
	private $user 		;
	private $password  	;
	private $dbname 	;

	public function __construct(){

		$arg_list = func_get_args()[0];

		$this->host 	= 	$arg_list['host'];
		$this->user 	= 	$arg_list['user'];
		$this->password = 	$arg_list['xxx'];
		$this->dbname 	= 	$arg_list['dbname'];
	}

	protected function connect(){

		$sqli = mysqli_connect($this->host, $this->user, $this->password, $this->dbname) or die("Error " . mysqli_error($sqli));
		$this->link = $sqli;
	}

	protected  function close(){
		$this->link->close();
		$this->link = NULL;
	}

	protected function handleError(){

		if (mysqli_connect_errno($this->link)) {
			echo "Error during database connection : " . mysqli_connect_error();
		}
	}

	public function insertValues (){


		$arg_list = func_get_args()[0];
		$this->connect();

		$request = "INSERT INTO record(indoor_temp, indoor_humidity, indoor_pressure, outdoor_temperature) VALUES (". $arg_list['indoor_temp'] . ",". $arg_list['indoor_humidity'] ."," . $arg_list['indoor_pressure']. "," .$arg_list['outdoor_temperature'].");";
		$result = $this->link->query($request);
		$this->handleError();
		$this->close();
	}

	public function retrieveValues (){


		$arg_list = func_get_args()[0];
		
		$from 	= $arg_list['from'];
		$to 	= $arg_list['to'];

		$request = 'SELECT indoor_temp, indoor_humidity, indoor_pressure, outdoor_temperature, timestamp FROM record';

		if ((isset($arg_list['from']) && isset($arg_list['to']))){
			$request = $request . ' WHERE timestamp > "' . $arg_list['from'] . '" AND timestamp < "' . $arg_list['to'] . '"';
		} elseif (isset($arg_list['from'])) {
			$request = $request . ' WHERE timestamp > "' . $arg_list['from'] .'"';
		} elseif (isset($arg_list['to'])) {
			$request = $request . ' WHERE timestamp < "' . $arg_list['to'] .'"';
		}
		echo $request;
		$this->connect();
		$result = $this->link->query($request);
		$this->handleError();
		$toEncode = array();
		$i=0;
		while($row = mysqli_fetch_array($result))
		{
			$entry = array('timestamp' => $row['timestamp'], 'indoor_temp' => $row['indoor_temp'], 'indoor_humidity' => $row['indoor_humidity'], 'indoor_pressure' => $row['indoor_pressure'], 'outdoor_temperature' => $row['outdoor_temperature'] );

			array_push($toEncode, $entry);
		}
		$this->close();
		$json = json_encode($toEncode);
		
		return $json;
	}

}

?>