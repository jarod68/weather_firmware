/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: Matthieu Holtz
** Year: 2014
** -------------------------------------------------------------------------*/
#include "LCDWeatherDisplay.h"

#include "Tendency.h"
#include "Pronostic.h"

#define  lcd_Addr 0x27
#define  lcd_cols 20
#define  lcd_rows 4

#define up_right_cross_address 6
#define down_right_cross_address 7

#define ico_00_address 0
#define ico_01_address 1
#define ico_02_address 2
#define ico_10_address 3
#define ico_11_address 4
#define ico_12_address 5

 uint8_t	LCDWeatherDisplay	::	up_right_arrow	[8] = { 0x00, 0x0f, 0x03, 0x05, 0x09, 0x10, 0x00	};
 uint8_t	LCDWeatherDisplay	::	down_left_arrow	[8] = { 0x00, 0x01, 0x12, 0x14, 0x18, 0x1e, 0x00	};
 uint8_t	LCDWeatherDisplay	::	up_left_arrow	[8] = { 0x00, 0x1e, 0x18, 0x14, 0x12, 0x01, 0x00	};
 uint8_t	LCDWeatherDisplay	::	down_right_arrow[8] = { 0x00, 0x10, 0x09, 0x05, 0x03, 0x0f, 0x00	};
 uint8_t	LCDWeatherDisplay	::	degres			[8] = { 0x1c, 0x14, 0x1c, 0x00, 0x00, 0x00, 0x00	};

 uint8_t	LCDWeatherDisplay	::	sun_00			[9] = { 0x00, 0x00, 0x04, 0x02, 0x01, 0x00, 0x01, 0x1f };
 uint8_t	LCDWeatherDisplay	::	sun_01			[9] = { 0x04, 0x04, 0x04, 0x04, 0x0e, 0x11, 0x00, 0x00 };
 uint8_t	LCDWeatherDisplay	::	sun_02			[9] = { 0x00, 0x00, 0x04, 0x08, 0x10, 0x00, 0x10, 0x1e };
 uint8_t	LCDWeatherDisplay	::	sun_10			[9] = { 0x01, 0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00 };
 uint8_t	LCDWeatherDisplay	::	sun_11			[9] = { 0x00, 0x00, 0x11, 0x04, 0x04, 0x04, 0x04, 0x04 };
 uint8_t	LCDWeatherDisplay	::	sun_12			[9] = { 0x10, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00, 0x00 };

 uint8_t	LCDWeatherDisplay	::	cloud_00		[9] = { 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f };
 uint8_t	LCDWeatherDisplay	::	cloud_01		[9] = { 0x00, 0x00, 0x00, 0x01, 0x12, 0x1c, 0x18, 0x18 };
 uint8_t	LCDWeatherDisplay	::	cloud_02		[9] = { 0x00, 0x00, 0x00, 0x10, 0x08, 0x04, 0x02, 0x02 };
 uint8_t	LCDWeatherDisplay	::	cloud_10		[9] = { 0x0f, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00 };
 uint8_t	LCDWeatherDisplay	::	cloud_11		[9] = { 0x18, 0x10, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00 };
 uint8_t	LCDWeatherDisplay	::	cloud_12		[9] = { 0x02, 0x04, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00 };

 uint8_t	LCDWeatherDisplay	::	rain_00			[9] = { 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f };
 uint8_t	LCDWeatherDisplay	::	rain_01			[9] = { 0x00, 0x00, 0x00, 0x01, 0x12, 0x1c, 0x18, 0x18 };
 uint8_t	LCDWeatherDisplay	::	rain_02			[9] = { 0x00, 0x00, 0x00, 0x10, 0x08, 0x04, 0x02, 0x02 };
 uint8_t	LCDWeatherDisplay	::	rain_10			[9] = { 0x0f, 0x0f, 0x07, 0x02, 0x04, 0x09, 0x12, 0x00 };
 uint8_t	LCDWeatherDisplay	::	rain_11			[9] = { 0x18, 0x10, 0x1f, 0x12, 0x04, 0x09, 0x12, 0x00 };
 uint8_t	LCDWeatherDisplay	::	rain_12			[9] = { 0x02, 0x04, 0x18, 0x08, 0x10, 0x00, 0x00, 0x00 };



 LCDWeatherDisplay	::	LCDWeatherDisplay	(WeatherInference<double> * inference) :
	 AWeatherDisplay(), lcd(new LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows)), _inference(inference)
{
	lcd->init();
	lcd->createChar(up_right_cross_address, up_right_arrow); lcd->createChar(down_right_cross_address, down_right_arrow);
}

 LCDWeatherDisplay	::	~LCDWeatherDisplay	(){ 
	 delete _inference;
 }

void	LCDWeatherDisplay	::	display	()
{

	lcd->backlight();
	lcd->setCursor(0, 0);
	lcd->print("In");
	lcd->setCursor(4, 0);
	lcd->print("temp = " + doubleToString(getIndoorTemperature())+' ');
	displayDegres(); 
	lcd->print('c');
	lcd->setCursor(19, 0);

	if (_inference->getIndoorTemperatureTendency() == Rising)
		displayUpArrow();
	else
		displayDownArrow();
		 

	 
	lcd->setCursor(4, 1);
	lcd->print("hum  = " + doubleToString(getIndoorHumidity()) + " %");
	lcd->setCursor(19, 1);
	if (_inference->getIndoorHumidityTendency() == Rising)
		displayUpArrow();
	else
		displayDownArrow();

	lcd->setCursor(4, 2);
	lcd->print("pres = " + doubleToString(getIndoorPressure()) + "hP");
	lcd->setCursor(19, 2);
	if (_inference->getIndoorPressureTendency() == Rising)
		displayUpArrow();
	else
		displayDownArrow();

	lcd->setCursor(0, 3);
	lcd->print("Out");
	lcd->setCursor(4, 3);
	lcd->print("temp = " + doubleToString(getOutdoorTemperature())+' ');
	displayDegres(); lcd->print('c');
	lcd->setCursor(19, 3);
	if (_inference->getOutdoorTemperatureTendency() == Rising)
		displayUpArrow();
	else
		displayDownArrow();

	if (_inference->getPronostic() == Sun){
		displaySun(1, 0);
	}
	else if (_inference->getPronostic() == Rain){
		displayRain(1, 0);
	}
	else if (_inference->getPronostic() == Cloud){
		displayCloud(1, 0);
	}


	/*
	lcd->setCursor(0, 1);
	lcd->write(sun_00_address);
	lcd->write(sun_01_address);
	lcd->write(sun_02_address);

	lcd->setCursor(0, 2);
	lcd->write(sun_10_address);
	lcd->write(sun_11_address);
	lcd->write(sun_12_address);
	*/
	
	
}

void	LCDWeatherDisplay::displayUpArrow()
{
	
	
	lcd->write(up_right_cross_address);
}
void	LCDWeatherDisplay::displayDownArrow()
{
	

	lcd->write(down_right_cross_address);
}
void	LCDWeatherDisplay::displayDegres()
{
	//lcd->createChar(ico_00_address, degres);

	//lcd->write(ico_00_address);
}

void	LCDWeatherDisplay::displaySun(const unsigned int	line, const unsigned int row)
{
	lcd->createChar(ico_00_address, sun_00);
	lcd->createChar(ico_01_address, sun_01);
	lcd->createChar(ico_02_address, sun_02);
	lcd->createChar(ico_10_address, sun_10);
	lcd->createChar(ico_11_address, sun_11);
	lcd->createChar(ico_12_address, sun_12);

	lcd->setCursor(row, line);
	lcd->write(ico_00_address);
	lcd->write(ico_01_address);
	lcd->write(ico_02_address);

	lcd->setCursor(row, line + 1);
	lcd->write(ico_10_address);
	lcd->write(ico_11_address);
	lcd->write(ico_12_address);
}
void	LCDWeatherDisplay	::	displayCloud	(const unsigned int	line, const unsigned int row)
{
	lcd->createChar(ico_00_address, cloud_00);
	lcd->createChar(ico_01_address, cloud_01);
	lcd->createChar(ico_02_address, cloud_02);
	lcd->createChar(ico_10_address, cloud_10);
	lcd->createChar(ico_11_address, cloud_11);
	lcd->createChar(ico_12_address, cloud_12);
	
	lcd->setCursor(row, line);
	lcd->write(ico_00_address);
	lcd->write(ico_01_address);
	lcd->write(ico_02_address);

	lcd->setCursor(row, line+1);
	lcd->write(ico_10_address);
	lcd->write(ico_11_address);
	lcd->write(ico_12_address);
}

void	LCDWeatherDisplay::displayRain(const unsigned int	line, const unsigned int row)
{
	lcd->createChar(ico_00_address, rain_00);
	lcd->createChar(ico_01_address, rain_01);
	lcd->createChar(ico_02_address, rain_02);
	lcd->createChar(ico_10_address, rain_10);
	lcd->createChar(ico_11_address, rain_11);
	lcd->createChar(ico_12_address, rain_12);

	lcd->setCursor(row, line);
	lcd->write(ico_00_address);
	lcd->write(ico_01_address);
	lcd->write(ico_02_address);

	lcd->setCursor(row, line + 1);
	lcd->write(ico_10_address);
	lcd->write(ico_11_address);
	lcd->write(ico_12_address);
}

void	LCDWeatherDisplay	::	clear	()
{
	lcd->clear();
}
String	LCDWeatherDisplay	::	doubleToString	(const double _double)
{
	char buffer[24];
	dtostrf(_double, 0, 1 ,buffer);
	return String(buffer);
}
