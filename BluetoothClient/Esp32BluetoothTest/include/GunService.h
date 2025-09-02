#ifndef GUN_SERVICE_H
#define GUN_SERVICE_H

#include <Arduino.h>
#include <ArduinoLog.h>
#include <BLEDevice.h>

#include "BluetoothLogHelper.h"

struct GunIdentity {
    uint16_t version;        // Version (U16)
    uint8_t uuid[8];         // UUID (U8*8)
    uint8_t gunModel;        // GunModel (U8)
    uint8_t padding[3];      // Padding (U8*3)
    uint32_t configCRC;      // ConfigCRC (U32)
    uint16_t blVersion;      // Bootloader Version (U16)
};
struct GunControl {
    uint8_t PktCounter : 4;      // U4
    uint8_t CmdCounter : 4;      // U4
    uint8_t IR_ack;          // U8
    uint16_t Action;          // U16
    uint8_t GunID;            // U8
    uint8_t WeaponType;       // U8
    uint8_t WeaponAmmo;       // U8
};

class GunService
{
public:
    GunService(BLERemoteService* pRemoteService);
    
    String GetIdentity();

    String GetTelemetry();

    String GetControl();

    static  BLEUUID serviceUUID;
    static  BLEUUID identityCharUUID;
    static  BLEUUID telemetryCharUUID;
    static  BLEUUID controlCharUUID;
    static  BLEUUID configCharUUID;

private:
    GunIdentity parseFirmwareData(const std::string&);
    GunControl parseControlData(const std::string&);
    BLERemoteService* myService;   
};


#endif // GUN_SERVICE_H