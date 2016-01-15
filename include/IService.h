/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

#include <pthread.h>
#include "RESTApi.h"
#include "IConnector.h"

/*
 * Engine of the service.
 */
class IService {
    public:
        virtual ~IService ();
        void Start ();
        void Stop ();
        
        virtual void Continue ()    = 0;
        virtual void Pause ()       = 0;
        virtual void MainLoop ()    = 0;
        
        bool            IService_serviceWorking;
        IConnector*     out;
        IConnector*     in;
        RESTApi*        api;
};