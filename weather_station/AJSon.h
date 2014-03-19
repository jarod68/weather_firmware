/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: Matthieu Holtz
** Year: 2014
** -------------------------------------------------------------------------*/
#pragma once
#ifndef AJSON_H
#define AJSON_H

#include <Arduino.h>

/**
* 
*/

class AJSon 
{

public:

	AJSon(){}

	virtual ~AJSon()	{}

	/**
	* 
	*/
	virtual		String		jsonize () = 0;


};
#endif 