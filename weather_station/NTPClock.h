#pragma once

#ifndef NTPCLOCK_H
#define NTPCLOCK_H

#include "AClock.h"
#include "NTPClient.h"

class NTPClock : public AClock
{
public:
	NTPClock	(NTPClient * ntpClient);
	virtual		~NTPClock();

	virtual		unsigned long	getPosixTimestamp	();
	virtual		void			synchronize			();
	virtual		unsigned int	getHours			();
	virtual		unsigned int	getMinutes			();
	virtual		unsigned int	getSeconds			();

protected :
	virtual		unsigned long	systemTimeSec		();

private:
	NTPClient	*	_ntpClient;
	unsigned long	_localTimeReference, _ntpTimeReference;
};
#endif
