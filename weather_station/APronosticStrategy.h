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
	virtual		Pronostic	getPronostic	()	{}


};
#endif 