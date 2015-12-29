/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>     // Capture signals

#include "HTTPCurlProvider.h"
#include "PIRSensor.h"
#include "DHTSensor.h"

using namespace std;

const int       PIR_PIN     = 11;
const int       DHT_PIN     = 7;
const string    USER_KEY    = "85994f97-5fb4-2915-6ccf-98c3bf16f664";

bool isRunning = true;

HTTPCurlProvider HttpProvider ("10.0.0.15", "8080", USER_KEY);

void sig_handler (int signo);

int
main (int argc, char **arg) {
    
    HttpProvider.InitiateProvider ();
    
    PIRSensor* MovementSensor = new PIRSensor (PIR_PIN);
    MovementSensor->SetOutProvider (&HttpProvider);
    MovementSensor->SetInProvider (&HttpProvider);
    MovementSensor->SetSensorName ("Living Room Movement");
    MovementSensor->SetSensorAddress (12346);
    MovementSensor->Start ();
    
    DHTSensor* TemperatureANDHumiditySensor = new DHTSensor (DHT_PIN, &HttpProvider);
    TemperatureANDHumiditySensor->SetReadInterval (5 * 1000000);
    TemperatureANDHumiditySensor->Start ();
    
    signal (SIGINT, sig_handler);
    while (isRunning) {
        usleep (500000);
    }
    
    MovementSensor->Stop ();
    TemperatureANDHumiditySensor->Stop ();
    usleep (500000);
    delete MovementSensor;
    delete TemperatureANDHumiditySensor;
    
    std::cout << std::endl << "Clean exit from application." << std::endl;
    return 0;
}

void
sig_handler (int signo) {
	if (signo == SIGINT) {
		isRunning = false;
	}
}
