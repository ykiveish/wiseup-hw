/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#include <iostream>
#include <stdlib.h>
#include "mraa.h"
#include "PIRSensor.h"
 
using namespace std;

void * 
dataThreadHandler (void * args) {
    PIRSensor * obj = (PIRSensor *) args;
    
    while (obj->sensorReading) {
        obj->sensor.Data = mraa_gpio_read (obj->pir);
        
        if (obj->sensor.Data != obj->sensor.PrevData) {
            obj->sensor.PrevData = obj->sensor.Data;
            obj->SendData ();
        }
        
        usleep (500000);
    }
    
    cout << "Exit - PIRSensor Thread" << endl;
}

PIRSensor::PIRSensor (int pin) {
    pinNumber = pin;
    pir = mraa_gpio_init(pinNumber);
    mraa_gpio_dir(pir, MRAA_GPIO_IN);
}

PIRSensor::~PIRSensor () {
    Stop ();
    mraa_gpio_close	(pir);
}

void
PIRSensor::DataArrivedCallback () {
    
}

void
PIRSensor::Start () {
    sensorReading = true;
    int error = pthread_create(&readDataThread, NULL, dataThreadHandler, this);
    if (error) {
    }
}

void
PIRSensor::Stop () {
    sensorReading = false;
}
