/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

#include <string>
#include "IProvider.h"

class HTTPCurlProvider : public IProvider {
    public:
        HTTPCurlProvider (std::string serverPath);
        ~HTTPCurlProvider ();
        
        void InitiateProvider ();
        void CloseProvider ();
        void SendData ();
        void RecieveData ();
        
    private:
        std::string m_ServerPath;
};
