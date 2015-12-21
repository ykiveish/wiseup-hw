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
#include "mraa.h"       // GPIO API

using namespace std;

const int       PIR_PIN     = 11;
const string    USER_KEY    = "85994f97-5fb4-2915-6ccf-98c3bf16f664";

bool isRunning = true;
mraa_gpio_context pir;

std::string 		responseData;
CURLcode            response;
std::stringstream   request;
CURL* 		        HTTPRequest;

void sig_handler (int signo);
size_t CurlDataArrivedCB (void *ptr, size_t size, size_t count, void *stream);

int
main (int argc, char **arg) {
    int pirData = 0;
    int pirDataPrev = pirData;
    
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
                std::cout << "Sending PIR data to the server ..." << std::endl;
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
