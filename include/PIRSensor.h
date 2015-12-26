/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

#include "ISensor.h"

class PIRSensor : public ISensor {
    public:
        PIRSensor (int pin);
        ~PIRSensor ();
        
        void Start ();
        void Stop ();        
        void DataArrivedCallback ();
        
        int                 pinNumber;
        mraa_gpio_context   pir;
};