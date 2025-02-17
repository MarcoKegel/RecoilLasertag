#ifndef SKYROCKET_H
#define SKYROCKET_H

#include <Arduino.h>
#include <BLEDevice.h>
#include "BluetoothHelper.h"


class SkyRocket 
{
public:
    SkyRocket();
    
    bool IsConnected();
    void Connect();
    void DisConnect();

    String GetManufacturer();
    String GetDeviceName();

    static const BLEUUID advertisedServiceUUID;

private:
      BLEDevice* myDevice;  
      BLEAdvertisedDevice* myAdvertisedDevice;
      BluetoothHelper* myBluetoothHelper;
};

#endif // SKYROCKET_H