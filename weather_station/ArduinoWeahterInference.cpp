#include "ArduinoWeahterInference.h"
#include "Arduino.h"

ArduinoWeahterInference	::	ArduinoWeahterInference		(size_t historySize, unsigned long delay) :
	AWeatherInference<double>(historySize, delay, delay, delay, delay)
{
}


unsigned	long	ArduinoWeahterInference	::	getTime(){

	return millis();
}
