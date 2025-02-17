#include <stdexcept>
#include "GunService.h"
#include "StringConverter.h"

const BLEUUID GunService::serviceUUID = BLEUUID("e6f59d10-8230-4a5c-b22f-c062b1d329e3");
const BLEUUID GunService::identityCharUUID = BLEUUID("e6f59d11-8230-4a5c-b22f-c062b1d329e3");
const BLEUUID GunService::telemetryCharUUID = BLEUUID("e6f59d12-8230-4a5c-b22f-c062b1d329e3");
const BLEUUID GunService::controlCharUUID = BLEUUID("e6f59d13-8230-4a5c-b22f-c062b1d329e3");
const BLEUUID GunService::configCharUUID = BLEUUID("e6f59d14-8230-4a5c-b22f-c062b1d329e3");

GunService::GunService(BLERemoteService *service)
{
  myService = service;
}

String GunService::GetIdentity()
{
  Serial.println("GunService::GetIdentity");
  auto characteristic = myService->getCharacteristic(identityCharUUID);
  if (characteristic == nullptr)
  {
    auto message = "No Characteristic found for: ";
    throw std::runtime_error(message);
  }
  return StringConverter::stringToHex(characteristic->readValue()).c_str();
}

String GunService::GetTelemetry()
{
  Serial.println("GunService::GetTelemetry");
  auto characteristic = myService->getCharacteristic(telemetryCharUUID);
  if (characteristic == nullptr)
  {
    auto message = "No Characteristic found for: ";
    throw std::runtime_error(message);
  }

  if(characteristic->canRead()==false)
  {
    
    return "Telemetry can not read";
  }
  uint8_t *rawData = characteristic->readRawData();
  Serial.println("Telemetry: ");
  for (int i = 0; i < 15; i++)
  {
    Serial.printf("%02X ", rawData[i]);
  }
  Serial.println();

  return StringConverter::stringToBinary(characteristic->readValue()).c_str();
}

String GunService::GetControl()
{
  Serial.println("GunService::GetControl");
  auto characteristic = myService->getCharacteristic(controlCharUUID);
  if (characteristic == nullptr)
  {
    auto message = "No Characteristic found for: ";
    throw std::runtime_error(message);
  }
  if(characteristic->canRead()==false)
  {
    
    return "GetControl can not read";
  }
  return characteristic->readValue().c_str();
}
