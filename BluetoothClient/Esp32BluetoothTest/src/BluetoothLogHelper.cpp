#include "BluetoothLogHelper.h"

BluetoothLogHelper::BluetoothLogHelper() {} 

void BluetoothLogHelper::LogInfo(BLERemoteCharacteristic *characteristic)
{
    Log.traceln("Characteristic UUid %s", characteristic->getUUID().toString().c_str());
    Log.traceln("Characteristic canBroadcast %s", characteristic->canBroadcast() ? "true" : "false");
    Log.traceln("Characteristic canIndicate %s", characteristic->canIndicate() ? "true" : "false");
    Log.traceln("Characteristic canNotify %s", characteristic->canNotify() ? "true" : "false");
    Log.traceln("Characteristic canRead %s", characteristic->canRead() ? "true" : "false");
    Log.traceln("Characteristic canWrite %s", characteristic->canWrite() ? "true" : "false");
    Log.traceln("Characteristic canWriteNoResponse %s", characteristic->canWriteNoResponse() ? "true" : "false");
}

BluetoothLogHelper BLH = BluetoothLogHelper();