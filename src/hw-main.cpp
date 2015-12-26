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

#include <sstream>      // stringstream
#include <curl/curl.h>  // HTTP Requests
#include <wiringPi.h>   // ARM GPIO API
#include "mraa.h"       // Inetl GPIO API

#include "HTTPCurlProvider.h"
#include "PIRSensor.h"

#define MAXTIMINGS	85

using namespace std;

const int       PIR_PIN     = 11;
const int       DHT_PIN     = 7;
const string    USER_KEY    = "85994f97-5fb4-2915-6ccf-98c3bf16f664";

int dht11_dat[5]        = { 0, 0, 0, 0, 0 };
int dht11_dat_prev[5]   = { 0, 0, 0, 0, 0 };

bool isRunning = true;
mraa_gpio_context pir;

std::string 		responseData;
CURLcode            response;
std::stringstream   request;
CURL* 		        HTTPRequest;

HTTPCurlProvider HttpProvider ("10.0.0.15:8080");

void sig_handler (int signo);
size_t CurlDataArrivedCB (void *ptr, size_t size, size_t count, void *stream);
bool read_dht11_dat ();

int
main (int argc, char **arg) {
    int pirData = 0;
    int pirDataPrev = pirData;
    
    if ( wiringPiSetup() == -1 )
		exit( 1 );
    
    HttpProvider.InitiateProvider ();
    
    PIRSensor* MovementSensor = new PIRSensor (PIR_PIN);
    MovementSensor->SetOutProvider (&HttpProvider);
    MovementSensor->SetInProvider (&HttpProvider);
    MovementSensor->SetSensorName ("Living Room Movement");
    MovementSensor->SetSensorAddress (12346);
    MovementSensor->Start ();
    
    pir = mraa_gpio_init(PIR_PIN);
    mraa_gpio_dir(pir, MRAA_GPIO_IN);
    
    curl_global_init(CURL_GLOBAL_ALL);
	HTTPRequest = curl_easy_init();
    
    signal (SIGINT, sig_handler);
    while (isRunning) {
        pirData = mraa_gpio_read (pir);
        
        if (pirData != pirDataPrev) {
            pirDataPrev = pirData;
            request.str(std::string()); // Creaning the request buffer.
            request << 	"http://10.0.0.15:8080/api/set_sensor_value/" << 
				USER_KEY << // USER_KEY
				"/12346" << // ADDRESS
				"/3/" <<    // TYPE
				pirData;    // DATA
            
            if (HTTPRequest) {
                // std::cout << "Sending PIR data to the server ..." << std::endl;
                std::cout << request.str() << std::endl;
                curl_easy_setopt (HTTPRequest, CURLOPT_URL, request.str().c_str());
                curl_easy_setopt (HTTPRequest, CURLOPT_WRITEFUNCTION, CurlDataArrivedCB);
                curl_easy_setopt (HTTPRequest, CURLOPT_WRITEDATA, &responseData);

                response = curl_easy_perform (HTTPRequest);

                if(response != CURLE_OK) {
                    std::cout << "CURL ERROR :: " << 
                    curl_easy_strerror(response) << std::endl;
                    return 1;
                }
            }
        }
        
        if (read_dht11_dat ()) {
            // Humidity sensor data
            if (abs (dht11_dat_prev[0] - dht11_dat[0]) > 2) {
                dht11_dat_prev[0] = dht11_dat[0];
                request.str(std::string()); // Creaning the request buffer.
                request << 	"http://10.0.0.15:8080/api/set_sensor_value/" << 
                    USER_KEY <<                             // USER_KEY
                    "/12345" <<                             // ADDRESS
                    "/2/" <<                                // TYPE
                    dht11_dat[0] << "." << dht11_dat[1];    // DATA
                
                if (HTTPRequest) {
                    // std::cout << "Sending PIR data to the server ..." << std::endl;
                    std::cout << request.str() << std::endl;
                    curl_easy_setopt (HTTPRequest, CURLOPT_URL, request.str().c_str());
                    curl_easy_setopt (HTTPRequest, CURLOPT_WRITEFUNCTION, CurlDataArrivedCB);
                    curl_easy_setopt (HTTPRequest, CURLOPT_WRITEDATA, &responseData);

                    response = curl_easy_perform (HTTPRequest);

                    if(response != CURLE_OK) {
                        std::cout << "CURL ERROR :: " << 
                        curl_easy_strerror(response) << std::endl;
                        return 1;
                    }
                }
            }
            
            // Temperature sensor data
            if (abs (dht11_dat_prev[2] - dht11_dat[2]) > 1) {
                dht11_dat_prev[2] = dht11_dat[2];
                request.str(std::string()); // Creaning the request buffer.
                request << 	"http://10.0.0.15:8080/api/set_sensor_value/" << 
                    USER_KEY <<                             // USER_KEY
                    "/12347" <<                             // ADDRESS
                    "/1/" <<                                // TYPE
                    dht11_dat[2] << "." << dht11_dat[3];    // DATA
                
                if (HTTPRequest) {
                    // std::cout << "Sending PIR data to the server ..." << std::endl;
                    std::cout << request.str() << std::endl;
                    curl_easy_setopt (HTTPRequest, CURLOPT_URL, request.str().c_str());
                    curl_easy_setopt (HTTPRequest, CURLOPT_WRITEFUNCTION, CurlDataArrivedCB);
                    curl_easy_setopt (HTTPRequest, CURLOPT_WRITEDATA, &responseData);

                    response = curl_easy_perform (HTTPRequest);

                    if(response != CURLE_OK) {
                        std::cout << "CURL ERROR :: " << 
                        curl_easy_strerror(response) << std::endl;
                        return 1;
                    }
                }
            }
        }
        
        usleep (500000);
    }
    
    // Clean MRAA
    mraa_gpio_close	(pir);
    
    // Clean CURL
    curl_easy_cleanup (HTTPRequest);
	curl_global_cleanup ();
    
    std::cout << std::endl << "Clean exit from application." << std::endl;
    return 0;
}

void
sig_handler (int signo) {
	if (signo == SIGINT) {
		isRunning = false;
	}
}

size_t
CurlDataArrivedCB (void *ptr, size_t size, size_t count, void *stream) {
	((std::string*)stream)->append((char*)ptr, 0, size*count);
	return size*count;
}

bool
read_dht11_dat () {
	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;
	float	f; /* fahrenheit */
 
	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
 
	/* pull pin down for 18 milliseconds */
	pinMode( DHT_PIN, OUTPUT );
	digitalWrite( DHT_PIN, LOW );
	delay( 18 );
	/* then pull it up for 40 microseconds */
	digitalWrite( DHT_PIN, HIGH );
	delayMicroseconds( 40 );
	/* prepare to read the pin */
	pinMode( DHT_PIN, INPUT );
 
	/* detect change and read data */
	for ( i = 0; i < MAXTIMINGS; i++ ) {
		counter = 0;
		while ( digitalRead( DHT_PIN ) == laststate ) {
			counter++;
			delayMicroseconds( 1 );
			if ( counter == 255 ) {
				break;
			}
		}
		laststate = digitalRead( DHT_PIN );
 
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
		// printf( "Humidity = %d.%d %% Temperature = %d.%d *C (%.1f *F)\n",
		//	dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f );
        return true;
	} else  {
		// printf( "Data not good, skip\n" );
        return false;
	}
}
