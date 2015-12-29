/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

#include <pthread.h>
#include <string>

#include "IProvider.h"
#include "GeneralTypes.h"

class ISensor {
    public:
        ISensor ();
        ~ISensor ();
        
        void SetOutProvider (IProvider* provider);
        void SetInProvider (IProvider* provider);
        void SetSensorName (std::string name);
        void SetSensorAddress (long long address);
        void SetSensorType (SENSOR_TYPE type);
        void SetReadInterval (unsigned int interval);
        
        virtual void SendData ();
        virtual void RecieveData ();
        virtual void DataArrivedCallback ();
        virtual void Start ();
        virtual void Stop ();

        IProvider*      outProvider;
        IProvider*      inProvider;
        
        pthread_t       readDataThread;
        unsigned int    readInterval;
        SensorInfo      sensor;
        bool            sensorReading;
};
