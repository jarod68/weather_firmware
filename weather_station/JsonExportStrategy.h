/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: Matthieu Holtz
** Year: 2014
** -------------------------------------------------------------------------*/
#pragma once
#ifndef JSONEXPORTSTRATEGY_H
#define JSONEXPORTSTRATEGY_H

#include "AJSon.h"
#include "AWeatherStrategy.h"

/**
*
*/
template<typename T>
class JsonExportStrategy : public AWeatherStrategy<T>, public AJSon
{

public:

	JsonExportStrategy() : AJSon(), AWeatherStrategy<T>()
	{}

	virtual ~JsonExportStrategy()	{}

	virtual		String  jsonize		()
	{
		
		char  indoorTemperature[8];
		dtostrf(_indoorTemperature, 2, 1, indoorTemperature);
		
		char  outdoorTemperature[8];
		dtostrf(_outdoorTemperature, 2, 1, outdoorTemperature);

		char indoorHumidity[8];
		dtostrf(_indoorHumidity, 2, 1, indoorHumidity);

		char indoorPressure[8];
		dtostrf(_indoorPressure, 2, 1, indoorPressure);

		String	str = String("{ \"indoorTemp\" : \"");
				str.concat(indoorTemperature);
				str.concat("\" , \"outdoorTemp\" : \"");
				str.concat(outdoorTemperature);
				str.concat("\" , \"indoorHumidity\" : \"");
				str.concat(indoorHumidity);
				str.concat("\" , \"indoorPressure\" : \"");
				str.concat(indoorPressure);
				str.concat("\" }");
		
		return str;
	}

	virtual		void		appendIndoorTemperature(T indoorTemperature)
	{
		_indoorTemperature = indoorTemperature;
	}


	virtual		void		appendIndoorHumidity(T indoorHumidity)
	{
		_indoorHumidity = indoorHumidity;
	}


	virtual		void		appendIndoorPressure(T indoorPressure)
	{
		_indoorPressure = indoorPressure;
	}


	virtual		void		appendOutdoorTemperature(T outdoorTemperature)
	{
		_outdoorTemperature = outdoorTemperature;
	}


private :
	T _indoorTemperature, _indoorHumidity, _indoorPressure, _outdoorTemperature;

};
#endif 