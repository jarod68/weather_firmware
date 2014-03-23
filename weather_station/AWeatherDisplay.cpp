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

AWeatherDisplay		::	AWeatherDisplay		(const double _indoorTemperature,
											 const double _indoorHumidity,
											 const double _indoorPressure,
											 const double _outdoorTemperature) :
											 indoorTemperature	(_indoorTemperature), 
											 indoorHumidity		(_indoorHumidity), 
											 indoorPressure		(_indoorPressure), 
											 outdoorTemperature	(_outdoorTemperature)
{}

double	AWeatherDisplay		::		getIndoorTemperature	() const{
	return indoorTemperature;
}
double	AWeatherDisplay		::		getIndoorHumidity		() const{
	return indoorHumidity;
}
double	AWeatherDisplay		::		getIndoorPressure		() const{
	return indoorPressure;
}
double	AWeatherDisplay     ::      getOutdoorTemperature   () const{
	return outdoorTemperature;
}

void	AWeatherDisplay		::		setIndoorTemperature		(const double _indoorTemperature)	{
	indoorTemperature = _indoorTemperature;
}
void	AWeatherDisplay		::		setIndoorHumidity			(const double _indoorHumidity)	{
	indoorHumidity = _indoorHumidity;
}
void	AWeatherDisplay		::		setIndoorPressure			(const double _indoorPressure)	{
	indoorPressure = _indoorPressure;
}
void	AWeatherDisplay		::		setOutdoorTemperature		(const double _outdoorTemperature){
	outdoorTemperature = _outdoorTemperature;
}

