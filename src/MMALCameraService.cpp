/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#include <iostream>
#include <unistd.h>
#include <cstring>
#include "MMALCameraService.h"
#include "UDSConnector.h"
 
using namespace std;

void * 
MMALCameraThreadHandler (void * args) {
    const char *my_argv[15] = { "args", "-w", "1024", "-h", "768", "-q", "5", "-o", STREAM_PATH"/frame.jpg", "-tl", "500", "-t", "9999999", "-th", "0:0:0" };
	int         my_argc = 15;
    
    MMALCameraService * obj = (MMALCameraService *) args;
    mmal_camera (my_argc, my_argv, &(obj->mmalCameraContext));
}

void * 
MainLoopMMALCameraServiceThreadHandler (void * args) {
    MMALCameraService * obj = (MMALCameraService *) args;
    
    while (obj->IService_serviceWorking) {
        usleep (100);
    }
    
    obj->mmalCameraContext.running = 0x0;
}

void __cameraFrame (long long frameNumber, void * args) {
    MMALCameraService * obj = (MMALCameraService *) args;
    
    ConnectorData data;
    memcpy (data.Data, &frameNumber, sizeof (long long));
    obj->out->SendRequest (data);
}

MMALCameraService::MMALCameraService () {
    mmalCameraContext.running   = 0x1;
    mmalCameraContext.args      = this;
    mmalCameraContext.callback  = __cameraFrame;
    
    umask(0);
    struct stat st = {0};
    if (stat (DEFENDER_PATH, &st) == -1) {
        mkdir (DEFENDER_PATH     ,0777);
        mkdir (MMAL_CAMERA_PATH  ,0777);
        mkdir (STREAM_PATH       ,0777);
    }
    
    out = new UDSConnector ("FaceRecognitionServiceIN");
    in  = new UDSConnector ("MMALCameraServiceIN");
}

MMALCameraService::~MMALCameraService () {
    IService_serviceWorking = false;
    mmalCameraContext.running = 0x0;
    printf ("------- ~MMALCameraService\n");
    
    delete out;
    delete in;
}

void
MMALCameraService::Continue () {
    
}

void
MMALCameraService::Pause () {
    
}

/*
 * Will start when Start method will be executed.
 */
void
MMALCameraService::MainLoop () {
    int error = pthread_create(&cameraThread, NULL, MMALCameraThreadHandler, this);
    if (error) {
        IService_serviceWorking = false;
    }
    
    error = pthread_create(&mainLoopThread, NULL, MainLoopMMALCameraServiceThreadHandler, this);
    if (error) {
        // TODO - Clean objects.
        IService_serviceWorking = false;
    }
}