/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

#include <pthread.h>
#include <string>
#include "IProvider.h"

typedef struct {
    long long   Address;
    std::string Name;
    double      Data;
    double      PrevData;
} SensorInfo;

class ISensor {
    public:
        void SetOutProvider (IProvider* provider);
        void SetInProvider (IProvider* provider);
        void SetSensorName (std::string name);
        void SetSensorAddress (long long address);
        
        virtual void SendData ();
        virtual void RecieveData ();
        virtual void DataArrivedCallback () = 0;
        
        virtual void Start () = 0;
        virtual void Stop () = 0;

        IProvider*  outProvider;
        IProvider*  inProvider;
        
        pthread_t   readDataThread;
        SensorInfo  sensor;
        bool        sensorReading;
};
