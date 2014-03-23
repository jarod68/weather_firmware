/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: Matthieu Holtz
** Year: 2014
** -------------------------------------------------------------------------*/
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
	virtual		void		appendIndoorTemperature		(const T indoorTemperature)     = 0;

	/**
	* Appends to indoor humidity with the specified value, and recompute tendency
	*/
	virtual		void		appendIndoorHumidity		(const T _indoorHumidity)		= 0;

	/**
	* Appends to indoor pressure with the specified value, and recompute tendency
	*/
	virtual		void		appendIndoorPressure		(const T _indoorPressure)		= 0;

	/**
	* Appends to outdoor temperature with the specified value, and recompute tendency
	*/
	virtual		void		appendOutdoorTemperature	(const T _outdoorTemperature)	= 0;

	
};
#endif 