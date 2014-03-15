/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: Matthieu Holtz
** Year: 2014
** -------------------------------------------------------------------------*/

#include <util.h>
#include <EthernetUdp.h>
#include <EthernetServer.h>
#include <EthernetClient.h>
#include <Ethernet.h>
#include <Dns.h>
#include <Dhcp.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <dht11.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <OneWire.h>
#include <MemoryFree.h>

#include "LCDWeatherDisplay.h"
#include "SlidingHistory.h"
#include "ArduinoPronosticStrategy.h"
#include "ArduinoTendencyStrategy.h"
#include "WeatherInference.h"
#include "APronosticStrategy.h"
#include "NTPClient.h"
#include "NTPClock.h"
int dallasPin = 2;
int dht11Pin = 9;

dht11 DHT11;

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(119);

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(dallasPin);
DallasTemperature sensors(&oneWire);
DeviceAddress outsideThermometer = { 0x28, 0xFD, 0xCC, 0x74, 0x05, 0x00, 0x00, 0xB6 };

const char * ntpIP = "129.6.15.28";
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
IPAddress gatewayIP(192, 168, 1, 254);
IPAddress dnsIP(192, 168, 1, 254);
NTPClient * ntp;
NTPClock * clock;
LCDWeatherDisplay				*	display					= NULL;
WeatherInference<double>		*	inference				= NULL;
ArduinoTendencyStrategy<double> *	tendencyStrategy		= NULL;
APronosticStrategy<double>		*	pronosticStrategy		= NULL;

boolean isError = false;

double insideTemperature = -1;
double outsideTemperature = -1;
double insideHumidity = -1;
double insidePressure = -1;

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


void captureBMP180(){

	sensors_event_t event;
	bmp.getEvent(&event);

	/* Display the results (barometric pressure is measure in hPa) */
	if (event.pressure)
	{
		insidePressure = event.pressure;
	}
}

void captureDallasTemperature(){
	
	sensors.requestTemperatures();
	outsideTemperature = sensors.getTempC(outsideThermometer);

}

void captureDHT11Temperature(){

	int chk = DHT11.read(dht11Pin);

	switch (chk)
	{
	case -1:
		Serial.println("DHT11 Checksum error");
		isError = true;
		break;
	case -2:
		Serial.println("DHT11 Time out error");
		isError = true;
		break;

	}

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
	discoverOneWireDevices();
	sensors.begin();

	// set the resolution to 10 bit (good enough?)
	sensors.setResolution(outsideThermometer, 10);

	pronosticStrategy = new ArduinoPronosticStrategy<double>();
	tendencyStrategy = new ArduinoTendencyStrategy<double>(1, 30, 30, 30, 30);
	
	inference = new WeatherInference<double>(tendencyStrategy, pronosticStrategy);
	
	display = new LCDWeatherDisplay(inference);
	
	Ethernet.begin(mac, ip, dnsIP, gatewayIP);

	ntp = new NTPClient(ntpIP);

	clock = new NTPClock(ntp);
	clock->synchronize();

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

void handleError(){

	if (isError)
		Serial.print("Error");
	isError = false;
}
void loop()
{
	handleDisplay();

	Serial.print("freeMemory()=");
	Serial.println(freeMemory());

	Serial.print(clock->getHours());
	Serial.print(":");
	Serial.print(clock->getMinutes());
	Serial.print(":");
	Serial.print(clock->getSeconds());

	delay(1000);
}
