#include "SkyRocket.h"






SkyRocket::SkyRocket()
{
}
void SkyRocket::onResult(BLEAdvertisedDevice advertisedDevice)
{
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(advertisedServiceUUID))
    {
        Serial.println("Found Rk45 Controller");
        BLEDevice::getScan()->stop();
        Device = new BLEAdvertisedDevice(advertisedDevice);
        doConnect = true;
        doScan = true;
    }
}

void SkyRocket::Connect()
{
    while(true)
    {
    if (doConnect == true)
    {
        if (connectToServer())
        {
            Serial.println("We are now connected to the BLE Server.");
        }
        else
        {
            Serial.println("We have failed to connect to the server; there is nothin more we will do.");
        }
        doConnect = false;
    }

    if (connected)
    {
        Serial.println("Read Value:");
        Serial.println(pRemoteCharacteristic->readValue().c_str());
    }
    else if (doScan)
    {
        BLEDevice::getScan()->start(0);
    }
    delay(1000);
    }
}

void SkyRocket::DisConnect()
{
    connected=false;
}

