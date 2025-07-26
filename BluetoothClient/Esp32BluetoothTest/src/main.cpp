#include <memory>
#include <ArduinoLog.h>
#include <Arduino.h>
#include <BLEDevice.h>
#include "SkyRocket.h"
#include <iostream>

void setup()
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
  
  Serial.printf("Telemetry: %s",skyRocket.GetTelemetry().c_str()); // anonymos function which writes to LOG is implemented. Need to be replaced with a class/function. Check how a override with null may work (derregister).
  Serial.println();
  delay(15 * 1000); // to get some logs from the notifier


  // Serial.printf("Control: %s",skyRocket.GetControl().c_str()); // is not tested yet, but should work.
  // Serial.println();
  
  skyRocket.DisConnect();
}

void loop()
{
}