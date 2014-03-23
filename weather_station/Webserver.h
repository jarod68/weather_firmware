/* ---------------------------------------------------------------------------
 ** This software is in the public domain, furnished "as is", without technical
 ** support, and with no warranty, express or implied, as to its usefulness for
 ** any purpose.
 **
 ** Author: Matthieu Holtz
 ** Year: 2014
 ** -------------------------------------------------------------------------*/

#pragma once

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Ethernet.h>
#include "WebserverDeliveryContentStrategy.h"

/**
 * This class is an Arduino HTTP webserver working on a specified port
 */
class Webserver {
    
public :
    
    /**
     * Constructor using port number parameter, and a WebserverDeliveryContentStrategy to handle the content delivery.
     */
    Webserver   (const unsigned int port, WebserverDeliveryContentStrategy * deliveryStrategy);
    
    virtual     ~Webserver();
    
    /**
     * This method handles an HTTP request. Calling handle has to be done in the main sketch loop() function
     */
    virtual     void    handle  ();
    
private :
    EthernetServer                      *   _server;
    WebserverDeliveryContentStrategy    *   _deliveryStrategy;
};



#endif
