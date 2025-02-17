#include <stdexcept>

#include "BluetoothHelper.h"

BluetoothHelper::BluetoothHelper(BLEUUID advertisementId)
{
    Serial.print("BluetoothHelper ctor: ");
    myAdvertisementId = advertisementId;
    IsConnected = false;
}

BLERemoteService *BluetoothHelper::getService(BLEUUID serviceId)
{
    Serial.println("BluetoothHelper getService: ");
    if (IsConnected == false)
    {
        throw std::runtime_error("Missing connection.");
    }

    myClient = BLEDevice::createClient();
    myClient->connect(myDevice);
    myClient->setMTU(517); // TODO why is this needed ?
    
    auto service = myClient->getService(serviceId);
    if (service == nullptr)
    {
        auto message = "Failed to find our service UUID: " + serviceId.toString();

        Serial.println(message.c_str());
        myClient->disconnect();
        throw std::runtime_error(message);
    }
    return service;
}

void BluetoothHelper::Disconnect()
{
    Serial.println("BluetoothHelper Disconnect");
    myClient->disconnect();
    myClient = nullptr;
    //IsConnected = false; //TODO refactor or rename. IsConnected is not correct
}

void BluetoothHelper::onResult(BLEAdvertisedDevice advertisedDevice)
{
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(myAdvertisementId))
    {
        Serial.println("Found Recoil Controller");
        
        BLEDevice::getScan()->stop();
        
        Serial.println("Create advertisedDevice");
        myDevice = new BLEAdvertisedDevice(advertisedDevice);

        IsConnected = true;
    }
}
