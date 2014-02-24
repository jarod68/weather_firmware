#pragma once

#ifndef ARDUINOWEATHERINFERENCE_H
#define ARDUINOWEATHERINFERENCE_H

#include <Arduino.h>

#include "AWeatherInference.h"

class ArduinoWeahterInference : public AWeatherInference<double>
{
public:
	ArduinoWeahterInference(size_t historySize, unsigned long delay);
	virtual unsigned long getTime();
};

#endif