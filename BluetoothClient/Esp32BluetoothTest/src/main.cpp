#include <memory>

#include <Arduino.h>
#include <BLEDevice.h>
#include "DeviceInformationService.h"
#include "SkyRocket.h"

// #include "BLEScan.h"

static SkyRocket *mySkyRocket;



void setup()
{
  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application…");
  mySkyRocket = new SkyRocket();

  BLEDevice::init("");
  BLEScan *pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(mySkyRocket);
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);

  mySkyRocket->Connect();
}

void loop()
{
}