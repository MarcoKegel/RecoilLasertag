# Bluetooth

Target is to understand the bluetooth protocol between the weapon and the smartphone


[Protocol see](https://wiki.lazerswarm.com/wiki/Recoil:Bluetooth_Protocol_Details)
[example implementation in javascript](https://github.com/DroopCat/Scope/blob/main/static/assets/lib/recoilweapon.js)
[gat dotnet lib](https://github.com/hashtagchris/DotNet-BlueZ)

# api

## Service “Generic Access”
GUID: 1800 
This is the standard GATT service that needs to be implemented.

### Characteristic “Device Name”. 
GUID: 2A00 
Attributes: Read-Write 
- The device name is an ASCII string concatenating the “SRG1_” prefix with the 16 characters representing the hex UUID of the device (the same UUID is also available in the ID characteristic of the Recoil service). E.g. SRG1_BF7EB8569758B65F

## Service “Device Information”
GUID: 180A
This is a standard GATT service. Apple devices running test programs such as “LightBlue” prefer to have this implemented, and the implementation is supplied with most BLE demos.

### Characteristic “Manufacturer name String”. 
GUID: 2A29 
Attributes: Read

## Service ”RecoilGun”
GUID: e6f59d10-8230-4a5c-b22f-c062b1d329e3

### Characteristic ”gun identity”
GUID: **e6f59d11**-8230-4a5c-b22f-c062b1d329e3 
Attributes: Read

### Characteristic ”Telemetry”
GUID: **e6f59d12**-8230-4a5c-b22f-c062b1d329e3 
Attributes: Read-Notify

| Name                 | Data Type    | Description                                                                                               | summed bytes |
| -------------------- | ------------ | --------------------------------------------------------------------------------------------------------- | ------------ |
| Pkt Cnt              | U4           | The counter of this packet.                                                                               | 0            |
| Cmd Cnt              | U4           | Latest command counter received from the app.                                                             | 1            |
| GunID                | U8           | The identifier for this gun. 0x01…0x10 is valid, 0 is invalid.                                            | 2            |
| Buttons              | U8           | Digital buttons from controller; one bit per button.                                                      | 3            |
| Pressed              | U4*6         | Number of times that buttons have been pressed (mod 16):                                                  | 6            |
| Voltage              | S16          | Battery voltage (in mV) This is formally a signed number, but of course a negative value is not expected. | 8            |
| IrEvents             | Struct {} *2 |                                                                                                           | 9            |
| WeaponAmmo           | U8           | Amount of ammo remaining for firing independently.                                                        | 10           |
| GunFlags             | U8           | Bit map                                                                                                   | 11           |
| Selected Weapon Type | U8           | Currently selected Weapon Type                                                                            | 12           |
| Reserved             | U8*3         | Reserved for future expansion                                                                             | 15           |


### Characteristic ”Control”
GUID: **e6f59d13**-8230-4a5c-b22f-c062b1d329e3 
Attributes: Read-Write

### Characteristic ”Config”
GUID: **e6f59d14**-8230-4a5c-b22f-c062b1d329e3
Attributes: Write

## Prototyping

### Using bluetoothctl [tutorial](https://www.linux-magazine.com/Issues/2017/197/Command-Line-bluetoothctl)
- find the local bt controller `bluetoothctl list`
- bluetoothctl select E8:48:B8:C8:20:00
- bluetoothctl scan on
- bluetoothctl devices
- bluetoothctl info EF:20:EC:C8:B7:2A


 ### read and write
```
btgatt-client -i hci0 -d EF:20:EC:C8:B7:2A
Connecting to device... Done
[GATT client]# Service Added - UUID: 00001801-0000-1000-8000-00805f9b34fb start: 0x000a end: 0x000a
[GATT client]# Service Added - UUID: 00001800-0000-1000-8000-00805f9b34fb start: 0x0001 end: 0x0009
[GATT client]# Service Added - UUID: e6f59d10-8230-4a5c-b22f-c062b1d329e3 start: 0x000b end: 0x0019
[GATT client]# Service Added - UUID: 0000180a-0000-1000-8000-00805f9b34fb start: 0x001a end: 0xffff
[GATT client]# GATT discovery procedures complete
[GATT client]#
service - start: 0x0001, end: 0x0009, type: primary, uuid: 00001800-0000-1000-8000-00805f9b34fb
          charac - start: 0x0002, value: 0x0003, props: 0x0a, ext_props: 0x0000, uuid: 00002a00-0000-1000-8000-00805f9b34fb
          charac - start: 0x0004, value: 0x0005, props: 0x02, ext_props: 0x0000, uuid: 00002a01-0000-1000-8000-00805f9b34fb
          charac - start: 0x0006, value: 0x0007, props: 0x02, ext_props: 0x0000, uuid: 00002a04-0000-1000-8000-00805f9b34fb
          charac - start: 0x0008, value: 0x0009, props: 0x02, ext_props: 0x0000, uuid: 00002aa6-0000-1000-8000-00805f9b34fb

service - start: 0x000a, end: 0x000a, type: primary, uuid: 00001801-0000-1000-8000-00805f9b34fb

service - start: 0x000b, end: 0x0019, type: primary, uuid: e6f59d10-8230-4a5c-b22f-c062b1d329e3
          charac - start: 0x000c, value: 0x000d, props: 0x12, ext_props: 0x0000, uuid: e6f59d11-8230-4a5c-b22f-c062b1d329e3
                  descr - handle: 0x000e, uuid: 00002902-0000-1000-8000-00805f9b34fb
                  descr - handle: 0x000f, uuid: 00002901-0000-1000-8000-00805f9b34fb
          charac - start: 0x0010, value: 0x0011, props: 0x10, ext_props: 0x0000, uuid: e6f59d12-8230-4a5c-b22f-c062b1d329e3
                  descr - handle: 0x0012, uuid: 00002902-0000-1000-8000-00805f9b34fb
                  descr - handle: 0x0013, uuid: 00002901-0000-1000-8000-00805f9b34fb
          charac - start: 0x0014, value: 0x0015, props: 0x0a, ext_props: 0x0000, uuid: e6f59d13-8230-4a5c-b22f-c062b1d329e3
                  descr - handle: 0x0016, uuid: 00002901-0000-1000-8000-00805f9b34fb
          charac - start: 0x0017, value: 0x0018, props: 0x0a, ext_props: 0x0000, uuid: e6f59d14-8230-4a5c-b22f-c062b1d329e3
                  descr - handle: 0x0019, uuid: 00002901-0000-1000-8000-00805f9b34fb

service - start: 0x001a, end: 0xffff, type: primary, uuid: 0000180a-0000-1000-8000-00805f9b34fb
          charac - start: 0x001b, value: 0x001c, props: 0x02, ext_props: 0x0000, uuid: 00002a29-0000-1000-8000-00805f9b34fb
```







## Devices
### RK45 1 

Device DC:EC:C8:B6:84:CC

### RK45 2
Device EF:20:EC:C8:B7:2A (random)
        Name: SRG1_2F55D6ACFB33ECF8
        Alias: SRG1_2F55D6ACFB33ECF8
        Paired: yes
        Bonded: yes
        Trusted: yes
        Blocked: no
        Connected: yes
        LegacyPairing: no
        UUID: Generic Access Profile    (00001800-0000-1000-8000-00805f9b34fb)
        UUID: Generic Attribute Profile (00001801-0000-1000-8000-00805f9b34fb)
        UUID: Device Information        (0000180a-0000-1000-8000-00805f9b34fb)
        UUID: Unknown                   (00009d10-0000-1000-8000-00805f9b34fb)
        UUID: Vendor specific           (e6f59d10-8230-4a5c-b22f-c062b1d329e3)
        AdvertisingFlags:
  06                                               .