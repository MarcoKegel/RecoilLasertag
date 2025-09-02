## Bluetooth Command Action Sequence

Here is the actual action sequence of Bluetooth commands sent by your code, including the payload values (where available), based on the logic in your `recoilweapon.js` class:

### 1. Connect to Device
- **SERVICE_UID:** `e6f59d10-8230-4a5c-b22f-c062b1d329e3`
- **CHARACTERISTICS:** All three (config, control, telemetry)
- **PAYLOAD:** None (just connection and characteristic discovery)
- **Purpose:** Establish BLE connection and get handles.

### 2. Start Telemetry Notifications
- **SERVICE_UID:** `e6f59d10-8230-4a5c-b22f-c062b1d329e3`
- **CHARACTERISTIC_UID:** `e6f59d12-8230-4a5c-b22f-c062b1d329e3` (Telemetry)
- **PAYLOAD:** None (just start notifications)
- **Purpose:** Begin receiving telemetry packets (button states, ammo, IR events).

### 3. Send Control Packet (Default/Init)
- **SERVICE_UID:** `e6f59d10-8230-4a5c-b22f-c062b1d329e3`
- **CHARACTERISTIC_UID:** `e6f59d13-8230-4a5c-b22f-c062b1d329e3` (Control)
- **PAYLOAD:** `0x0000` (default action, used for initialization and updating settings)
- **Purpose:** Initialize gun state, update settings, or set gun ID.

### 4. Send Control Packet (Shoot)
- **SERVICE_UID:** `e6f59d10-8230-4a5c-b22f-c062b1d329e3`
- **CHARACTERISTIC_UID:** `e6f59d13-8230-4a5c-b22f-c062b1d329e3` (Control)
- **PAYLOAD:** `0x0001` (shoot action)
- **Purpose:** Trigger the gun to shoot.

### 5. Send Control Packet (Recoil)
- **SERVICE_UID:** `e6f59d10-8230-4a5c-b22f-c062b1d329e3`
- **CHARACTERISTIC_UID:** `e6f59d13-8230-4a5c-b22f-c062b1d329e3` (Control)
- **PAYLOAD:** `0x0008` (recoil action)
- **Purpose:** Trigger the gun's recoil motor.

### 6. Send Control Packet (Flash)
- **SERVICE_UID:** `e6f59d10-8230-4a5c-b22f-c062b1d329e3`
- **CHARACTERISTIC_UID:** `e6f59d13-8230-4a5c-b22f-c062b1d329e3` (Control)
- **PAYLOAD:** `0x0010` (flash action)
- **Purpose:** Trigger the gun's muzzle flash.

### 7. Send Control Packet (Remove Clip)
- **SERVICE_UID:** `e6f59d10-8230-4a5c-b22f-c062b1d329e3`
- **CHARACTERISTIC_UID:** `e6f59d13-8230-4a5c-b22f-c062b1d329e3` (Control)
- **PAYLOAD:** `0x0002` (remove clip)
- **Purpose:** Simulate removing the ammo clip.

### 8. Send Control Packet (Load Clip)
- **SERVICE_UID:** `e6f59d10-8230-4a5c-b22f-c062b1d329e3`
- **CHARACTERISTIC_UID:** `e6f59d13-8230-4a5c-b22f-c062b1d329e3` (Control)
- **PAYLOAD:** `0x0004` (load clip)
- **Purpose:** Simulate loading the ammo clip.

### 9. Send Control Packet (Power Off)
- **SERVICE_UID:** `e6f59d10-8230-4a5c-b22f-c062b1d329e3`
- **CHARACTERISTIC_UID:** `e6f59d13-8230-4a5c-b22f-c062b1d329e3` (Control)
- **PAYLOAD:** `0x0020` (power off)
- **Purpose:** Power off the gun.

### 10. Update Shot Configuration
- **SERVICE_UID:** `e6f59d10-8230-4a5c-b22f-c062b1d329e3`
- **CHARACTERISTIC_UID:** `e6f59d14-8230-4a5c-b22f-c062b1d329e3` (Config)
- **PAYLOAD:** 5 bytes (see below)
  - Tag: `0x10`
  - Length: `0x02`
  - Auto feedback flags: (recoil, flash)
  - Weapon override: `0xff` (default)
- **Purpose:** Change gun feedback settings.

### 11. Set Weapon Profile
- **SERVICE_UID:** `e6f59d10-8230-4a5c-b22f-c062b1d329e3`
- **CHARACTERISTIC_UID:** `e6f59d14-8230-4a5c-b22f-c062b1d329e3` (Config)
- **PAYLOAD:** 12 bytes (see below)
  - Slot/tag
  - Length: `0x09`
  - Weapon parameters (trigger mode, rate of fire, IR power, LED power, motor power, flash params)
- **Purpose:** Update weapon definition/configuration for a specific slot.

---

## Summary Table

| Sequence Step            | Service UID         | Characteristic UID                | Payload Value(s)      | Purpose                        |
|------------------------- |--------------------|-----------------------------------|-----------------------|--------------------------------|
| Connect                  | e6f59d10-...       | All                               | None                  | Establish BLE connection       |
| Start Telemetry          | e6f59d10-...       | e6f59d12-... (Telemetry)          | None                  | Receive gun state updates      |
| Control (Init)           | e6f59d10-...       | e6f59d13-... (Control)            | 0x0000                | Initialize/update gun state    |
| Control (Shoot)          | e6f59d10-...       | e6f59d13-... (Control)            | 0x0001                | Shoot                         |
| Control (Recoil)         | e6f59d10-...       | e6f59d13-... (Control)            | 0x0008                | Recoil                        |
| Control (Flash)          | e6f59d10-...       | e6f59d13-... (Control)            | 0x0010                | Muzzle flash                  |
| Control (Remove Clip)    | e6f59d10-...       | e6f59d13-... (Control)            | 0x0002                | Remove clip                   |
| Control (Load Clip)      | e6f59d10-...       | e6f59d13-... (Control)            | 0x0004                | Load clip                     |
| Control (Power Off)      | e6f59d10-...       | e6f59d13-... (Control)            | 0x0020                | Power off                     |
| Update Shot Config       | e6f59d10-...       | e6f59d14-... (Config)             | [0x10,0x02,...]       | Feedback settings              |
| Set Weapon Profile       | e6f59d10-...       | e6f59d14-... (Config)             | [slot,0x09,...]       | Weapon definition              |

---

**Note:**
- The actual payloads for config/weapon profile are buffers with multiple bytes, as described above.
- The action sequence is determined by the order in which your code calls the respective methods (e.g., `shoot()`, `recoil()`, `updateSettings()`, etc).
- Most commands are sent via the control characteristic, with specific payload values for each action.
- If you want the exact byte layout for any payload, let me know which action you want detailed!