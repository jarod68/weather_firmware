/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: Matthieu Holtz
** Year: 2014
** -------------------------------------------------------------------------*/

#pragma once
#ifndef ACLOCK_H
#define ACLOCK_H

class AClock
{

public:

	AClock(){}
	virtual ~AClock()	{}

	// Gets in the current timezone, the hours value
	virtual		unsigned int	getHours			()						= 0;

	// Gets the minutes value
	virtual		unsigned int	getMinutes			()						= 0;

	// Gets the seconds amount
	virtual		unsigned int	getSeconds			()						= 0;
	
	// Gets the current UTC hours value
	virtual		unsigned int	getHours_UTC		()						= 0;

	// Sets the timezone offset
	virtual		void			setTimezoneOffset	(unsigned int offset)	= 0;

	// Returns the timezone offset
	virtual		unsigned int	getTimezoneOffset	()						= 0;
};
#endif 