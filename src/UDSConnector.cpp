/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#include "IConnector.h"
#include "UDSConnector.h"
#include "uipc.h"
 
using namespace std;

void *
ListenerHandler (void * args) {
	UDSConnector * obj = (UDSConnector *) args;
    int  client = -1;
    char msg[256];
	
	WiseIPC *ipcInput = NULL;
    try {
        ipcInput = new WiseIPC (obj->socketPath.str());
        ipcInput->setServer ();

        while (obj->IConnector_connectorWorking) {
            client = ipcInput->listenIPC ();
            ipcInput->setBuffer ((uint8_t *)&msg);
            ipcInput->readMsg (client, sizeof (msg));
            obj->requestHandler (msg);
		}
	} catch (...) {
        std::cout << "[IPC] Default error ..." << std::endl;
    }

    delete ipcInput;
}

UDSConnector::UDSConnector (std::string name) {
	socketPath << "/tmp/defender/" << name;
	
}

UDSConnector::~UDSConnector () {
	printf ("------- ~UDSConnector\n");
}

void
UDSConnector::SendRequest (ConnectorData data) {
    WiseIPC *ipcOutput = new WiseIPC (socketPath.str());
    ipcOutput->setClient ();
    ipcOutput->setBuffer ((uint8_t *)data.Data);
    ipcOutput->sendMsg (8);
    
    delete ipcOutput;
}

void
UDSConnector::Listener () {
	int error = pthread_create(&requestListenerThread, NULL, ListenerHandler, this);
    if (error) {
    }
}
