/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: Matthieu Holtz
** Year: 2014
** -------------------------------------------------------------------------*/
#include "AWeatherDisplay.h"


AWeatherDisplay		::	AWeatherDisplay		() :
											indoorTemperature	(-1), 
											indoorHumidity		(-1), 
											indoorPressure		(-1), 
											outdoorTemperature	(-1)
{}

AWeatherDisplay		::	AWeatherDisplay		(double _indoorTemperature, 
											 double _indoorHumidity, 
											 double _indoorPressure, 
											 double _outdoorTemperature) :
											 indoorTemperature	(_indoorTemperature), 
											 indoorHumidity		(_indoorHumidity), 
											 indoorPressure		(_indoorPressure), 
											 outdoorTemperature	(_outdoorTemperature)
{}

double	AWeatherDisplay		::		getIndoorTemperature	(){
	return indoorTemperature;
}
double	AWeatherDisplay		::		getIndoorHumidity		(){
	return indoorHumidity;
}
double	AWeatherDisplay		::		getIndoorPressure		(){
	return indoorPressure;
}
double	AWeatherDisplay::getOutdoorTemperature(){
	return outdoorTemperature;
}

void	AWeatherDisplay		::		setIndoorTemperature		(double _indoorTemperature)	{
	indoorTemperature = _indoorTemperature;
}
void	AWeatherDisplay		::		setIndoorHumidity			(double _indoorHumidity)	{
	indoorHumidity = _indoorHumidity;
}
void	AWeatherDisplay		::		setIndoorPressure			(double _indoorPressure)	{
	indoorPressure = _indoorPressure;
}
void	AWeatherDisplay		::		setOutdoorTemperature		(double _outdoorTemperature){
	outdoorTemperature = _outdoorTemperature;
}

