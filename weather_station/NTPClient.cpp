#include "NTPClient.h"
#include <SPI.h>
// NTP time stamp is in the first 48 bytes of the message

const  unsigned int  NTPClient::BUFFERSIZE = 48;

 NTPClient::NTPClient(EthernetUDP * udp, const char * ntpIP) :
	 _udp(udp), _ntpIP(ntpIP), _packetBuffer(NULL), _localPort(2390)
	
{
	
}


NTPClient::~NTPClient()
{
}

unsigned long NTPClient::requestTime(){

	_packetBuffer = new uint8_t[BUFFERSIZE];
	_udp->begin(_localPort);
	sendNTPpacket(); // send an NTP packet to a time server
	// wait to see if a reply is available
	delay(1000);

	if (_udp->parsePacket()) {
		Serial.println("packet received");
		// We've received a packet, read the data from it
		_udp->read(_packetBuffer, BUFFERSIZE); // read the packet into the buffer

		//the timestamp starts at byte 40 of the received packet and is four bytes,
		// or two words, long. First, esxtract the two words:

		unsigned long highWord = word(_packetBuffer[40], _packetBuffer[41]);
		unsigned long lowWord = word(_packetBuffer[42], _packetBuffer[43]);
		// combine the four bytes (two words) into a long integer
		// this is NTP time (seconds since Jan 1 1900):
		unsigned long secsSince1900 = highWord << 16 | lowWord;
		//Serial.print("Seconds since Jan 1 1900 = ");
		//Serial.println(secsSince1900);

		// now convert NTP time into everyday time:
		//Serial.print("Unix time = ");
		// Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
		const unsigned long seventyYears = 2208988800UL;
		// subtract seventy years:
		unsigned long epoch = secsSince1900 - seventyYears;
		/*
		Serial.print("---- FROM NTP ----");
		
		// print Unix time:
		Serial.println(epoch);


		// print the hour, minute and second:
		Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
		Serial.print((epoch % 86400L) / 3600); // print the hour (86400 equals secs per day)
		Serial.print(':');
		if (((epoch % 3600) / 60) < 10) {
			// In the first 10 minutes of each hour, we'll want a leading '0'
			Serial.print('0');
		}
		Serial.print((epoch % 3600) / 60); // print the minute (3600 equals secs per minute)
		Serial.print(':');
		if ((epoch % 60) < 10) {
			// In the first 10 seconds of each minute, we'll want a leading '0'
			Serial.print('0');
		}
		Serial.println(epoch % 60); // print the second
		*/
		delete[] _packetBuffer;
		return epoch;
	}
}


	void NTPClient::sendNTPpacket()
	{
		
		//Serial.println("1");
		// set all bytes in the buffer to 0
		memset(_packetBuffer, 0, BUFFERSIZE);
		// Initialize values needed to form NTP request
		// (see URL above for details on the packets)
		//Serial.println("2");
		_packetBuffer[0] = 0xE3;   // LI, Version, Mode
		_packetBuffer[1] = 0;     // Stratum, or type of clock
		_packetBuffer[2] = 6;     // Polling Interval
		_packetBuffer[3] = 0xEC;  // Peer Clock Precision
		// 8 bytes of zero for Root Delay & Root Dispersion
		_packetBuffer[12] = 49;
		_packetBuffer[13] = 0x4E;
		_packetBuffer[14] = 49;
		_packetBuffer[15] = 52;

		//Serial.println("3");

		// all NTP fields have been given values, now
		// you can send a packet requesting a timestamp:
		_udp->beginPacket(_ntpIP, 123); //NTP requests are to port 123
		//Serial.println("4");
		_udp->write(_packetBuffer, BUFFERSIZE);
		//Serial.println("5");
		_udp->endPacket();
		//Serial.println("6");
	}

