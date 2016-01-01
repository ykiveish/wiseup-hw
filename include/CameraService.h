/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

#include <iostream>
#include <string>

typedef enum {
    CAMERA_MMAL         = 1,
    CAMERA_V4L2         = 2
} CAMERA_TYPE;

class CameraService : public IService {
    public:
        CameraService (CAMERA_TYPE type, string devicePath);
        ~CameraService ();
        
        void MainLoop ();
    
    private:
        string m_DevicePath;
};
