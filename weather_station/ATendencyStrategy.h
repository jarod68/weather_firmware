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
	virtual		Tendency	getIndoorTemperatureTendency	() = 0;

	/**
	* Gets the indoor humidity tendency
	*/
	virtual		Tendency	getIndoorHumidityTendency		() = 0;

	/**
	* Gets the indoor pressure tendency
	*/
	virtual		Tendency	getIndoorPressureTendency		() = 0;

	/**
	* Gets the outdoor temperature tendency
	*/
	virtual		Tendency	getOutdoorTemperatureTendency	() = 0;


};
#endif 