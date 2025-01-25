record TelemetryPayload
{

    public uint PacketCount { get; set; }          // U4
    public uint CommandCount { get; set; }         // U4
    public byte GunID { get; set; }                // U8
    public byte Buttons { get; set; }              // U8
    public uint[] PressedCounts { get; set; } = new uint[6]; // U4*6
    public short BatteryVoltage { get; set; }      // S16

    public ushort[] InfraredPayloads { get; set; } = new ushort[2];  // U16*2 (IR events payload)
    public byte[] InfraredCounters { get; set; } = new byte[2];      // U4*2 (LSB of IR events)

    public byte WeaponAmmo { get; set; }           // U8
    public byte GunFlags { get; set; }             // U8
    public byte SelectedWeaponType { get; set; }   // U8
    public byte[] Reserved { get; set; } = new byte[3];

    public static TelemetryPayload FromByteArray(byte[] data)
   {
        if (data.Length < 18) // Ensure the byte array has the minimum required length
            throw new ArgumentException("Invalid byte array length");

        using (var reader = new BinaryReader(new MemoryStream(data)))
        {
            byte firstByte = reader.ReadByte();
                        
            // Extract 4-bit values
            byte packetCount = (byte)(firstByte >> 4); // Upper 4 bits
            byte commandCount = (byte)(firstByte & 0x0F); // Lower 4 bits
            
            var gunStatus = new TelemetryPayload
            {
                PacketCount = packetCount,
                CommandCount = commandCount,
                GunID = reader.ReadByte(),
                Buttons = reader.ReadByte()
            };

            // Read 6 pairs of 4-bit values (each byte has 2 U4 values)
            for (int i = 0; i < 3; i++)
            {
                byte pressedPair = reader.ReadByte();
                gunStatus.PressedCounts[i * 2] = (byte)(pressedPair >> 4); // Upper 4 bits
                gunStatus.PressedCounts[i * 2 + 1] = (byte)(pressedPair & 0x0F); // Lower 4 bits
            }

            gunStatus.BatteryVoltage = reader.ReadInt16();

            // Read Infrared event structures
            gunStatus.InfraredPayloads[0] = reader.ReadUInt16();
            gunStatus.InfraredPayloads[1] = reader.ReadUInt16();

            byte irCounterPair = reader.ReadByte();
            gunStatus.InfraredCounters[0] = (byte)(irCounterPair >> 4); // Upper 4 bits
            gunStatus.InfraredCounters[1] = (byte)(irCounterPair & 0x0F); // Lower 4 bits

            gunStatus.WeaponAmmo = reader.ReadByte();
            gunStatus.GunFlags = reader.ReadByte();
            gunStatus.SelectedWeaponType = reader.ReadByte();
            gunStatus.Reserved = reader.ReadBytes(3);

            return gunStatus;
        }
    
    }


}
