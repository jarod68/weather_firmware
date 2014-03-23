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
#include "WebserverDeliveryContentStrategy.h"
#include <SPI.h>

/**
* This class is an implementation of AWeatherStrategy, AJSon, and WebserverDeliveryContentStrategy.
* It intends to compute a JSon output of weather sensors, and serve them to an EthernetClient
*/
template<typename T>
class JsonExportStrategy : public AWeatherStrategy<T>, public AJSon, public WebserverDeliveryContentStrategy
{

public:

	JsonExportStrategy() : AJSon(), AWeatherStrategy<T>(), WebserverDeliveryContentStrategy()
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

		String	str = String("{\"iT\":\"");
				str.concat(indoorTemperature);
				str.concat("\",\"oT\":\"");
				str.concat(outdoorTemperature);
				str.concat("\",\"iH\":\"");
				str.concat(indoorHumidity);
				str.concat("\",\"iP\":\"");
				str.concat(indoorPressure);
				str.concat("\"}");
		
		return str;
	}
    
    virtual void deliverTo(EthernetClient * client){
        
            client->println("HTTP/1.1 200 OK\nContent-Type: text\nConnection: close\nRefresh: 5\n");

            client->println(this->jsonize());
         
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