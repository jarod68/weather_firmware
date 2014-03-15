/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: Matthieu Holtz
** Year: 2014
** -------------------------------------------------------------------------*/
#pragma once
#ifndef PRONOSTICSTRATEGY_H
#define PRONOSTICSTRATEGY_H

#include "AWeatherStrategy.h"
#include "Pronostic.h"

/**
* This class is a an abstract strategy to be used with WeatherInference. It intends to compute a Pronostic value.
*/
template<typename T>
class APronosticStrategy : public AWeatherStrategy<T>
{

public:

	APronosticStrategy()	:	AWeatherStrategy<T>	()	{}

	virtual ~APronosticStrategy						()	{}

	/**
	* Computes the pronostic
	*/
	virtual		Pronostic	getPronostic()	=	0;


};
#endif 