internal record IdentityPayload
{

    public ushort Version { get; set; }
    public byte[] UUID { get; set; } = new byte[8];
    public byte GunModel { get; set; }
    public byte[] Padding { get; set; } = new byte[3];
    public uint ConfigCRC { get; set; }
    public ushort BootloaderVersion { get; set; }

    public static IdentityPayload FromByteArray(byte[] data)
    {
        if (data.Length < 18) // Ensure the byte array is large enough
            throw new ArgumentException("Invalid byte array length");

        using (var reader = new BinaryReader(new MemoryStream(data)))
        {
            return new IdentityPayload
            {
                Version = reader.ReadUInt16(),
                UUID = reader.ReadBytes(8),
                GunModel = reader.ReadByte(),
                Padding = reader.ReadBytes(3),
                ConfigCRC = reader.ReadUInt32(),
                BootloaderVersion = reader.ReadUInt16()
            };
        }

    }
}
