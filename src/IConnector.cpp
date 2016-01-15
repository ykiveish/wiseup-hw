/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#include "IConnector.h"
 
using namespace std;

IConnector::~IConnector () {
    printf ("------- ~IConnector\n");
}

void
IConnector::StartListener () {
    IConnector_connectorWorking = true;
	Listener ();
}

void
IConnector::StopListener () {
	IConnector_connectorWorking = false;
}

void
IConnector::SendRequest (ConnectorData data) {
    
}

void
IConnector::RegisterRequestArrivedCallback (RequestDataArrivedCallback callback) {
    requestHandler = callback;
}
