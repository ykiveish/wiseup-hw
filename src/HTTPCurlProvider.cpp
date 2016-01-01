/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#include "HTTPCurlProvider.h"
 
using namespace std;

/*size_t
CurlDataArrivedCB (void *ptr, size_t size, size_t count, void *stream) {
	((std::string*)stream)->append((char*)ptr, 0, size*count);
	return size*count;
}*/

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
    // curl_global_init (CURL_GLOBAL_ALL);
	// m_HTTPRequest = curl_easy_init ();
}

void
HTTPCurlProvider::CloseProvider () {
    delete api;
    // Clean CURL
    // curl_easy_cleanup (m_HTTPRequest);
	// curl_global_cleanup ();
}

void
HTTPCurlProvider::SendData (REQIEST_TYPE type, void ** data) {
    // m_RequestData.str(std::string()); // Creaning the request buffer.
    
    SensorInfo* sensor = (SensorInfo*) data;
    
    switch (type) {
        case HTTP_GET:
            api->GET_UpdateSensor (sensor);
            /*m_RequestData << "http://" <<
                m_ServerPath <<                 // SERVER_PATH
                ":" << m_ServerPort <<          // SERVER_PORT
                "/api/set_sensor_value/" <<     // REST_METHOD
                m_UserKey <<                    // USER_KEY
                "/" << sensor->Address <<       // ADDRESS
                "/" << sensor->Type <<          // TYPE
                "/" << sensor->Data;            // DATA
            
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
            std::cout << m_RequestData.str() << std::endl; */
        break;
        case HTTP_POST:
        break;
    }
}

void
HTTPCurlProvider::RecieveData () {
    
}
