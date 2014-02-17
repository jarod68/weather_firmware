#pragma once
#ifndef LCDWEATHERDISPLAY_H
#define LCDWEATHERDISPLAY_H

#include "AWeatherDisplay.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


class LCDWeatherDisplay : protected AWeatherDisplay
{
public:
	LCDWeatherDisplay();
	virtual void display();
	virtual void clear();
	inline String doubleToString(const double _double);

	virtual void setIndoorTemperature(double _indoorTemperature);
	virtual void setIndoorHumidity(double _indoorHumidity);
	virtual void setIndoorPressure(double _indoorPressure);
	virtual void setOutdoorTemperature(double _outdoorTemperature);

protected :
	double previousIndoorTemperature;
	double previousIndoorHumidity;
	double previousIndoorPressure;
	double previousOutdoorTemperature;

private:
	LiquidCrystal_I2C * lcd;
	static uint8_t up_right_cross[8];
	static uint8_t down_left_cross[8];
	static uint8_t up_left_cross[8];
	static uint8_t down_right_cross[8];
	static uint8_t degres[8];



};

#endif