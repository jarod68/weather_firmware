#include "NTPClock.h"
#include <Arduino.h>

NTPClock	::	NTPClock	(NTPClient * ntpClient) :
													_ntpClient(ntpClient),
													_localTimeReference(0),
													_ntpTimeReference(0)
{
	this->synchronize();
}

NTPClock	::	~NTPClock	()
{
}

unsigned long  NTPClock		::	getPosixTimestamp	()
{
	return _ntpTimeReference + systemTimeSec() - _localTimeReference;
}

void			NTPClock	::	synchronize		()
{
	_ntpTimeReference = _ntpClient->requestTime();
	_localTimeReference = systemTimeSec();
}

unsigned long	NTPClock	::	systemTimeSec	()
{
	return (unsigned long)((double)millis() / 1000.0);
}

unsigned int	NTPClock	::	getHours		()
{
	return (getPosixTimestamp() % 86400L) / 3600; 
}

unsigned int	NTPClock	::	getMinutes		()
{
	return ((getPosixTimestamp() % 3600) / 60); 
}

unsigned int	NTPClock	::	getSeconds		()
{
	return (getPosixTimestamp() % 60);
}