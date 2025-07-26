#ifndef GUN_SERVICE_H
#define GUN_SERVICE_H

#include <Arduino.h>
#include <ArduinoLog.h>
#include <BLEDevice.h>

#include "BluetoothLogHelper.h"



class GunService
{
public:
    GunService(BLERemoteService* pRemoteService);
    
    String GetIdentity();

    String GetTelemetry();

    String GetControl();

    static  BLEUUID serviceUUID;
    static  BLEUUID identityCharUUID;
    static  BLEUUID telemetryCharUUID;
    static  BLEUUID controlCharUUID;
    static  BLEUUID configCharUUID;

private:
    BLERemoteService* myService;   
};


#endif // GUN_SERVICE_H