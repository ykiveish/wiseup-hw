/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#include "HTTPCurlProvider.h"
 
using namespace std;

HTTPCurlProvider::HTTPCurlProvider (std::string serverPath, std::string serverPort, std::string userKey) {
    m_UserKey    = userKey;
    m_ServerPath = serverPath;
    m_ServerPort = serverPort;
    InitiateProvider ();
}

HTTPCurlProvider::~HTTPCurlProvider () {
    CloseProvider ();
}

void
HTTPCurlProvider::InitiateProvider () {
    api = new RESTApi (m_ServerPath, m_ServerPort, m_UserKey);
}

void
HTTPCurlProvider::CloseProvider () {
    delete api;
}

void
HTTPCurlProvider::SendData (REQIEST_TYPE type, void ** data) {
    
    SensorInfo* sensor = (SensorInfo*) data;
    
    switch (type) {
        case HTTP_GET:
            api->GET_UpdateSensor (sensor);
        break;
        case HTTP_POST:
        break;
    }
}

void
HTTPCurlProvider::RecieveData () {
    
}
