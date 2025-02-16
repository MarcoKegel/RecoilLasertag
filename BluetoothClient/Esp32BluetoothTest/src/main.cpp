#include <memory>

#include <Arduino.h>
#include <BLEDevice.h>
#include "SkyRocket.h"
#include <iostream>

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application…");
  SkyRocket skyRocket;
  try
  {

    do
    {
      skyRocket.Connect();
      delay(5 * 1000);
    } while (skyRocket.IsConnected() == false);
    auto manu = skyRocket.GetManufacturer();

    Serial.println(manu.c_str());
  }
  catch (const std::exception &e)
  {

    std::cerr << e.what() << '\n';
  }
  skyRocket.DisConnect();
}

void loop()
{
}