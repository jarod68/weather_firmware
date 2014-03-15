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

	virtual		unsigned int	getHours	()	=	0;
	virtual		unsigned int	getMinutes	()	=	0;
	virtual		unsigned int	getSeconds	()	=	0;

};
#endif 