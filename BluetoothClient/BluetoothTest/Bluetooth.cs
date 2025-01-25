
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

        string serviceUUID = "e6f59d10-8230-4a5c-b22f-c062b1d329e3";
        string characteristicUUID = "00002a24-0000-1000-8000-00805f9b34fb";

        IGattService1 service = await rk45.GetServiceAsync(serviceUUID);
        var characteristics = await service.GetCharacteristicsAsync();
        foreach (var characteristic in characteristics)
        {
            var uid = await characteristic.GetUUIDAsync();
            byte[] value = await characteristic.ReadValueAsync(timeout);

            var valueAsHex = BitConverter.ToString(value);

            Console.WriteLine($"{uid}:{valueAsHex}");

        }
    }

}