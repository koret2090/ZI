#ifndef MACADDRESS_H
#define MACADDRESS_H

#include <winsock2.h>
#include <iphlpapi.h>
#include <iostream>

#define MAC_SIZE 20

class MacAddress
{
public:
    MacAddress();
    static char* getMac();
};




#endif // MACADDRESS_H
