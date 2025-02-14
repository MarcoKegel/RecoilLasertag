#ifndef SKYROCKET_H
#define SKYROCKET_H

#include <Arduino.h>
#include <BLEDevice.h>

static BLEUUID advertisedServiceUUID("00009d10-0000-1000-8000-00805f9b34fb");

class SkyRocket : public BLEAdvertisedDeviceCallbacks
{
public:
    SkyRocket();
    void onResult(BLEAdvertisedDevice advertisedDevice) override;
    void Connect();
    void DisConnect();
    BLEAdvertisedDevice *Device;

private:
    bool connectToServer();
    boolean doConnect = false;
    boolean connected = false;
    boolean doScan = false;
    
};

#endif // SKYROCKET_H