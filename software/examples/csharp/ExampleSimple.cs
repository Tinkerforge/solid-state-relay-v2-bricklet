using System;
using System.Threading;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Solid State Relay Bricklet 2.0

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletSolidStateRelayV2 ssr =
		  new BrickletSolidStateRelayV2(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Turn relay on/off 10 times with 1 second delay
		for(int i = 0; i < 5; i++)
		{
			Thread.Sleep(1000);
			ssr.SetState(true);
			Thread.Sleep(1000);
			ssr.SetState(false);
		}

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
