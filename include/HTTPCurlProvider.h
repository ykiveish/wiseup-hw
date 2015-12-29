/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

#include <iostream>
#include <string>
#include <sstream>      // stringstream
#include <curl/curl.h>  // HTTP Requests

#include "IProvider.h"
#include "GeneralTypes.h"

class HTTPCurlProvider : public IProvider {
    public:
        HTTPCurlProvider (std::string serverPath, std::string serverPort, std::string userKey);
        ~HTTPCurlProvider ();
        
        void InitiateProvider ();
        void CloseProvider ();
        void SendData (REQIEST_TYPE type, void ** data);
        void RecieveData ();
        
    private:
        std::string         m_UserKey;
        std::string         m_ServerPath;
        std::string         m_ServerPort;
        std::string 		m_ResponseData;
        std::stringstream   m_RequestData;
        CURLcode            m_HTTPResponse;
        CURL* 		        m_HTTPRequest;
};
