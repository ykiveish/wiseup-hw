/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

#include <sstream>
#include "IConnector.h"

class UDSConnector : public IConnector {
	public:
		UDSConnector (std::string name);
		~UDSConnector ();
		
        void SendRequest (ConnectorData data);
		void Listener ();
		
		std::stringstream 	socketPath;
		pthread_t 			requestListenerThread;
};
