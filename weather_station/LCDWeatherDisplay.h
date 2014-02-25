#pragma once
#ifndef LCDWEATHERDISPLAY_H
#define LCDWEATHERDISPLAY_H

#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "AWeatherInference.h"
#include "AWeatherDisplay.h"

class LCDWeatherDisplay : public AWeatherDisplay
{
public:
	LCDWeatherDisplay	(AWeatherInference<double> * inference);

	virtual		~LCDWeatherDisplay();

	virtual		void	display();
	virtual		void	clear();
	inline		String	doubleToString	(const double _double);


private:
	LiquidCrystal_I2C			*	lcd;
	AWeatherInference<double>	*	_inference;

	static		uint8_t		up_right_cross[8];
	static		uint8_t		down_left_cross[8];
	static		uint8_t		up_left_cross[8];
	static		uint8_t		down_right_cross[8];
	static		uint8_t		degres[8];

};

#endif