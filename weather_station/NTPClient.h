/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: Matthieu Holtz
** Year: 2014
** -------------------------------------------------------------------------*/
#pragma once
#ifndef NTPCLIENT_H
#define NTPCLIENT_H

#include <EthernetUdp.h>

/**
* NTP client to retrieve time over network
*/
class NTPClient
{
public:
	// Constructor using the NTP server IP address to be used
	NTPClient	(const char * ntpIP);
	virtual		~NTPClient();

	// Requests time by sending a request to the NTP server
	virtual		unsigned long	requestTime	();
protected:
	void sendNTPpacket();

private:
	const unsigned int	_localPort;
	EthernetUDP		*	_udp;
	const char		*	_ntpIP;
	uint8_t			*	_packetBuffer; //buffer to hold incoming and outgoing packets
	const static unsigned int	BUFFERSIZE;
};

#endif
