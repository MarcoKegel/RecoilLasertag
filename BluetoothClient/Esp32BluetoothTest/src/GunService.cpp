#include <stdexcept>
#include "GunService.h"
#include "StringConverter.h"
#include <cstring>

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
    Log.errorln("No Characteristic found for: %s", String(identityCharUUID.toString().c_str()));
  }
  auto rawData = characteristic->readValue();

  auto parsed = parseFirmwareData(rawData);
  Log.infoln("parsed version %d", parsed.version);
  Log.infoln("parsed bl version %d", parsed.blVersion);
  Log.infoln("parsed crc 0x%08x", parsed.configCRC);
  Log.infoln("parsed model %d", parsed.gunModel);

  // Print padding as hex bytes
  Log.infoln("parsed padding %02x %02x %02x",
             parsed.padding[0], parsed.padding[1], parsed.padding[2]);

  // Print uuid as hex bytes
  Log.infoln("parsed uid %02x %02x %02x %02x %02x %02x %02x %02x",
             parsed.uuid[0], parsed.uuid[1], parsed.uuid[2], parsed.uuid[3],
             parsed.uuid[4], parsed.uuid[5], parsed.uuid[6], parsed.uuid[7]);

  return StringConverter::stringToHex(rawData).c_str();
}

/**
  GunIdentity info{};
 * Expected format (total 18 bytes):
 * - Version: 2 bytes (little endian)
 * - UUID: 8 bytes
 * - Gun Model: 1 byte
 * - Padding: 3 bytes
 * - Config CRC: 4 bytes (little endian)
 * - Bootloader Version: 2 bytes (little endian, currently not parsed)
 * Throws std::runtime_error if the data is too short for any field.
 */
GunIdentity GunService::parseFirmwareData(const std::string &data)
{
  Log.traceln("GunService::parseFirmwareData");

  GunIdentity info;
  int offset = 0;

  // Read Version (2 bytes, little endian)
  info.version = static_cast<uint8_t>(data[offset]) | (static_cast<uint8_t>(data[offset + 1]) << 8);
  offset += 2;

  // Read UUID (8 bytes)
  if (data.size() < offset + 8)
  {
    throw std::runtime_error("Firmware data too short for UUID");
  }
  // Read UUID (8 bytes)
  memcpy(info.uuid, data.data() + offset, 8);
  offset += 8;

  // Check if data is large enough for gun model (1 byte)
  if (data.size() < offset + 1)
  {
    throw std::runtime_error("Firmware data too short for gun model field");
  }
  // Read Gun Model (1 byte)
  info.gunModel = static_cast<uint8_t>(data[offset]);
  offset += 1;

  // Read Padding (3 bytes)
  if (data.size() < offset + 3)
  {
    throw std::runtime_error("Firmware data too short for padding");
  }
  // Read Padding (3 bytes)
  memcpy(info.padding, data.data() + offset, 3);
  offset += 3;

  // Check if data is large enough for config CRC (4 bytes)
  if (data.size() < offset + 4)
  {
    throw std::runtime_error("Firmware data too short for config CRC field");
  }
  // Read Config CRC (4 bytes, little endian)
  info.configCRC =
      static_cast<uint8_t>(data[offset]) |
      (static_cast<uint8_t>(data[offset + 1]) << 8) |
      (static_cast<uint8_t>(data[offset + 2]) << 16) |
      (static_cast<uint8_t>(data[offset + 3]) << 24);
  offset += 4;

  info.blVersion = static_cast<uint8_t>(data[offset]) | (static_cast<uint8_t>(data[offset + 1]) << 8);
  offset += 2;

  return info;
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
    Log.errorln("No Characteristic found for: %s", String(telemetryCharUUID.toString().c_str()));
  }

  BLH.LogInfo(characteristic);

  characteristic->registerForNotify([](BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify)
                                    { Log.infoln("Telemetry notification received: %s", StringConverter::stringToHex(std::string((char *)pData, length)).c_str()); });

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
    Log.errorln("No Characteristic found for: %s", String(controlCharUUID.toString().c_str()));
    return "";
  }
  BLH.LogInfo(characteristic);

  auto value = characteristic->readValue(); //todo characteristics are always 20 bytes ....

  Log.infoln("Read Value as Hex: %s", value);

  auto parsed = parseControlData(value);
  Log.infoln("Parsed PktCounter: %d", parsed.PktCounter);
  Log.infoln("Parsed CmdCounter: %d", parsed.CmdCounter);
  Log.infoln("Parsed GunID: %d", parsed.GunID);
  Log.infoln("Parsed IR_ack: %d", parsed.IR_ack);
  Log.infoln("Parsed Action: %d", parsed.Action);
  Log.infoln("Parsed WeaponAmmo: %d", parsed.WeaponAmmo);
  Log.infoln("Parsed WeaponType: %d", parsed.WeaponType);

   return characteristic->readValue().c_str();
}

GunControl GunService::parseControlData(const std::string &data)
{
  if (data.size() < 7)
  {
    Log.errorln("Control data too short: %zu bytes", data.size());
  }

  for (size_t i = 0; i < data.size(); ++i)
  {
    Log.traceln("data: index %d decimal '%d' hex '%X'", i, data[i], data[i]);
  }

  GunControl pkt;
  size_t offset = 0;

  // Byte 0: PktCounter (high nibble)
  uint8_t firstByte = (uint8_t)data[offset];
  pkt.PktCounter = (firstByte & 0xF0) >> 4;
  offset += 1;
  // Bytes 1-2: Action (U16, little endian)
  pkt.Action = (uint16_t)data[offset] | ((uint16_t)data[offset + 1] << 8);
  offset += 2;
  // Byte 3: GunID
  pkt.GunID = (uint8_t)data[offset];
  offset += 1;
  // Byte 4: WeaponType
  pkt.WeaponType = (uint8_t)data[offset];
  offset += 1;
  // Byte 5: WeaponAmmo
  pkt.WeaponAmmo = (uint8_t)data[offset];
  offset += 1;
  return pkt;
}
