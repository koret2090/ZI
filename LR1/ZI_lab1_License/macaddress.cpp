#include "macaddress.h"

MacAddress::MacAddress()
{

}

char* MacAddress::getMac()
{
    IP_ADAPTER_INFO AdapterInfo[MAC_SIZE];       // информация об адаптерах
    DWORD dwBufLen = sizeof (AdapterInfo);       // кол-во байт в буффере

    DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);
    if (dwStatus != ERROR_SUCCESS)
    {
        return nullptr;
    }

    PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo; // информация о текущем адаптере
    BYTE *addr = pAdapterInfo->Address;

    char* address = new char[MAC_SIZE];
    std::snprintf(address, MAC_SIZE, "%02x%02x%02x%02x", *addr, (*addr+1), (*addr+2), (*addr+3));

    return address;
}
