#pragma once
#ifndef AWEATHERSTRATEGY_H
#define AWEATHERSTRATEGY_H

#include "Tendency.h"

/**
*
*/
template<typename T>
class AWeatherStrategy
{

public:

	AWeatherStrategy				()	{}

	virtual		~AWeatherStrategy	()	{}

	/**
	* Appends to indoor humidity with the specified value, and recompute tendency
	*/
	virtual		void		appendIndoorTemperature		(T indoorTemperature){}

	/**
	* Appends to indoor humidity with the specified value, and recompute tendency
	*/
	virtual		void		appendIndoorHumidity		(T _indoorHumidity)	{}

	/**
	* Appends to indoor pressure with the specified value, and recompute tendency
	*/
	virtual		void		appendIndoorPressure		(T _indoorPressure)	{}

	/**
	* Appends to outdoor temperature with the specified value, and recompute tendency
	*/
	virtual		void		appendOutdoorTemperature	(T _outdoorTemperature){}

	
};
#endif 