#ifndef GUN_SERVICE_H
#define GUN_SERVICE_H

#include <Arduino.h>
#include <BLEDevice.h>



class GunService
{
public:
    GunService(BLERemoteService* pRemoteService);
    
    String GetIdentity();

    String GetTelemetry();

    String GetControl();

    static const BLEUUID serviceUUID;
    static const BLEUUID identityCharUUID;
    static const BLEUUID telemetryCharUUID;
    static const BLEUUID controlCharUUID;
    static const BLEUUID configCharUUID;

private:
    BLERemoteService* myService;   
};


#endif // GUN_SERVICE_H