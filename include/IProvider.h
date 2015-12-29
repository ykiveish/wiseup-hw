/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

typedef enum {
    HTTP_GET        = 0,
    HTTP_POST       = 1
} REQIEST_TYPE;

class IProvider {
    public:
        virtual void InitiateProvider   () = 0;
        virtual void CloseProvider      () = 0;
        virtual void SendData           (REQIEST_TYPE type, void ** data) = 0;
        virtual void RecieveData        () = 0;
};
