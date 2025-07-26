#ifndef BLUETOOTH_HELPER_H
#define BLUETOOTH_HELPER_H

#include <Arduino.h>
#include <ArduinoLog.h>
#include <BLEDevice.h> 
#include "BluetoothLogHelper.h"

class BluetoothHelper : public BLEAdvertisedDeviceCallbacks
{
public:
    BluetoothHelper(BLEUUID advertisementId);
    virtual ~BluetoothHelper();
    

    BLERemoteService* getService(BLEUUID serviceId);
    void Disconnect();
    void onResult(BLEAdvertisedDevice advertisedDevice) override;
    bool IsConnected();

private:
   BLEAdvertisedDevice* myDevice;
   BLEClient* myClient;
   BLEUUID myAdvertisementId;

};

#endif // BLUETOOTH_HELPER_H