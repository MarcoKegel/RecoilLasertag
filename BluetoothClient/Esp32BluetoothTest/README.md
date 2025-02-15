
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