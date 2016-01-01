/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

#include <iostream>
#include <string>
#include <sstream>          // stringstream
#include <curl/curl.h>      // HTTP Requests
#include "GeneralTypes.h"   // SensorInfo

typedef void (*RESTApiDataArrived)(void ** data); 

class RESTApi {
    public:
        RESTApi (std::string serverPath, std::string serverPort, std::string userKey);
        ~RESTApi ();
        
        void SetDataArrivedCallback (RESTApiDataArrived callback);
        void GET_UpdateSensor (SensorInfo* sensor);
        
    private:
        std::string         m_UserKey;
        std::string         m_ServerPath;
        std::string         m_ServerPort;
        std::string 		m_ResponseData;
        std::stringstream   m_RequestData;
        CURLcode            m_HTTPResponse;
        CURL* 		        m_HTTPRequest;
        
        RESTApiDataArrived  m_DataArrivedCallback;
};
