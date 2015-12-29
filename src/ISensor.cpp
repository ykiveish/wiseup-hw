/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#include "ISensor.h"
 
using namespace std;

ISensor::ISensor () {
    readInterval = 1000000;
}

ISensor::~ISensor () {
    
}

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
ISensor::SetSensorType (SENSOR_TYPE type) {
    sensor.Type = type;
}

void
ISensor::SetReadInterval (unsigned int interval) {
    readInterval = interval;
}

void
ISensor::SendData () {
    outProvider->SendData (HTTP_GET, (void **)&sensor);
}

void
ISensor::RecieveData () {
    inProvider->RecieveData ();
}

void
ISensor::DataArrivedCallback () {
    
}

void
ISensor::Start () {
    
}

void
ISensor::Stop () {
    
}
