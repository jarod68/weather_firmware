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
					double _indoorTemperature, 
					double _indoorHumidity, 
					double _indoorPressure, 
					double _outdoorTemperature
					);
	
	virtual		~AWeatherDisplay()	{}
	
	virtual		void	display()	= 0;
	virtual		void	clear()		= 0;
	
	virtual		double	getIndoorTemperature	();
	virtual		double	getIndoorHumidity		();
	virtual		double	getIndoorPressure		();
	virtual		double	getOutdoorTemperature	();

	virtual		void	setIndoorTemperature	(double _indoorTemperature);
	virtual		void	setIndoorHumidity		(double _indoorHumidity);
	virtual		void	setIndoorPressure		(double _indoorPressure);
	virtual		void	setOutdoorTemperature	(double _outdoorTemperature);

protected:
	double	indoorTemperature;
	double	indoorHumidity;
	double	indoorPressure;
	double	outdoorTemperature;

};

#endif