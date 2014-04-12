/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: Matthieu Holtz
** Year: 2014
** -------------------------------------------------------------------------*/
#pragma once
#ifndef LCDWEATHERDISPLAY_H
#define LCDWEATHERDISPLAY_H

#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "WeatherInference.h"
#include "AWeatherDisplay.h"
#include "Pronostic.h"

class LCDWeatherDisplay : public AWeatherDisplay
{
public:
	LCDWeatherDisplay(WeatherInference<double> * inference);

	virtual		~LCDWeatherDisplay();

	virtual		void	display();
	virtual		void	clear();
	virtual		void	displayCloud	(const unsigned int	line, const unsigned int row);
	virtual		void	displaySun		(const unsigned int	line, const unsigned int row);
	virtual		void	displayRain		(const unsigned int	line, const unsigned int row);
	virtual		void	displayUpArrow	();
	virtual		void	displayDownArrow();

	inline		String	doubleToString	(const double		_double);


private:
	LiquidCrystal_I2C			*	lcd;
	WeatherInference<double>	*	_inference;

	static		uint8_t		up_right_arrow	[];
	static		uint8_t		down_right_arrow[];
	static		uint8_t		degres			[];
	static		uint8_t		sun_00			[];
	static		uint8_t		sun_01			[];
	static		uint8_t		sun_02			[];
	static		uint8_t		sun_10			[];
	static		uint8_t		sun_11			[];
	static		uint8_t		sun_12			[];
	static		uint8_t		cloud_00		[];
	static		uint8_t		cloud_01		[];
	static		uint8_t		cloud_02		[];
	static		uint8_t		cloud_10		[];
	static		uint8_t		cloud_11		[];
	static		uint8_t		cloud_12		[];
	static		uint8_t		rain_00			[];
	static		uint8_t		rain_01			[];
	static		uint8_t		rain_02			[];
	static		uint8_t		rain_10			[];
	static		uint8_t		rain_11			[];
	static		uint8_t		rain_12			[];


};

#endif