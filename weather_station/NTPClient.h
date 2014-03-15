#pragma once
#ifndef NTPCLIENT_H
#define NTPCLIENT_H

#include <EthernetUdp.h>



class NTPClient
{
public:
	NTPClient(EthernetUDP * udp, const char * ntpIP);
	virtual ~NTPClient();

	virtual  unsigned long requestTime();
protected :
	void sendNTPpacket();

private :
	

	const unsigned int _localPort;
	EthernetUDP * _udp;
	const char * _ntpIP;
	uint8_t * _packetBuffer; //buffer to hold incoming and outgoing packets
	const static unsigned int  BUFFERSIZE;
};
#endif
