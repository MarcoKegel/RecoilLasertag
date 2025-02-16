#include <stdexcept>
#include "DeviceInformationService.h"

const BLEUUID DeviceInformationService::serviceUUID = BLEUUID("0000180a-0000-1000-8000-00805f9b34fb");
const BLEUUID DeviceInformationService::charUUID = BLEUUID("00002a29-0000-1000-8000-00805f9b34fb");

DeviceInformationService::DeviceInformationService(BLERemoteService *service)
{
  myService = service;
}

String DeviceInformationService::GetManufacturer()
{
  Serial.println("DeviceInformationService::GetManufacturer");
  auto characteristic = myService->getCharacteristic(charUUID);
  if (characteristic == nullptr)
  {
    auto message = "No Characteristic found for: ";
    throw std::runtime_error(message);
  }
  return characteristic->readValue().c_str();
}