#ifndef GENERIC_ACCESS_SERVICE_H
#define GENERIC_ACCESS_SERVICE_H

#include <Arduino.h>
#include <BLEDevice.h>



class GenericAccessService
{
public:
    GenericAccessService(BLERemoteService* pRemoteService);
    
    String GetDeviceInfo();
    void SetDeviceInfo(String value);

    static const BLEUUID serviceUUID;
    static const BLEUUID charUUID;

private:
    BLERemoteService* myService;   
};


#endif // GENERIC_ACCESS_SERVICE_H