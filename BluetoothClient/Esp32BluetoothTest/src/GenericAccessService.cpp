#include <stdexcept>
#include "GenericAccessService.h"
#include <BluetoothLogHelper.h>

BLEUUID GenericAccessService::serviceUUID = BLEUUID("00001800-0000-1000-8000-00805f9b34fb");
BLEUUID GenericAccessService::charUUID = BLEUUID("00002A00-0000-1000-8000-00805F9B34FB");

GenericAccessService::GenericAccessService(BLERemoteService *service)
{
  myService = service;
}

String GenericAccessService::GetDeviceInfo()
{
  Serial.println("GenericAccessService::GetDeviceInfo");
  if (myService == nullptr)
  {
    Log.errorln("myService is nullptr!");
  }
  auto characteristic = myService->getCharacteristic(charUUID);
  if (characteristic == nullptr)
  {
    Log.errorln("Characteristic found for: %s", String(charUUID.toString().c_str()));
  }

  BLH.LogInfo(characteristic);

  Log.traceln("GenericAccessService GetDeviceInfo raw: %s", characteristic->readRawData());

  return "nothing to see here";
}