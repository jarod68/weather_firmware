#pragma once
#ifndef ACLOCK_H
#define ACLOCK_H

class AClock
{

public:

	AClock(){}
	virtual ~AClock()	{}

	virtual		unsigned int	getHours(){};
	virtual		unsigned int	getMinutes(){};
	virtual		unsigned int	getSeconds(){};

};
#endif 