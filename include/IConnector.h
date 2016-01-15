/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

#include <pthread.h>
#include "GeneralTypes.h"

typedef void (*RequestDataArrivedCallback)(void * data); 

/*
 * Service connectors.
 */
class IConnector {
    public:
        virtual ~IConnector();
        virtual void StartListener ();
		virtual void StopListener ();
        virtual void SendRequest (ConnectorData data);
        virtual void RegisterRequestArrivedCallback (RequestDataArrivedCallback callback);
        virtual void Listener () = 0;
        
        pthread_t 					requestListenerThread;
		RequestDataArrivedCallback	requestHandler;
		bool						IConnector_connectorWorking;
};