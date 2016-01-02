/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

#include <iostream>
#include <string>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "IService.h"
#include "RaspiStill.h"

#define DEFENDER_PATH     "/tmp/defender"
#define MMAL_CAMERA_PATH  "/tmp/defender/mmal-camera"
#define PROCESSING_PATH   "/tmp/defender/mmal-camera/processing"
#define STREAM_PATH       "/tmp/defender/mmal-camera/stream"

class MMALCameraService : public IService {
    public:
        MMALCameraService ();
        ~MMALCameraService ();
        
        void Continue ();
        void Pause ();
        void MainLoop ();
        
        mmal_camera_context_t mmalCameraContext;
    
    private:
        pthread_t cameraThread;
        pthread_t mainLoopThread;
};
