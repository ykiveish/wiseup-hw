/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#include <iostream>
#include <stdlib.h>
#include "mraa.h"
#include "DHTSensor.h"

#include <wiringPi.h>   // ARM GPIO API

#define MAXTIMINGS	85
 
using namespace std;

void * 
DHTDataThreadHandler (void * args) {
    DHTSensor * obj = (DHTSensor *) args;
    
    while (obj->sensorReading) {
        // Read sensors data (temperature and humidity).
        if (obj->read_dht11_dat ()) {
            // Check temperature sensor.
            obj->temperature->sensor.Data = obj->dht11_dat[2] + obj->dht11_dat[3] * ((1 / (floor (log10 (abs(obj->dht11_dat[3])))) + 1));
            if (obj->temperature->sensor.Data != obj->temperature->sensor.PrevData) {
                obj->temperature->sensor.PrevData = obj->temperature->sensor.Data;
                obj->temperature->SendData ();
            }
            
            // Check humidity sensor.
            obj->humidity->sensor.Data = obj->dht11_dat[0] + obj->dht11_dat[1] * ((1 / (floor (log10 (abs(obj->dht11_dat[1])))) + 1));
            if (obj->humidity->sensor.Data != obj->humidity->sensor.PrevData) {
                obj->humidity->sensor.PrevData = obj->humidity->sensor.Data;
                obj->humidity->SendData ();
            }
            
            usleep (obj->readInterval);
        } else {
            usleep (50000);
        }
    }
}

DHTSensor::DHTSensor (int pin, IProvider* provider) {
    pinNumber       = pin;
    wiringPiValid   = true;
    
    if (wiringPiSetup() == -1) {
        wiringPiValid = false;
    }
    
    temperature = new GenericSensor ();
    temperature->SetOutProvider (provider);
    temperature->SetInProvider (provider);
    temperature->SetSensorName ("Living Room Temperature");
    temperature->SetSensorType (TEMPERATURE);
    temperature->SetSensorAddress (12347);
    
    humidity = new GenericSensor ();
    humidity->SetOutProvider (provider);
    humidity->SetInProvider (provider);
    humidity->SetSensorName ("Living Room Humidity");
    humidity->SetSensorType (HUMIDITY);
    humidity->SetSensorAddress (12345);
}

DHTSensor::~DHTSensor () {
    Stop ();
    
    delete temperature;
    delete humidity;
}

void
DHTSensor::Start () {
    sensorReading = true;
    int error = pthread_create(&readDataThread, NULL, DHTDataThreadHandler, this);
    if (error) {
    }
}

void
DHTSensor::Stop () {
    sensorReading = false;
}

bool
DHTSensor::read_dht11_dat () {
	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		    = 0, i;
	float	f; /* fahrenheit */
 
	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
 
	/* pull pin down for 18 milliseconds */
    pinMode (pinNumber, OUTPUT);
	digitalWrite( pinNumber, LOW );
	delay( 18 );
	/* then pull it up for 40 microseconds */
	digitalWrite( pinNumber, HIGH );
	delayMicroseconds( 40 );
	/* prepare to read the pin */
	pinMode( pinNumber, INPUT );
 
	/* detect change and read data */
	for ( i = 0; i < MAXTIMINGS; i++ ) {
		counter = 0;
		while ( digitalRead( pinNumber ) == laststate ) {
			counter++;
			delayMicroseconds( 1 );
			if ( counter == 255 ) {
				break;
			}
		}
		laststate = digitalRead( pinNumber );
 
		if ( counter == 255 )
			break;
 
		/* ignore first 3 transitions */
		if ( (i >= 4) && (i % 2 == 0) ) {
			/* shove each bit into the storage bytes */
			dht11_dat[j / 8] <<= 1;
			if ( counter > 16 )
				dht11_dat[j / 8] |= 1;
			j++;
		}
	}
 
	/*
	 * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
	 * print it out if data is good
	 */
	if ( (j >= 40) &&
	     (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) ) {
		f = dht11_dat[2] * 9. / 5. + 32;
        // printf ("DHT DATA\n");
        return true;
	} else  {
        // printf ("DHT ERROR\n");
        return false;
	}
}