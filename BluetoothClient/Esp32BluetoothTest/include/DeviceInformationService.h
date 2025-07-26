#ifndef DEVICE_INFORMATION_SERVICE_H
#define DEVICE_INFORMATION_SERVICE_H

#include <Arduino.h>
#include <ArduinoLog.h>
#include <BLEDevice.h>



class DeviceInformationService
{
public:
    DeviceInformationService(BLERemoteService* pRemoteService);
    
    String GetManufacturer();

    static BLEUUID serviceUUID;
    static BLEUUID charUUID;

private:
    BLERemoteService* myService;   
};


#endif // DEVICE_INFORMATION_SERVICE_H