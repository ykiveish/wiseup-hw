/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#include "ISensor.h"
 
using namespace std;

void
ISensor::SetOutProvider (IProvider* provider) {
    outProvider = provider;
}

void
ISensor::SetInProvider (IProvider* provider) {
    inProvider = provider;
}

void
ISensor::SetSensorName (std::string name) {
    sensor.Name = name;
}

void
ISensor::SetSensorAddress (long long address) {
    sensor.Address = address;
}

void
ISensor::SendData () {
    outProvider->SendData ();
}

void
ISensor::RecieveData () {
    inProvider->RecieveData ();
}
