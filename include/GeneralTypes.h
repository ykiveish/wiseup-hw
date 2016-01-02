/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

#include <string>

typedef enum {
    TEMPERATURE         = 1,
    HUMIDITY            = 2,
    PIR                 = 3,
    LUMINANCE           = 4,
    LED                 = 5
} SENSOR_TYPE;

typedef struct {
    long long   Address;
    std::string Name;
    SENSOR_TYPE Type;
    double      Data;
    double      PrevData;
} SensorInfo;

typedef struct {
    uint8_t     Data[64];
} ConnectorData;
