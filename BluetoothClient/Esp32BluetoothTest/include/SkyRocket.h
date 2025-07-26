#ifndef SKYROCKET_H
#define SKYROCKET_H

#include <Arduino.h>
#include <ArduinoLog.h>
#include <BLEDevice.h>
#include "BluetoothHelper.h"


class SkyRocket 
{
public:
    SkyRocket();
    ~SkyRocket();

    bool IsConnected();
    void Connect();
    void DisConnect();

    String GetManufacturer();
    String GetDeviceName();
    String GetGunIdentity();
    String GetTelemetry();
    String GetControl();

    static const BLEUUID advertisedServiceUUID;

private:
    bool WaitForConnection(unsigned long timeoutMs);

    BLEDevice* myDevice;  
    BLEAdvertisedDevice* myAdvertisedDevice;
    BluetoothHelper* myBluetoothHelper;
};

#endif // SKYROCKET_H