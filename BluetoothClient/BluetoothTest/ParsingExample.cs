
using HashtagChris.DotNetBlueZ;
using HashtagChris.DotNetBlueZ.Extensions;
public class ParsingExample
{
    public async Task ParseIdentity()
    {
        var device = await new DeviceManager().Connect();

        var service = new GunService();
        Console.WriteLine($"Getting GunService");
        var gattService = await device.GetServiceAsync(service.Uid);

        var ch = service.Identity;
        Console.WriteLine($"Reading {ch.Name}");
        var c = await gattService.GetCharacteristicAsync(ch.Uid);
        byte[] value = await c.ReadValueAsync(timeout);

        var valueAsHex = BitConverter.ToString(value);

        Console.WriteLine($"{ch.Name}:{valueAsHex}");

        var payload = IdentityPayload.FromByteArray(value);
        Console.WriteLine(payload);

    }

    public async Task LogTelemetry()
    {
        var device = await new DeviceManager().Connect();

        var service = new GunService();
        Console.WriteLine($"Getting GunService");
        var gattService = await device.GetServiceAsync(service.Uid);

        var ch = service.Telemetry;
        Console.WriteLine($"Reading {ch.Name}");
        var c = await gattService.GetCharacteristicAsync(ch.Uid);

        c.Value += watcher;
        await Task.Delay(30 * 1000);

    }

    private async Task watcher(GattCharacteristic sender, GattCharacteristicValueEventArgs eventArgs)
    {
        try
        {
            Console.WriteLine($"{BitConverter.ToString(eventArgs.Value)}");
            var payload = TelemetryPayload.FromByteArray(eventArgs.Value);
            
            Console.WriteLine($"GunId {ToBinary(payload.GunID)}");
            Console.WriteLine($"Button {ToBinary(payload.Buttons)}");

        }
        catch (Exception ex)
        {
            Console.Error.WriteLine(ex);
        }
    }

    private string ToBinary(byte number) => Convert.ToString(number, 2).PadLeft(8, '0');
    private static TimeSpan timeout = TimeSpan.FromSeconds(15);


}


