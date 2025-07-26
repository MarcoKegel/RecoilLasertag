#ifndef BLUETOOTH_LOG_HELPER_H
#define BLUETOOTH_LOG_HELPER_H

#include <Arduino.h>
#include <ArduinoLog.h>
#include <BLEDevice.h>

class BluetoothLogHelper 
{
public:
    BluetoothLogHelper();
    ~BluetoothLogHelper();
    
    void LogInfo(BLERemoteCharacteristic *characteristic);

private:
};

extern BluetoothLogHelper BLH;

#endif // BLUETOOTH_HELPER_H
