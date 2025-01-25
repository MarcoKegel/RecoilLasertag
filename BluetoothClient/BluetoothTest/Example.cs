using System.Text;
using HashtagChris.DotNetBlueZ;
using HashtagChris.DotNetBlueZ.Extensions;

public class SimpleExample
{
    public async Task ReadAndWriteValues()
    {
       var rk45 = await new DeviceManager().Connect();


        await WriteDeviceInformation(rk45);
        await WriteGunService(rk45);

    }
    private async Task WriteDeviceInformation(Device device)
    {
        var service = new DeviceInformationService();
        Console.WriteLine($"Getting DeviceInformationService");
        IGattService1 gattService = await device.GetServiceAsync(service.Uid);
        await GetAndWriteValueAsHex(gattService, service.ManufacturerName);
    }
    private async Task WriteGunService(Device device)
    {
        var service = new GunService();
        Console.WriteLine($"Getting GunService");
        var gattService = await device.GetServiceAsync(service.Uid);
        await GetAndWriteValueAsHex(gattService, service.Identity);
        await GetAndWriteValueAsHex(gattService, service.Config);
        await GetAndWriteValueAsHex(gattService, service.Control);
        //await GetAndWriteValueAsHex(service1.Telemetry);
    }

    private async Task GetAndWriteValueAsHex(IGattService1 gattService, Characteristic ch)
    {
        Console.WriteLine($"Reading {ch.Name}");
        var c = await gattService.GetCharacteristicAsync(ch.Uid);
        byte[] value = await c.ReadValueAsync(timeout);

        var valueAsHex = BitConverter.ToString(value);
        var valueAsUtf = Encoding.UTF8.GetString(value);
        Console.WriteLine($"{ch.Name}:{valueAsHex}\n{valueAsUtf}");
    }

    private static TimeSpan timeout = TimeSpan.FromSeconds(15);
}
