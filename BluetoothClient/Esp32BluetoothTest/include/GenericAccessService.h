#ifndef GENERIC_ACCESS_SERVICE_H
#define GENERIC_ACCESS_SERVICE_H

#include <Arduino.h>
#include <ArduinoLog.h>
#include <BLEDevice.h>



class GenericAccessService
{
public:
    GenericAccessService(BLERemoteService* pRemoteService);
    
    String GetDeviceInfo();
    void SetDeviceInfo(String value);

    static BLEUUID serviceUUID;
    static BLEUUID charUUID;

private:
    BLERemoteService* myService;   
};


#endif // GENERIC_ACCESS_SERVICE_H