/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

#include <math.h>
#include "GenericSensor.h"

class DHTSensor : public ISensor {
    public:
        DHTSensor (int pin, IProvider* provider);
        ~DHTSensor ();
        
        void Start ();
        void Stop ();        
        bool read_dht11_dat ();
        
        int             pinNumber;
        bool            wiringPiValid;
        GenericSensor*  temperature;
        GenericSensor*  humidity;
        int dht11_dat[5];
};
