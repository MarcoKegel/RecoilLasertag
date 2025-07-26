#include <stdexcept>
#include "DeviceInformationService.h"

BLEUUID DeviceInformationService::serviceUUID = BLEUUID("0000180a-0000-1000-8000-00805f9b34fb");
BLEUUID DeviceInformationService::charUUID = BLEUUID("00002a29-0000-1000-8000-00805f9b34fb");

DeviceInformationService::DeviceInformationService(BLERemoteService *service)
{
  myService = service;
}

String DeviceInformationService::GetManufacturer()
{
  Log.traceln("DeviceInformationService::GetManufacturer");
  if (myService == nullptr) {
    Log.errorln("myService is nullptr!");
    return "";
  }
  auto characteristic = myService->getCharacteristic(charUUID);
  if (characteristic == nullptr)
  {
    Log.errorln("No Characteristic found for: %s" , String(charUUID.toString().c_str()));
    return "";
  }
  std::string value = characteristic->readValue();
  return String(value.c_str());
}