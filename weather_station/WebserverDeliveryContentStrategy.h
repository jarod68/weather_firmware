/* ---------------------------------------------------------------------------
 ** This software is in the public domain, furnished "as is", without technical
 ** support, and with no warranty, express or implied, as to its usefulness for
 ** any purpose.
 **
 ** Author: Matthieu Holtz
 ** Year: 2014
 ** -------------------------------------------------------------------------*/
#pragma once

#ifndef WEBSERVERDELIVERYCONTENTSTRATEGY_H
#define WEBSERVERDELIVERYCONTENTSTRATEGY_H

#include <Ethernet.h>

/**
 * This pure virtual class defines delivering strategy for a Webserver instance
 */
class WebserverDeliveryContentStrategy {
    
    
public :
    
    /**
     * Delivers content to the argument specified EthernetClient's
     */
    virtual     void    deliverTo   (EthernetClient * client)   =   0;
    
};


#endif
