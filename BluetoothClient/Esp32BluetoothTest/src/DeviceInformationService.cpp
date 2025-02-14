#include "DeviceInformationService.h"

class MyClientCallback : public BLEClientCallbacks
{
    MyClientCallback(SkyRocket *skyRocket)
    {
        mySkyRocket = skyRocket;
    }
    void onConnect(BLEClient *pclient)
    {
    }

    void onDisconnect(BLEClient *pclient)
    {
        mySkyRocket->DisConnect();
    }

    SkyRocket *mySkyRocket;
};

DeviceInformationService::DeviceInformationService(SkyRocket *skyRocket)
{
    mySkyRocket = skyRocket;
    ClientCallBack = new MyClientCallback(mySkyRocket);
}

bool DeviceInformationService::ConnectToServer()
{
  Serial.print("Forming a connection to ");
  Serial.println(mySkyRocket->Device->getAddress().toString().c_str());

  BLEClient *pClient = BLEDevice::createClient();
  Serial.println(" — Created client");

  pClient->setClientCallbacks(ClientCallBack);

  pClient->connect(mySkyRocket->Device);
  Serial.println(" — Connected to server");
  pClient->setMTU(517);
  BLERemoteService *pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr)
  {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" — Found our service");

  pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
  if (pRemoteCharacteristic == nullptr)
  {
    Serial.print("Failed to find our characteristic UUID: ");
    Serial.println(charUUID.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" — Found our characteristic");

  if (pRemoteCharacteristic->canRead())
  {
    std::string value = pRemoteCharacteristic->readValue();
    Serial.print("The characteristic value was: ");
    Serial.println(value.c_str());
  }

  if (pRemoteCharacteristic->canNotify())
    pRemoteCharacteristic->registerForNotify(notifyCallback);
  connected = true;
  return true;
}

void DeviceInformationService::notifyCallback(
    BLERemoteCharacteristic *pBLERemoteCharacteristic,
    uint8_t *pData,
    size_t length,
    bool isNotify)
{
  Serial.print("Notify callback for characteristic ");
  Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
  Serial.print(" of data length ");
  Serial.println(length);
  Serial.print("data: ");
  Serial.write(pData, length);
  Serial.println();
}