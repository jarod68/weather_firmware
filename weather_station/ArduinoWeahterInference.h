#pragma once

#ifndef ARDUINOWEATHERINFERENCE_H
#define ARDUINOWEATHERINFERENCE_H

#include "AWeatherInference.h"

class ArduinoWeahterInference : protected AWeatherInference<double>
{
public:
	ArduinoWeahterInference(size_t historySize, unsigned long delay);
	virtual unsigned long getTime();
};

#endif