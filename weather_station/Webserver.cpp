/* ---------------------------------------------------------------------------
 ** This software is in the public domain, furnished "as is", without technical
 ** support, and with no warranty, express or implied, as to its usefulness for
 ** any purpose.
 **
 ** Author: Matthieu Holtz
 ** Year: 2014
 ** -------------------------------------------------------------------------*/

#include "Webserver.h"
#include <SPI.h>

Webserver   ::  Webserver   (const unsigned int port,
                            WebserverDeliveryContentStrategy * deliveryStrategy) :
                            _server(new EthernetServer(port)),
                            _deliveryStrategy(deliveryStrategy)
{
    _server->begin();
}

Webserver   ::  ~Webserver      ()
{
    delete _server;
}

void    Webserver   ::  handle  ()
{
    // listen for incoming clients
    EthernetClient client = _server->available();
    if (client) {
        // an http request ends with a blank line
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                // if you've gotten to the end of the line (received a newline
                // character) and the line is blank, the http request has ended,
                // so you can send a reply
                if (c == '\n' && currentLineIsBlank) {
                    _deliveryStrategy->deliverTo(&client);
                    break;
                }
                if (c == '\n') {
                    // you're starting a new line
                    currentLineIsBlank = true;
                }
                else if (c != '\r') {
                    // you've gotten a character on the current line
                    currentLineIsBlank = false;
                }
            }
        }
        // give the web browser time to receive the data
        delay(1);
        // close the connection:
        client.stop();
    }
}
