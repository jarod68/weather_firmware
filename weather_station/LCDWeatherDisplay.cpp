#include "LCDWeatherDisplay.h"

#include "Tendency.h"

#define  lcd_Addr 0x27
#define  lcd_cols 20
#define  lcd_rows 4

#define up_right_cross_address 0
#define down_left_cross_address 1
#define up_left_cross_address 2
#define down_right_cross_address 3
#define degres_address 4



 uint8_t LCDWeatherDisplay::up_right_cross[8] = { 0x0, 0x0f, 0x03, 0x5, 0x09, 0x10, 0x0 };
 uint8_t LCDWeatherDisplay::down_left_cross[8] = { 0x0, 0x01, 0x12, 0x14, 0x18, 0x1e, 0x0 };
 uint8_t LCDWeatherDisplay::up_left_cross[8] = { 0x0, 0x1e, 0x18, 0x14, 0x12, 0x01, 0x0 };
 uint8_t LCDWeatherDisplay::down_right_cross[8] = { 0x0, 0x10, 0x09, 0x05, 0x03, 0x0f, 0x0 };
 uint8_t LCDWeatherDisplay::degres[8] = { 0x1c, 0x14, 0x1c, 0x00, 0x00, 0x00, 0x00 };


 LCDWeatherDisplay::LCDWeatherDisplay(AWeatherInference<double> * inference) :
	 AWeatherDisplay(), lcd(new LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows)), _inference(inference)
{
	lcd->init();
	lcd->createChar(up_right_cross_address, up_right_cross);
	lcd->createChar(down_left_cross_address, down_left_cross);
	lcd->createChar(down_right_cross_address, down_right_cross);
	lcd->createChar(up_left_cross_address, up_left_cross);
	lcd->createChar(degres_address, degres);

}

void LCDWeatherDisplay::display()
{

	lcd->backlight();
	lcd->setCursor(0, 0);
	lcd->print("In");
	lcd->setCursor(4, 0);
	lcd->print("temp = " + doubleToString(getIndoorTemperature())+' ');
	lcd->write(degres_address); lcd->print('c');
	lcd->setCursor(19, 0);

	 if (_inference->getIndoorTemperatureTendency() == Rising)
		lcd->write(up_right_cross_address); 
	else 
		lcd->write(down_right_cross_address);


	lcd->setCursor(4, 1);
	lcd->print("hum  = " + doubleToString(getIndoorHumidity()) + " %");
	lcd->setCursor(19, 1);
	if (_inference->getIndoorHumidityTendency() == Rising)
		lcd->write(up_right_cross_address);
	else 
		lcd->write(down_right_cross_address);

	lcd->setCursor(4, 2);
	lcd->print("pres = " + doubleToString(getIndoorPressure()) + "hPa");
	lcd->setCursor(19, 2);
	if (_inference->getIndoorPressureTendency() == Rising)
		lcd->write(up_right_cross_address);
	else 
		lcd->write(down_right_cross_address);

	lcd->setCursor(0, 3);
	lcd->print("Out");
	lcd->setCursor(4, 3);
	lcd->print("temp = " + doubleToString(getOutdoorTemperature())+' ');
	lcd->write(degres_address); lcd->print('c');
	lcd->setCursor(19, 3);
	if (_inference->getOutdoorTemperatureTendency() == Rising)
		lcd->write(up_right_cross_address);
	else
		lcd->write(down_right_cross_address);

}

void LCDWeatherDisplay::clear()
{
	lcd->clear();
}
String LCDWeatherDisplay::doubleToString(const double _double)
{
	char buffer[24];
	dtostrf(_double, 0, 1 ,buffer);
	return String(buffer);
}
