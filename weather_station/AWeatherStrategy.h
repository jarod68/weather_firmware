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
	virtual		void		appendIndoorTemperature		(T indoorTemperature)	= 0;

	/**
	* Appends to indoor humidity with the specified value, and recompute tendency
	*/
	virtual		void		appendIndoorHumidity		(T _indoorHumidity)		= 0;

	/**
	* Appends to indoor pressure with the specified value, and recompute tendency
	*/
	virtual		void		appendIndoorPressure		(T _indoorPressure)		= 0;

	/**
	* Appends to outdoor temperature with the specified value, and recompute tendency
	*/
	virtual		void		appendOutdoorTemperature	(T _outdoorTemperature)	= 0;

	
};
#endif 