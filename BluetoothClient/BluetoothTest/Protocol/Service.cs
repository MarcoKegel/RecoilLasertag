using System.Diagnostics.CodeAnalysis;

internal abstract record Service
{
    public required string Name { get; init; }
    public required string Uid { get; init; }

    [SetsRequiredMembers]
    public Service(string Name, string Uid)
    {
        this.Name = Name;
        this.Uid = Uid;
    }

}
internal record Characteristic
{
    public required string Name { get; init; }
    public required string Uid { get; init; }
    [SetsRequiredMembers]
    public Characteristic(string Name, string Uid)
    {
        this.Name = Name;
        this.Uid = Uid;
    }
}

internal record GunService : Service
{
    public Characteristic Identity { get; }
    public Characteristic Telemetry { get; }
    public Characteristic Control { get; }
    public Characteristic Config { get; }

    [SetsRequiredMembers]
    public GunService() : base(nameof(GunService), "e6f59d10-8230-4a5c-b22f-c062b1d329e3")
    {
        Identity = new(nameof(Identity),    "e6f59d11-8230-4a5c-b22f-c062b1d329e3");
        Telemetry = new(nameof(Telemetry),  "e6f59d12-8230-4a5c-b22f-c062b1d329e3");
        Control = new(nameof(Control),      "e6f59d13-8230-4a5c-b22f-c062b1d329e3");
        Config = new(nameof(Config),        "e6f59d14-8230-4a5c-b22f-c062b1d329e3");
    }
}

internal record GenericAccessService : Service
{
    public Characteristic DeviceName { get; }
    
    [SetsRequiredMembers]
    public GenericAccessService() : base(nameof(GenericAccessService), "00001800-0000-1000-8000-00805f9b34fb")
    {
        throw new NotImplementedException("Is not implemented at the moment");
        DeviceName = new(nameof(GenericAccessService), "00002a00-0000-1000-8000-00805f9b34fb");
        //00002a01-0000-1000-8000-00805f9b34fb
        //00002a04-0000-1000-8000-00805f9b34fb
        //00002aa6-0000-1000-8000-00805f9b34fb
      
    }
}

internal record DeviceInformationService: Service
{
    public Characteristic ManufacturerName { get; }
  
    [SetsRequiredMembers]
    public DeviceInformationService() : base(nameof(DeviceInformationService), "0000180a-0000-1000-8000-00805f9b34fb")
    {
        ManufacturerName = new(nameof(ManufacturerName), "00002a29-0000-1000-8000-00805f9b34fb");
        
    }
}