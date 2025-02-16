#ifndef BLUETOOTH_HELPER_H
#define BLUETOOTH_HELPER_H

#include <Arduino.h>
#include <BLEDevice.h>

class BluetoothHelper : public BLEAdvertisedDeviceCallbacks
{
public:
    bool IsConnected;

    BluetoothHelper(BLEUUID advertisementId);
    
    BLERemoteService* getService(BLEUUID serviceId);
    void Disconnect();
    void onResult(BLEAdvertisedDevice advertisedDevice) override;

private:
   BLEAdvertisedDevice* myDevice;
   BLEClient* myClient;
   BLEUUID myAdvertisementId;

};

#endif // BLUETOOTH_HELPER_H