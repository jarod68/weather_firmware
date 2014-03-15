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