
using System.Diagnostics.CodeAnalysis;
using System.Text;
using HashtagChris.DotNetBlueZ;
using HashtagChris.DotNetBlueZ.Extensions;

public class BT
{
    public async Task Run()
    {
        TimeSpan timeout = TimeSpan.FromSeconds(15);


        IAdapter1 adapter = await BlueZManager.GetAdapterAsync(adapterName: "hci0");
        IReadOnlyList<Device> devices = await adapter.GetDevicesAsync();

        Device rk45 = null;
        foreach (var device in devices)
        {
            var address = await device.GetAddressAsync();
            Console.WriteLine(address);
            if (address.Equals("EF:20:EC:C8:B7:2A"))
            {
                rk45 = device;
                break;
            }
        }

        if (rk45 is null)
        {
            new Exception("rk45 not found.");
        }
        await rk45.ConnectAsync();
        Console.WriteLine($"Connected with {await rk45.GetNameAsync()}");
        Console.WriteLine($"Connected with {await rk45.GetConnectedAsync()}");


        var service1 = new GunService();

        IGattService1 service = await rk45.GetServiceAsync(service1.Uid);
        var characteristic = await service.GetCharacteristicAsync(service1.Identity.Uid);

        byte[] value = await characteristic.ReadValueAsync(timeout);

        var valueAsHex = BitConverter.ToString(value);

        Console.WriteLine($"{service1.Identity.Name}:{valueAsHex}");


    }



}




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

internal record GunService : Service
{
    public Characteristic Identity { get; }
    [SetsRequiredMembers]
    public GunService() : base(nameof(GunService), "e6f59d10-8230-4a5c-b22f-c062b1d329e3")
    {
        Identity = new(nameof(Identity), "e6f59d11-8230-4a5c-b22f-c062b1d329e3");
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
