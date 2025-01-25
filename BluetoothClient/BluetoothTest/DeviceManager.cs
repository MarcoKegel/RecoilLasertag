using HashtagChris.DotNetBlueZ;
using HashtagChris.DotNetBlueZ.Extensions;

internal class DeviceManager
{

public async Task<Device> Connect()
{
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
        return rk45;
}
}
