/*
 * Author: Yevgeniy Kiveisha <lodmilak@gmail.com>
 * Copyright (c) 2013 Wiseup.
 */

#include "IService.h"
 
using namespace std;

void
IService::Start () {
    // TODO - Start all IConnectors objects
    IService_serviceWorking = true;
    MainLoop ();
}

void
IService::Stop () {
    IService_serviceWorking = false;
    // TODO - clean all IConnectors objects
}
