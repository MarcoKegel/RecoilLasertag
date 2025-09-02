#include <memory>
#include <ArduinoLog.h>
#include <Arduino.h>
#include <BLEDevice.h>
#include "SkyRocket.h"
#include "GunService.h"
#include <iostream>
#include <StringConverter.h>

void Try01()
{
  Serial.begin(115200);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial); // Set log level and output
  Log.infoln("Starting Arduino BLE Client application…");

  SkyRocket skyRocket;

  do
  {
    skyRocket.Connect();
    delay(5 * 1000);
  } while (skyRocket.IsConnected() == false);

  // Serial.printf("Manufacturar: %s",skyRocket.GetManufacturer().c_str()); // This does work.
  // Serial.println();

  // Serial.printf("DeviceName: %s",skyRocket.GetDeviceName().c_str()); // This return nothing, double check with some other app
  // Serial.println();
  // Serial.printf("Identity: %s",skyRocket.GetGunIdentity().c_str());  // works but need to refactored to return objects instead complicated string
  // Serial.println();

  // Serial.printf("Telemetry: %s",skyRocket.GetTelemetry().c_str()); // anonymos function which writes to LOG is implemented. Need to be replaced with a class/function. Check how a override with null may work (derregister).
  //  need to be refactored to provide an api to get an object with properties/structs
  // Serial.println();
  // delay(5 * 1000); // to get some logs from the notifier

  Serial.printf("Control: %s", skyRocket.GetControl().c_str()); // is not tested yet, but should work.
  Serial.println();

  skyRocket.DisConnect();
}

void Try02()
{
  Serial.begin(115200);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial); // Set log level and output
  Log.infoln("Starting Arduino BLE Client application…");

  auto bluetoothHelper = new BluetoothHelper(SkyRocket::advertisedServiceUUID);

  BLEDevice::init("ESP32_C3_SkyRocket"); // Fixed typo
  BLEScan *pBLEScan = BLEDevice::getScan();
  Log.infoln("[BLE] start scan.");
  pBLEScan->setAdvertisedDeviceCallbacks(bluetoothHelper);
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);
  while (bluetoothHelper->IsConnected() == false)
  {
    Log.infoln("Wait for Connection.");
    delay(1 * 1000);
  }

  pBLEScan->stop();

  auto telemetryCharacteristic = bluetoothHelper->getCharacteristic(GunService::serviceUUID, GunService::telemetryCharUUID);
  if (telemetryCharacteristic == nullptr)
  {
    Log.errorln("telemetryCharacteristic is nullptr!");
    return;
  }

  telemetryCharacteristic->registerForNotify([](BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify)
                                             {
    std::string strValue = std::string((char *)pData, length);
    Log.infoln("Telemetry Notify callback for characteristic %s of data length %d", pBLERemoteCharacteristic->getUUID().toString().c_str(), length);
    Log.infoln("%s", StringConverter::stringToBinary(strValue).c_str()); 
    });
}

void setup()
{
  Try02();
}

void loop()
{
}