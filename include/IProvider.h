/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#pragma once

class IProvider {
    public:
        virtual void InitiateProvider   () = 0;
        virtual void CloseProvider      () = 0;
        virtual void SendData           () = 0;
        virtual void RecieveData        () = 0;
};
