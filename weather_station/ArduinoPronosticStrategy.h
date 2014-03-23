/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: Matthieu Holtz
** Year: 2014
** -------------------------------------------------------------------------*/
#pragma once

#ifndef ARDUINOPRONOSTICTRATEGY_H
#define ARDUINOPRONOSTICTRATEGY_H

#include "APronosticStrategy.h"
#include "Arduino.h"

// Mean sea level pressure
#define ATM_PRESSURE 1013 //hPa

// Humidity level in the air when it rains
#define HUMIDITY_RAIN_RATE 60 //percent

// Six hours in milliseconds
#define SIX_HOURS_MILLIS 21600000 //ms

// One minute in milliseconds
#define ONE_MINUTE_MILLIS 60000 //ms


/**
* Concrete implementation of APronosticStrategy. It intends to compute a Pronostic value based both on pressure and humidity values.
*/
template<typename T>
class ArduinoPronosticStrategy : public APronosticStrategy<T>
{

public:
	ArduinoPronosticStrategy				()	:
										APronosticStrategy<T>(),
										_indoorHumidities_delay(ONE_MINUTE_MILLIS),
										_indoorPressures_delay(SIX_HOURS_MILLIS),
										_indoorHumiditiesMean_prev(0),
										_indoorPressuresMean_prev(0),
										_indoorHumiditiesMean_curr(0),
										_indoorPressuresMean_curr(0),
										_indoorHumidities_insertTime(0),
										_indoorPressures_insertTime(0)
	{}

	virtual		~ArduinoPronosticStrategy	()
	{
		return;
	}

	virtual		void		appendIndoorTemperature	(T indoorTemperature)
	{
		return;
	}

	virtual		void		appendIndoorHumidity	(T _indoorHumidity)
	{
		unsigned long time = getTime();

		if (_indoorHumidities_insertTime <= 0 || time >= _indoorHumidities_insertTime + _indoorHumidities_delay){
			_indoorHumiditiesMean_prev = _indoorHumiditiesMean_curr;
			_indoorHumiditiesMean_curr = _indoorHumidity;
			_indoorHumidities_insertTime = time;
		}
	}

	virtual		void		appendIndoorPressure	(T _indoorPressure)
	{
		unsigned long time = getTime();

		if (_indoorPressures_insertTime <= 0 || time >= _indoorPressures_insertTime + _indoorPressures_delay){
			
			_indoorPressuresMean_prev = _indoorPressuresMean_curr;
			_indoorPressuresMean_curr = _indoorPressure;
			_indoorPressures_insertTime = time;
		}
	}

	virtual		void		appendOutdoorTemperature	(T _outdoorTemperature)
	{
		return;
	}

	virtual		Pronostic	getPronostic			()
	{
		//If too much humidity in the air :

		if (_indoorHumiditiesMean_curr >= HUMIDITY_RAIN_RATE)
			return Rain;

		//If not algorithm computes pronostic based on pressure

		//With history :
		if (_indoorPressuresMean_prev <= 0){

			if (_indoorPressuresMean_curr > ATM_PRESSURE)
				return Sun;
			else
				return Cloud;
			 
		}
        //Without history :
		
        if (_indoorPressuresMean_curr > _indoorPressuresMean_prev)
            return Sun;
        
        //else
        return Cloud;
		

	}

	virtual		unsigned long		getTime		(){
		return millis();
	}

private:

	T						_indoorHumiditiesMean_prev;
	T						_indoorPressuresMean_prev;

	T						_indoorHumiditiesMean_curr;
	T						_indoorPressuresMean_curr;

	unsigned	long		_indoorHumidities_insertTime;
	unsigned	long		_indoorPressures_insertTime;

	unsigned	long		_indoorHumidities_delay;
	unsigned	long		_indoorPressures_delay;

};

#endif