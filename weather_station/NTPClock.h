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
	virtual		~NTPClock();

	// Returns the Posix timestamp value. AKA number of milliseconds since 1 jan. 1970.
	virtual		unsigned long	getPosixTimestamp	();

	// Synchronizes the clock with the ntp server used by this instance
	virtual		void			synchronize			();

	// Gets the current hours value
	virtual		unsigned int	getHours			();

	// Gets the current minutes value
	virtual		unsigned int	getMinutes			();

	// Gets the current seconds value
	virtual		unsigned int	getSeconds			();

protected :
	virtual		unsigned long	systemTimeSec		();

private:
	NTPClient	*	_ntpClient;
	unsigned long	_localTimeReference, _ntpTimeReference;
};
#endif
