/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#include <iostream>
#include "RESTApi.h"
 
using namespace std;

size_t
CurlDataArrivedCB (void *ptr, size_t size, size_t count, void *stream) {
	((std::string*)stream)->append((char*)ptr, 0, size*count);
	return size*count;
}

RESTApi::RESTApi (std::string serverPath, std::string serverPort, std::string userKey) {
    m_UserKey    = userKey;
    m_ServerPath = serverPath;
    m_ServerPort = serverPort;
    
    curl_global_init (CURL_GLOBAL_ALL);
	m_HTTPRequest = curl_easy_init ();
}

RESTApi::~RESTApi () {
    // Clean CURL
    curl_easy_cleanup (m_HTTPRequest);
	curl_global_cleanup ();
    printf ("------- ~RESTApi\n");
}

void
RESTApi::SetDataArrivedCallback (RESTApiDataArrived callback) {
    
}

void
RESTApi::GET_UpdateSensor (SensorInfo* sensor) {
    m_RequestData.str(std::string()); // Creaning the request buffer.
    
    m_RequestData << "http://" <<
        m_ServerPath <<                 // SERVER_PATH
        ":" << m_ServerPort <<          // SERVER_PORT
        "/api/set_sensor_value/" <<     // REST_METHOD
        m_UserKey <<                    // USER_KEY
        "/" << sensor->Address <<        // ADDRESS
        "/" << sensor->Type <<           // TYPE
        "/" << sensor->Data;             // DATA
    
    if (m_HTTPRequest) {
        curl_easy_setopt (m_HTTPRequest, CURLOPT_URL, m_RequestData.str().c_str());
        curl_easy_setopt (m_HTTPRequest, CURLOPT_WRITEFUNCTION, CurlDataArrivedCB);
        curl_easy_setopt (m_HTTPRequest, CURLOPT_WRITEDATA, &m_ResponseData);

        m_HTTPResponse = curl_easy_perform (m_HTTPRequest);

        if (m_HTTPResponse != CURLE_OK) {
            std::cout << "CURL ERROR :: " << 
            curl_easy_strerror(m_HTTPResponse) << std::endl;
        }
    }
    
    std::cout << m_RequestData.str() << std::endl;
}
