/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

#include <iostream>
#include <string>

#include "IService.h"

#define STREAM_PATH       "/tmp/defender/mmal-camera/stream"

class FaceRecognitionService : public IService {
    public:
        FaceRecognitionService ();
        ~FaceRecognitionService ();
        
        void Continue ();
        void Pause ();
        void MainLoop ();
    
    private:
        pthread_t mainLoopThread;
};