#include <stdexcept>

#include "BluetoothHelper.h"

BluetoothHelper::BluetoothHelper(BLEUUID advertisementId)
{
    Log.traceln("BluetoothHelper ctor: ");
    myAdvertisementId = advertisementId;

    myClient = nullptr;
    myDevice = nullptr;
}

BluetoothHelper::~BluetoothHelper()
{
    bool IsConnected = false;
    if (myClient != nullptr)
    {
        myClient->disconnect();
        delete myClient;
        myClient = nullptr;
    }
    if (myDevice != nullptr)
    {
        delete myDevice;
        myDevice = nullptr;
    }
}

bool BluetoothHelper::IsConnected()
{
    Log.traceln("Device exists: %s", myDevice != nullptr ? "true" : "false");
    Log.traceln("Client exists: %s", myClient != nullptr ? "true" : "false");
    if (myClient != nullptr)
    {
        Log.traceln("Client connected: %s", myClient->isConnected() ? "true" : "false");
    }
    return (myDevice != nullptr);
}

BLERemoteService *BluetoothHelper::getService(BLEUUID serviceId)
{

    Log.traceln("BluetoothHelper getService: %s", serviceId.toString().c_str());
    if (myDevice == nullptr)
    {
        Log.errorln("myDevice is nullptr!");
        return nullptr;
    }
    Log.infoln("Use Device: %s\n", myDevice->getName().c_str());
    if (myClient == nullptr || myClient->isConnected() == false)
    {
        Log.traceln("Creating client.");
        myClient = BLEDevice::createClient();
        if (myClient == nullptr)
        {
            Log.errorln("Failed to create BLE client!");
            return nullptr;
        }
        myClient->connect(myDevice);
        Log.traceln("Client connected.");
        myClient->setMTU(517); // TODO why is this needed ?
    }

    while (myClient->isConnected() == false)
    {
        Log.infoln("Waiting for client to connect...");
        delay(500);
    }

    auto services = myClient->getServices();
    if (services == nullptr)
    {
        Log.errorln(" services is nullptr!");
        return nullptr;
    }
    for (auto it = services->begin(); it != services->end(); ++it)
    {
        Log.traceln("Service UUID: %s", it->second->getUUID().toString().c_str());
    }

    auto service = myClient->getService(serviceId);
    Log.traceln("Service created: %s\n", serviceId.toString().c_str());
    if (service == nullptr)
    {
        auto message = "Failed to find our service UUID: " + serviceId.toString();
        Log.errorln(message.c_str());
        return nullptr;
    }
    return service;
}
BLERemoteCharacteristic* BluetoothHelper::getCharacteristic(BLEUUID serviceId, BLEUUID characteristicId)
{
    auto service = getService(serviceId);
    if (service == nullptr)
    {
        Log.errorln("Service is nullptr!");
        return nullptr;
    }
    auto characteristic = service->getCharacteristic(characteristicId);
    if (characteristic == nullptr)
    {
        auto message = "Failed to find our characteristic UUID: " + characteristicId.toString();
        Log.errorln(message.c_str());
        return nullptr;
    }
    return characteristic;
}
void BluetoothHelper::Disconnect()
{
    Log.traceln("BluetoothHelper Disconnect");
    if (myClient != nullptr)
    {
        myClient->disconnect();
    }
    // IsConnected = false; //TODO refactor or rename. IsConnected is not correct
}

void BluetoothHelper::onResult(BLEAdvertisedDevice advertisedDevice)
{
    Log.info("BLE Advertised Device found: ");
    Log.infoln(advertisedDevice.toString().c_str());

    if (advertisedDevice.haveServiceUUID() &&
        advertisedDevice.isAdvertisingService(myAdvertisementId))
    {
        Log.infoln("Found Recoil Controller");

        BLEDevice::getScan()->stop();

        Log.traceln("Create advertisedDevice");
        myDevice = new BLEAdvertisedDevice(advertisedDevice);
    }
}
