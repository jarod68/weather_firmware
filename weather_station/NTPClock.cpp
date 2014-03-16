/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: Matthieu Holtz
** Year: 2014
** -------------------------------------------------------------------------*/
#include "NTPClock.h"
#include <Arduino.h>

NTPClock::NTPClock(NTPClient * ntpClient) :_ntpClient(ntpClient),
										_localTimeReference(0),
										_ntpTimeReference(0),
										_timezoneOffset(0)
{
	this->synchronize();
}

NTPClock	::	NTPClock	(NTPClient * ntpClient, unsigned int timezoneOffset) :
																				_ntpClient(ntpClient),
																				_localTimeReference(0),
																				_ntpTimeReference(0),
																				_timezoneOffset(timezoneOffset)
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
	return getHours_UTC() + _timezoneOffset;
}

unsigned int	NTPClock	::	getMinutes		()
{
	return ((getPosixTimestamp() % 3600) / 60); 
}

unsigned int	NTPClock	::	getSeconds		()
{
	return (getPosixTimestamp() % 60);
}

unsigned int	NTPClock	::	getHours_UTC()
{
	return (getPosixTimestamp() % 86400L) / 3600;
}

void			NTPClock	::	setTimezoneOffset(unsigned int offset)
{
	_timezoneOffset = offset;
}

unsigned int	NTPClock	::	getTimezoneOffset()
{
	return _timezoneOffset;
}