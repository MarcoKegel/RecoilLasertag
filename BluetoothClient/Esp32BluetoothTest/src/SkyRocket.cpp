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

SkyRocket::~SkyRocket()
{
    myBluetoothHelper->Disconnect();
    delete myBluetoothHelper;
    myBluetoothHelper = nullptr;
}

void SkyRocket::Connect()
{
    BLEDevice::init("ESP32_C3_SkyRocket"); // Fixed typo
    BLEScan *pBLEScan = BLEDevice::getScan();
   Log.infoln("[BLE] start scan.");
    pBLEScan->setAdvertisedDeviceCallbacks(myBluetoothHelper);
    pBLEScan->setInterval(1349);
    pBLEScan->setWindow(449);
    pBLEScan->setActiveScan(true);
    pBLEScan->start(5, false);
    WaitForConnection(10000);
    pBLEScan->stop();
}

bool SkyRocket::WaitForConnection(unsigned long timeoutMs)
{
    unsigned long start = millis();
    while (!myBluetoothHelper->IsConnected())
    {
        if (millis() - start > timeoutMs)
        {
            Log.warningln("Connection timeout.");
            return false;
        }
        Log.infoln("Wait for Connection.");
        delay(500);
    }
    return true;
}

String SkyRocket::GetManufacturer()
{
    Log.traceln("SkyRocket::GetManufacturer");
    if (!WaitForConnection(10000))
    { // 10s timeout
        return "Connection failed";
    }
    auto service = myBluetoothHelper->getService(DeviceInformationService::serviceUUID);
    if (service == nullptr)
    {
       Log.errorln("DeviceInformationService service is nullptr!");
        return "";
    }
    auto message = DeviceInformationService(service).GetManufacturer();
    return message;
}

String SkyRocket::GetDeviceName()
{
    Log.traceln("SkyRocket::GetDeviceName");
    if (!WaitForConnection(10000))
    { // 10s timeout
        return "Connection failed";
    }
    auto service = myBluetoothHelper->getService(GenericAccessService::serviceUUID);
    if (service == nullptr)
    {
        Log.errorln("GenericAccessService service is nullptr!");
        return "";
    }
    auto message = GenericAccessService(service).GetDeviceInfo();
    return message;
}

String SkyRocket::GetGunIdentity()
{
     Log.traceln("SkyRocket::GetGunIdentity");
    if (!WaitForConnection(10000))
    { // 10s timeout
        return "Connection failed";
    }
    auto service = myBluetoothHelper->getService(GunService::serviceUUID);
    if (service == nullptr)
    {
       Log.errorln("GunService service is nullptr!");
        return "";
    }
    auto message = GunService(service).GetIdentity();
    return message;
}

String SkyRocket::GetTelemetry()
{
     Log.traceln("SkyRocket::GetTelemetry");
    if (!WaitForConnection(10000))
    { // 10s timeout
        return "Connection failed";
    }
    auto service = myBluetoothHelper->getService(GunService::serviceUUID);
    if (service == nullptr)
    {
        Log.errorln("GunService service is nullptr!");
        return "";
    }
    auto message = GunService(service).GetTelemetry();
    return message;
}

String SkyRocket::GetControl()
{
     Log.traceln("SkyRocket::GetControl");
    if (!WaitForConnection(10000))
    { // 10s timeout
        return "Connection failed";
    }
    auto service = myBluetoothHelper->getService(GunService::serviceUUID);
    if (service == nullptr)
    {
        Log.errorln("GunService service is nullptr!");
        return "";
    }
    auto message = GunService(service).GetControl();
    return message;
}

void SkyRocket::DisConnect()
{
    if (myBluetoothHelper != nullptr)
    {
        myBluetoothHelper->Disconnect(); // TODO Some Kind of Cleanup of AdvirticedService and so on.
    }
}

bool SkyRocket::IsConnected()
{
    return myBluetoothHelper->IsConnected();
}