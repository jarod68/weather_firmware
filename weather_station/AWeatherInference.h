#pragma once

#ifndef AWEATHERINFERENCE_H
#define AWEATHERINFERENCE_H

#include <Arduino.h>

#include "Tendency.h"
#include "SlidingHistory.h"


template<typename T>
class AWeatherInference
{


public:
	AWeatherInference(size_t historySize,
		unsigned long indoorTemperatures_delay,
		unsigned long indoorHumidities_delay,
		unsigned long indoorPressures_delay,
		unsigned long outdoorTemperatures_delay) :

		_indoorTemperatures(new SlidingHistory<T>(historySize)),
		_indoorHumidities(new SlidingHistory<T>(historySize)),
		_indoorPressures(new SlidingHistory<T>(historySize)),
		_outdoorTemperatures(new SlidingHistory<T>(historySize)),
		_indoorTemperatures_delay(indoorTemperatures_delay),
		_indoorHumidities_delay(indoorHumidities_delay),
		_indoorPressures_delay(indoorPressures_delay),
		_outdoorTemperatures_delay(outdoorTemperatures_delay),
		_indoorTemperaturesMean_prev(0),
		_indoorHumiditiesMean_prev(0),
		_indoorPressuresMean_prev(0),
		_outdoorTemperaturesMean_prev(0),
		_indoorTemperaturesMean_curr(0),
		_indoorHumiditiesMean_curr(0),
		_indoorPressuresMean_curr(0),
		_outdoorTemperaturesMean_curr(0),
		_indoorTemperatures_insertTime(0),
		_indoorHumidities_insertTime(0), 
		_indoorPressures_insertTime(0),
		_outdoorTemperatures_insertTime(0)

	{
	}

	void setIndoorTemperature(T _indoorTemperature){

		unsigned long time = getTime();

		if (time < _indoorTemperatures_insertTime || time >= _indoorTemperatures_insertTime + _indoorTemperatures_delay){

			_indoorTemperaturesMean_prev = _indoorTemperaturesMean_curr;
			this->_indoorTemperatures->addToHistory(_indoorTemperature);
			_indoorTemperaturesMean_curr = this->_indoorTemperatures->mean();
			_indoorTemperatures_insertTime = time;
		}

	}

	void setIndoorHumidity(T _indoorHumidity){
		unsigned long time = getTime();

		if (time < _indoorHumidities_insertTime || time >= _indoorHumidities_insertTime + _indoorHumidities_delay){
			_indoorHumiditiesMean_prev = _indoorHumiditiesMean_curr;
			this->_indoorHumidities->addToHistory(_indoorHumidity);
			_indoorHumiditiesMean_curr = this->_indoorHumidities->mean();
			_indoorHumidities_insertTime = time;
		}


	}
	void setIndoorPressure(T _indoorPressure){
		unsigned long time = getTime();

		if (time < _indoorPressures_insertTime || time >= _indoorPressures_insertTime + _indoorPressures_delay){

			_indoorPressuresMean_prev = _indoorPressuresMean_curr;
			this->_indoorPressures->addToHistory(_indoorPressure);
			_indoorPressuresMean_curr = this->_indoorPressures->mean();
			_indoorPressures_insertTime = time;
		}


	}
	void setOutdoorTemperature(T _outdoorTemperature){
		unsigned long time = getTime();

		if (time < _outdoorTemperatures_insertTime || time >= _outdoorTemperatures_insertTime + _outdoorTemperatures_delay){

			_outdoorTemperaturesMean_prev = _outdoorTemperaturesMean_curr;
			this->_outdoorTemperatures->addToHistory(_outdoorTemperature);
			_outdoorTemperaturesMean_curr = this->_outdoorTemperatures->mean();
			_outdoorTemperatures_insertTime = time;
		}

	}

	
	virtual Tendency getIndoorTemperatureTendency(){

		return _indoorTemperaturesMean_curr > _indoorTemperaturesMean_prev ? Rising : Falling;

	}
	virtual Tendency getIndoorHumidityTendency(){

		return _indoorHumiditiesMean_curr > _indoorHumiditiesMean_prev ? Rising : Falling;
	}
	virtual Tendency getIndoorPressureTendency(){

		return _indoorPressuresMean_curr > _indoorPressuresMean_prev ? Rising : Falling;
	}
	virtual Tendency getOutdoorTemperatureTendency(){

		return _outdoorTemperaturesMean_curr > _outdoorTemperaturesMean_prev ? Rising : Falling;

	}

	virtual unsigned long getTime(){ return 0; } //pure virtual method

private:
	SlidingHistory<T> * _indoorTemperatures;
	SlidingHistory<T> * _indoorHumidities;
	SlidingHistory<T> * _indoorPressures;
	SlidingHistory<T> * _outdoorTemperatures;

	T _indoorTemperaturesMean_prev;
	T _indoorHumiditiesMean_prev;
	T _indoorPressuresMean_prev;
	T _outdoorTemperaturesMean_prev;

	T _indoorTemperaturesMean_curr;
	T _indoorHumiditiesMean_curr;
	T _indoorPressuresMean_curr;
	T _outdoorTemperaturesMean_curr;

	unsigned long _indoorTemperatures_insertTime;
	unsigned long _indoorHumidities_insertTime;
	unsigned long _indoorPressures_insertTime;
	unsigned long _outdoorTemperatures_insertTime;

	unsigned long _indoorTemperatures_delay;
	unsigned long _indoorHumidities_delay;
	unsigned long _indoorPressures_delay;
	unsigned long _outdoorTemperatures_delay;

};

#endif