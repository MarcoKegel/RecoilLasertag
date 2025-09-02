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

  auto service = bluetoothHelper->getService(GunService::serviceUUID);
  if (service == nullptr)
  {
    Log.errorln("gun service is nullptr!");
    return;
  }

  auto telemetryCharacteristic = service->getCharacteristic(GunService::telemetryCharUUID);
  if (telemetryCharacteristic == nullptr)
  {
    Log.errorln("telemetryCharacteristic is nullptr!");
    return;
  }

  telemetryCharacteristic->registerForNotify([](BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify)
                                             {
    std::string strValue = std::string((char *)pData, length);
    Log.infoln("Telemetry Notify callback for characteristic %s of data length %d", pBLERemoteCharacteristic->getUUID().toString().c_str(), length);
    Log.infoln("%s", StringConverter::stringToBinary(strValue).c_str()); });

  auto controlCharacteristic = service->getCharacteristic(GunService::controlCharUUID);
  if (controlCharacteristic == nullptr)
  {
    Log.errorln("controlCharacteristic is nullptr!");
    return;
  }

  uint8_t init[20] = {0x0, 0x0, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  controlCharacteristic->writeValue(init, 20, false); // init
  Log.infoln("Init sent");

  uint8_t shoot[20] = {0x00, 0x00, 0x01, 0x00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  controlCharacteristic->writeValue(shoot, 20, false); // shoot
  Log.infoln("Shoot sent");

    uint8_t poweroff[20] = {0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  controlCharacteristic->writeValue(poweroff, 20, false); // shoot
  Log.infoln("Poweroff sent");

  // The write values have no effect - why

  delay(5 * 1000); // to get some logs from the notifier
  bluetoothHelper->Disconnect();
  Log.infoln("DONE");
}

void setup()
{
  Try02();
}

void loop()
{
}