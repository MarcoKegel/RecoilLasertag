#include "SkyRocket.h"
#include <stdexcept>

#include "DeviceInformationService.h"
const BLEUUID SkyRocket::advertisedServiceUUID("00009d10-0000-1000-8000-00805f9b34fb");

SkyRocket::SkyRocket()
{
    myAdvertisedDevice = nullptr;
    myBluetoothHelper = new BluetoothHelper(advertisedServiceUUID);
}

void SkyRocket::Connect()
{
    BLEDevice::init("ESP32_C3_SkyRocked");
    BLEScan *pBLEScan = BLEDevice::getScan();
    Serial.println("[BLE] start scan.");
    pBLEScan->setAdvertisedDeviceCallbacks(myBluetoothHelper);
    pBLEScan->setInterval(1349);
    pBLEScan->setWindow(449);
    pBLEScan->setActiveScan(true);
    pBLEScan->start(5, false);
}

String SkyRocket::GetManufacturer()
{
    Serial.println("SkyRocket::GetManufacturer");
    while (myBluetoothHelper->IsConnected ==false)
    {
        Serial.println("Wait for Connection.");
        delay(5000);
    }
    auto message = DeviceInformationService(myBluetoothHelper->getService(DeviceInformationService::serviceUUID)).GetManufacturer();
    
    return message;
}

void SkyRocket::DisConnect()
{
    myBluetoothHelper->Disconnect();
}

bool SkyRocket::IsConnected()
{
    return myBluetoothHelper->IsConnected;
}