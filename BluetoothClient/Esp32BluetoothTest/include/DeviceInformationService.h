#ifndef DEVICE_INFORMATION_SERVICE_H
#define DEVICE_INFORMATION_SERVICE_H

#include <Arduino.h>
#include <BLEDevice.h>
#include "SkyRocket.h"

static BLEUUID serviceUUID("0000180a-0000-1000-8000-00805f9b34fb");
static BLEUUID charUUID("00002a29-0000-1000-8000-00805f9b34fb");

class DeviceInformationService
{
public:
    DeviceInformationService(SkyRocket *);
    bool ConnectToServer();

    BLEClientCallbacks *ClientCallBack;

private:
    SkyRocket *mySkyRocket;
    BLERemoteCharacteristic *pRemoteCharacteristic;
    void DeviceInformationService::notifyCallback(
        BLERemoteCharacteristic *pBLERemoteCharacteristic,
        uint8_t *pData,
        size_t length,
        bool isNotify);
};

#endif // DEVICE_INFORMATION_SERVICE_H