/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#include <iostream>
#include <unistd.h>
#include <cstring>
#include "FaceRecognitionService.h"
#include "UDSConnector.h"
 
using namespace std;

void * 
MainLoopFaceRecognitionServiceThreadHandler (void * args) {
    FaceRecognitionService * obj = (FaceRecognitionService *) args;
    
    while (obj->IService_serviceWorking) {
        usleep (100);
    }
    
    obj->out->StopListener();
    obj->in->StopListener();
}

void
__newFrameArrived (void * data) {
    ConnectorData* receivedData = (ConnectorData*)data;
    long long frameNumber = 0;
    memcpy (&frameNumber, receivedData->Data, 8);
    printf ("__newFrameArrived - %lld\n", frameNumber);
}

FaceRecognitionService::FaceRecognitionService () {
    out = new UDSConnector ("FaceRecognitionServiceOUT");
    in  = new UDSConnector ("FaceRecognitionServiceIN");
    
    in->RegisterRequestArrivedCallback (__newFrameArrived);
    in->StartListener();
}

FaceRecognitionService::~FaceRecognitionService () {
    printf ("------- ~FaceRecognitionService\n");
    
    delete out;
    delete in;
}

void
FaceRecognitionService::Continue () {
    
}

void
FaceRecognitionService::Pause () {
    
}

void
FaceRecognitionService::MainLoop () {
    int error = pthread_create(&mainLoopThread, NULL, MainLoopFaceRecognitionServiceThreadHandler, this);
    if (error) {
        // TODO - Clean objects.
        IService_serviceWorking = false;
    }
}