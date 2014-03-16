/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: Matthieu Holtz
** Year: 2014
** -------------------------------------------------------------------------*/
#pragma once

#ifndef NTPCLOCK_H
#define NTPCLOCK_H

#include "AClock.h"
#include "NTPClient.h"

// This class is a concrete AClock implementation using NTP request to synchronize local Arduino's time with real outside world time. 
// It provides a seconds precisions since NTP doesn't support milliseconds time synchronization.
class NTPClock : public AClock
{
public:
	// Constructor using NTPClient pointer as parameter. The NTPCLient is needed to provide NTP time synchronization with local Arduino time
	NTPClock	(NTPClient * ntpClient);

	// Constructor using NTPClient pointer as parameter. The NTPCLient is needed to provide NTP time synchronization with local Arduino time. 
	// The timezoneOffset parameter is used to specify timezone.
	NTPClock(NTPClient * ntpClient, unsigned int timezoneOffset);

	virtual		~NTPClock();

	// Returns the Posix timestamp value. AKA number of milliseconds since 1 jan. 1970.
	virtual		unsigned long	getPosixTimestamp	();

	// Synchronizes the clock with the ntp server used by this instance
	virtual		void			synchronize			();

	virtual		unsigned int	getHours			();

	virtual		unsigned int	getMinutes			();

	virtual		unsigned int	getSeconds			();

	virtual		unsigned int	getHours_UTC		();

	virtual		void			setTimezoneOffset	(unsigned int offset);

	virtual		unsigned int	getTimezoneOffset	();

protected :
	virtual		unsigned long	systemTimeSec		();

private:
	NTPClient	*	_ntpClient;
	unsigned long	_localTimeReference, _ntpTimeReference;
	unsigned int	_timezoneOffset;
};
#endif
