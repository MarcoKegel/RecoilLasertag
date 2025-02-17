#include <stdexcept>
#include "GenericAccessService.h"

const BLEUUID GenericAccessService::serviceUUID = BLEUUID("00001800-0000-1000-8000-00805f9b34fb");
const BLEUUID GenericAccessService::charUUID =    BLEUUID("00002a00-0000-1000-8000-00805f9b34fb");

GenericAccessService::GenericAccessService(BLERemoteService *service)
{
  myService = service;
}

String GenericAccessService::GetDeviceInfo()
{
  Serial.println("DeviceInformationService::GetDeviceInfo");
  auto characteristic = myService->getCharacteristic(charUUID);
  if (characteristic == nullptr)
  {
    auto message = "No Characteristic found for: ";
    throw std::runtime_error(message);
  }
  return characteristic->readValue().c_str();
}