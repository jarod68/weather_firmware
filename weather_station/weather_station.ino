/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: Matthieu Holtz
** Year: 2014
** -------------------------------------------------------------------------*/

#define TEN_MINUTES_MILLIS 600000
//#define DISCOVER_ONE_WIRE_DEVICES


#include <Ethernet.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include "dht11.h"
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <OneWire.h>
//#include <MemoryFree.h>
//#include <SD.h>
//#include <EthernetUdp.h>

#include "LCDWeatherDisplay.h"
#include "SlidingHistory.h"
#include "ArduinoPronosticStrategy.h"
#include "ArduinoTendencyStrategy.h"
#include "WeatherInference.h"
#include "APronosticStrategy.h"
#include "JsonExportStrategy.h"
#include "Webserver.h"

const int dallasPin     = 2;
const int dht11Pin      = 9;
const int SDchipSelect  = 4;

// DHT11 temperature sensor setup
dht11 DHT11;

// BMP085 pressure sensor setup
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(119);

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(dallasPin);
DallasTemperature sensors(&oneWire);
DeviceAddress outsideThermometer = { 0x28, 0xFD, 0xCC, 0x74, 0x05, 0x00, 0x00, 0xB6 };

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
//IPAddress gatewayIP(192, 168, 0, 1);
//IPAddress dnsIP(192, 168, 1, 254);

Webserver                       *   server                  = NULL;
LCDWeatherDisplay				*	display					= NULL;
WeatherInference<double>		*	inference				= NULL;
ArduinoTendencyStrategy<double> *	tendencyStrategy		= NULL;
APronosticStrategy<double>		*	pronosticStrategy		= NULL;
JsonExportStrategy<double>		*	exportStrategy			= NULL;
boolean isError = false;

double insideTemperature = -1;
double outsideTemperature = -1;
double insideHumidity = -1;
double insidePressure = -1;

#ifdef DISCOVER_ONE_WIRE_DEVICES
void discoverOneWireDevices(void) {
	byte i;
	byte present = 0;
	byte data[12];
	byte addr[8];

	Serial.print("Looking for 1-Wire devices...\n\r");
	while (oneWire.search(addr)) {
		Serial.print("\n\rFound \'1-Wire\' device with address:\n\r");
		for (i = 0; i < 8; i++) {
			Serial.print("0x");
			if (addr[i] < 16) {
				Serial.print('0');
			}
			Serial.print(addr[i], HEX);
			if (i < 7) {
				Serial.print(", ");
			}
		}
		if (OneWire::crc8(addr, 7) != addr[7]) {
			Serial.print("CRC is not valid!\n");
			return;
		}
	}
	Serial.print("\n\r\n\rThat's it.\r\n");
	oneWire.reset_search();
	return;
}
#endif

void captureBMP180(){

	sensors_event_t event;
	bmp.getEvent(&event);

    if (event.pressure)
		insidePressure = event.pressure;
	
}

void captureDallasTemperature(){
	
	sensors.requestTemperatures();
	outsideTemperature = sensors.getTempC(outsideThermometer);

}

void captureDHT11Temperature(){

	int chk = DHT11.read(dht11Pin);

	insideHumidity = DHT11.humidity;
	insideTemperature = DHT11.temperature;

}

void setup()
{
	pinMode(dallasPin, INPUT);
	pinMode(dht11Pin, INPUT);
	bmp.begin();
	
	Serial.begin(9600);
	delay(2000);
    
    #ifdef DISCOVER_ONE_WIRE_DEVICES
	discoverOneWireDevices();
    #endif
    
	sensors.begin();

	// set the resolution to 10 bit (good enough?)
	sensors.setResolution(outsideThermometer, 10);

	pronosticStrategy = new ArduinoPronosticStrategy<double>();
    
	tendencyStrategy = new ArduinoTendencyStrategy<double>(3, TEN_MINUTES_MILLIS, TEN_MINUTES_MILLIS, TEN_MINUTES_MILLIS, TEN_MINUTES_MILLIS);
    
	exportStrategy = new JsonExportStrategy<double>();
    
	inference = new WeatherInference<double>(tendencyStrategy, pronosticStrategy, exportStrategy);
	
	display = new LCDWeatherDisplay(inference);
	
	Ethernet.begin(mac, ip);

    server = new Webserver(80, exportStrategy);
    
}

void handleDisplay(){

	captureDallasTemperature();
	captureDHT11Temperature();
	captureBMP180();

	display->setIndoorHumidity(insideHumidity);
	display->setIndoorTemperature(insideTemperature);
	display->setOutdoorTemperature(outsideTemperature);
	display->setIndoorPressure(insidePressure);
	
	inference->appendIndoorHumidity(insideHumidity);
	inference->appendIndoorTemperature(insideTemperature);
	inference->appendOutdoorTemperature(outsideTemperature);
	inference->appendIndoorPressure(insidePressure);

	display->display();
	delay(100);
}

void loop()
{
	handleDisplay();
	
	//Serial.print("freeMemory()=");
	//Serial.println(freeMemory());
    server->handle();
	
    //Speed down execution
	delay(100);
}
