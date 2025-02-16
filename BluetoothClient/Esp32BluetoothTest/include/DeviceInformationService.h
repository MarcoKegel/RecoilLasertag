#ifndef DEVICE_INFORMATION_SERVICE_H
#define DEVICE_INFORMATION_SERVICE_H

#include <Arduino.h>
#include <BLEDevice.h>



class DeviceInformationService
{
public:
    DeviceInformationService(BLERemoteService* pRemoteService);
    
    String GetManufacturer();

    static const BLEUUID serviceUUID;
    static const BLEUUID charUUID;

private:
    BLERemoteService* myService;   
};


#endif // DEVICE_INFORMATION_SERVICE_H