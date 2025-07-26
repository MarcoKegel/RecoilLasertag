#include <stdexcept>
#include "GunService.h"
#include "StringConverter.h"

BLEUUID GunService::serviceUUID = BLEUUID("e6f59d10-8230-4a5c-b22f-c062b1d329e3");
BLEUUID GunService::identityCharUUID = BLEUUID("e6f59d11-8230-4a5c-b22f-c062b1d329e3");
BLEUUID GunService::telemetryCharUUID = BLEUUID("e6f59d12-8230-4a5c-b22f-c062b1d329e3");
BLEUUID GunService::controlCharUUID = BLEUUID("e6f59d13-8230-4a5c-b22f-c062b1d329e3");
BLEUUID GunService::configCharUUID = BLEUUID("e6f59d14-8230-4a5c-b22f-c062b1d329e3");

GunService::GunService(BLERemoteService *service)
{
  myService = service;
}

String GunService::GetIdentity()
{
  Log.traceln("GunService::GetIdentity");
  if (myService == nullptr)
  {
    Log.errorln("Error: myService is nullptr!");
  }
  auto characteristic = myService->getCharacteristic(identityCharUUID);
  if (characteristic == nullptr)
  {
    Log.errorln("No Characteristic found for: %s" , String(identityCharUUID.toString().c_str()));
  }
  return StringConverter::stringToHex(characteristic->readValue()).c_str();
}

String GunService::GetTelemetry()
{
  Log.traceln("GunService::GetTelemetry");
  if (myService == nullptr)
  {
    Log.errorln("myService is nullptr!");
  }
  auto characteristic = myService->getCharacteristic(telemetryCharUUID);
  if (characteristic == nullptr)
  {
    Log.errorln("No Characteristic found for: %s" , String(telemetryCharUUID.toString().c_str()));
  }
  
  BLH.LogInfo(characteristic);

  characteristic->registerForNotify([](BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) 
  {
    Log.infoln("Telemetry notification received: %s", StringConverter::stringToHex(std::string((char*)pData, length)).c_str());    
  });

  return "Telemetry notifications registered";
}

String GunService::GetControl()
{
  Log.traceln("GunService::GetControl");
  if (myService == nullptr)
  {
    Log.errorln("myService is nullptr!");
  }
  auto characteristic = myService->getCharacteristic(controlCharUUID);
  if (characteristic == nullptr)
  {
    Log.errorln("No Characteristic found for: %s" ,String(controlCharUUID.toString().c_str()));
    return "";
  }
  if (characteristic->canRead() == false)
  {
    return "GetControl can not read";
  }
  return characteristic->readValue().c_str();
}
