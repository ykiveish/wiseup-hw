/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

#include <pthread.h>
#include "GeneralTypes.h"

/*
 * Service connectors.
 */
class IConnector {
    public:
        virtual void StartListener ();
        virtual void SendRequest (ConnectorData data);
        virtual void RegisterRequestArrivedCallback ();
        virtual void Listener () = 0;
        
        pthread_t requestListenerThread;
};