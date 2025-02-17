#include "SkyRocket.h"
#include <stdexcept>

#include "DeviceInformationService.h"
#include "GenericAccessService.h"
#include "GunService.h"

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
    while (myBluetoothHelper->IsConnected == false)
    {
        Serial.println("Wait for Connection.");
        delay(5000);
    }
    auto message = DeviceInformationService(myBluetoothHelper->getService(DeviceInformationService::serviceUUID)).GetManufacturer();
    myBluetoothHelper->Disconnect();
    return message;
}

String SkyRocket::GetDeviceName()
{
    Serial.println("SkyRocket::GetDeviceName");
    while (myBluetoothHelper->IsConnected == false)
    {
        Serial.println("Wait for Connection.");
        delay(5000);
    }
    auto message = GenericAccessService(myBluetoothHelper->getService(GenericAccessService::serviceUUID)).GetDeviceInfo();
    myBluetoothHelper->Disconnect();

    return message;
}

String SkyRocket::GetGunIdentity()
{
    Serial.println("SkyRocket::GetGunIdentity");
    while (myBluetoothHelper->IsConnected == false)
    {
        Serial.println("Wait for Connection.");
        delay(5000);
    }
    auto message = GunService(myBluetoothHelper->getService(GunService::serviceUUID)).GetIdentity();
    myBluetoothHelper->Disconnect();

    return message;
}

String SkyRocket::GetTelemetry()
{
    Serial.println("SkyRocket::GetTelemetry");
    while (myBluetoothHelper->IsConnected == false)
    {
        Serial.println("Wait for Connection.");
        delay(5000);
    }
    auto message = GunService(myBluetoothHelper->getService(GunService::serviceUUID)).GetTelemetry();
    myBluetoothHelper->Disconnect();

    return message;
}

String SkyRocket::GetControl()
{
    Serial.println("SkyRocket::GetControl");
    while (myBluetoothHelper->IsConnected == false)
    {
        Serial.println("Wait for Connection.");
        delay(5000);
    }
    auto message = GunService(myBluetoothHelper->getService(GunService::serviceUUID)).GetControl();
    myBluetoothHelper->Disconnect();

    return message;
}

void SkyRocket::DisConnect()
{
    // myBluetoothHelper->Disconnect(); // TODO Some Kind of Cleanup of AdvirticedService and so on.
}

bool SkyRocket::IsConnected()
{
    return myBluetoothHelper->IsConnected;
}