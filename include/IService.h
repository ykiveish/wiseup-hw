/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

#include <pthread.h>
#include "RESTApi.h"

typedef struct {
    uint8_t     Data[64];
} ConnectorData;

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

/*
 * Engine of the service.
 */
class IService {
    public:
        void Start ();
        void Stop ();
        
        virtual void MainLoop () = 0;
    
    protected:
        IConnector  out;
        IConnector  in;
        RESTApi*    api;
};