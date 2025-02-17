
**Bluetooth**
```plantuml

class BLERemoteCharacteristic
{
    bool canRead()
    string readValue()

    bool canWrite()
    void writeValue(string)

    bool canNotify()
    void registerForNotify(callback)

}

class BLERemoteService
{
    BLERemoteCharacteristic getCharacteristic(UUID id)
}

class BLEClient
{
    void setClientCallbacks(BLEClientCallbacks)
    void connect (BLEAdvertisedDevice)
    void disconnect()
    BLERemoteService getService(UUID) 

}

class BLEAdvertisedDevice{}
class BLEAdvertisedDeviceCallbacks
{
    virtual void onResult(BLEAdvertisedDevice)

}

class BLEScan
{
void setAdvertisedDeviceCallbacks(BLEAdvertisedDeviceCallbacks)
}
class BLEDevice
{
    static void Init(string)
    static BLEScan getScan()    
}

BLEDevice -d-> BLEScan: create
BLEScan -d-> BLEAdvertisedDeviceCallbacks : use
BLEAdvertisedDeviceCallbacks -d-> BLEAdvertisedDevice : create
BLEAdvertisedDevice -d-> BLEClient: create
BLEClient -d->  BLERemoteService:create
BLERemoteService -d-> BLERemoteCharacteristic: create



```

Sequence 

```plantuml

main -> BLEDevice: init
main -> BLEDevice: getScan()
BLEDevice -> BLEScan : create
BLEScan -> BLEAdvertisedDeviceCallbacks:

main -> BLEAdvertisedDeviceCallbacks: create
main -> BLEScan: setAdvertisedDeviceCallbacks

BLEScan --> BLEAdvertisedDeviceCallbacks: onResult
BLEAdvertisedDeviceCallbacks ->BLEAdvertisedDeviceCallbacks:onResult
BLEAdvertisedDeviceCallbacks -> BLEAdvertisedDevice: create
BLEAdvertisedDeviceCallbacks -> BLEClient:connect


BLEAdvertisedDeviceCallbacks -> BLEClient:GetService
BLEClient -> BLERemoteService:Create
BLEClient <- BLERemoteService:return
BLEAdvertisedDeviceCallbacks <- BLEClient:Returns remote service
```


**SkyRocket**
```plantuml

class SkyRocket
{
    void Connect ()
    DeviceInformationService GetDeviceInformation();

}

class DeviceInformationService
{
    string GetManufacturer ();
}

class GenericAccessService
{
    string GetDeviceName();
    void SetDeviceName(string name);    
}

class RecoilGunService
{
    string GetId();
    string GetTelemetry();

    string GetControl();
    void SetControl(string value);

    void SetConfig(string value);
}
```

## Example Parsing from ChatGpt
**Parsing**
```cpp
#include <cstdint>
#include <cstring>

struct IrEvent {
    uint16_t rawData;

    uint8_t getShotCounter() const { return (rawData >> 10) & 0x3F; }  // Bits 15-10
    uint8_t getWeaponType() const { return (rawData >> 6) & 0x0F; }   // Bits 9-6
    uint8_t getShooterID() const { return (rawData >> 6) & 0x0F; }    // Bits 9-6
    uint8_t getWeaponID() const { return (rawData >> 6) & 0x0F; }     // Bits 9-6
    uint8_t getShotCounterWrap() const { return (rawData >> 3) & 0x07; }  // Bits 5-3
    uint8_t getRounds() const { return ((rawData >> 3) & 0x07) * 4 + 4; } // Rounds formula
    uint8_t getGrenadeID() const { return (rawData >> 6) & 0x3F; }     // 6-bit hash
    uint8_t getGrenadeRandom() const { return (rawData >> 2) & 0x0F; } // 4-bit random
    uint8_t getGrenadeState() const { return rawData & 0x03; }         // 2-bit state
};

struct GunPacket {
    uint32_t pktCnt;       // Offset: 0
    uint32_t cmdCnt;       // Offset: 1
    uint8_t gunID;         // Offset: 2
    uint8_t buttons;       // Offset: 3
    uint8_t pressed[6];    // Offset: 6
    int16_t voltage;       // Offset: 8 (Signed 16-bit)
    IrEvent irEvents[2];   // Offset: 9 (Struct *2)
    uint8_t weaponAmmo;    // Offset: 10
    uint8_t gunFlags;      // Offset: 11
    uint8_t selectedWeapon;// Offset: 12
    uint8_t reserved[3];   // Offset: 15 (Future expansion)

    void parse(const uint8_t* pData) {
        pktCnt = pData[0];
        cmdCnt = pData[1];
        gunID = pData[2];
        buttons = pData[3];
        memcpy(pressed, &pData[6], 6);
        voltage = static_cast<int16_t>((pData[8] << 8) | pData[9]);
        irEvents[0].rawData = (pData[9] << 8) | pData[10];
        irEvents[1].rawData = (pData[11] << 8) | pData[12];
        weaponAmmo = pData[10];
        gunFlags = pData[11];
        selectedWeapon = pData[12];
        memcpy(reserved, &pData[15], 3);
    }
};
```

**Using**

```cpp
#include <iostream>

int main() {
    uint8_t rawData[18] = {0};  // Example input data
    GunPacket packet;
    packet.parse(rawData);

    std::cout << "Packet Count: " << packet.pktCnt << std::endl;
    std::cout << "Command Count: " << packet.cmdCnt << std::endl;
    std::cout << "Gun ID: " << (int)packet.gunID << std::endl;
    std::cout << "Voltage: " << packet.voltage << " mV" << std::endl;
    std::cout << "Weapon Ammo: " << (int)packet.weaponAmmo << std::endl;
    std::cout << "Shot Counter: " << (int)packet.irEvents[0].getShotCounter() << std::endl;

    return 0;
}
```