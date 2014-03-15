#pragma once
#ifndef ATENDENCYSTRATEGY_H
#define ATENDENCYSTRATEGY_H

#include "AWeatherStrategy.h"
#include "Tendency.h"

/**
*
*/
template<typename T>
class ATendencyStrategy : public AWeatherStrategy<T>
{

public:

	ATendencyStrategy() : AWeatherStrategy<T>() {}

	virtual ~ATendencyStrategy(){}


	/**
	* Gets the indoor temperature tendency
	*/
	virtual		Tendency	getIndoorTemperatureTendency	(){};

	/**
	* Gets the indoor humidity tendency
	*/
	virtual		Tendency	getIndoorHumidityTendency		(){};

	/**
	* Gets the indoor pressure tendency
	*/
	virtual		Tendency	getIndoorPressureTendency		(){};

	/**
	* Gets the outdoor temperature tendency
	*/
	virtual		Tendency	getOutdoorTemperatureTendency	(){};


};
#endif 