/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: Matthieu Holtz
** Year: 2014
** -------------------------------------------------------------------------*/
#pragma once
#ifndef AWEATHERDISPLAY_H
#define AWEATHERDISPLAY_H

#include <Arduino.h>

class AWeatherDisplay
{
public:
	AWeatherDisplay	();

	AWeatherDisplay	(
					const double _indoorTemperature,
					const double _indoorHumidity,
					const double _indoorPressure,
					const double _outdoorTemperature
					);
	
	virtual		~AWeatherDisplay()	{}
	
	virtual		void	display()	= 0;
	virtual		void	clear()		= 0;
	
	virtual		double	getIndoorTemperature	() const;
	virtual		double	getIndoorHumidity		() const;
	virtual		double	getIndoorPressure		() const;
	virtual		double	getOutdoorTemperature	() const;

	virtual		void	setIndoorTemperature	(const double _indoorTemperature);
	virtual		void	setIndoorHumidity		(const double _indoorHumidity);
	virtual		void	setIndoorPressure		(const double _indoorPressure);
	virtual		void	setOutdoorTemperature	(const double _outdoorTemperature);

protected:
	double	indoorTemperature;
	double	indoorHumidity;
	double	indoorPressure;
	double	outdoorTemperature;

};

#endif