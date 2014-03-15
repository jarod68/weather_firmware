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
