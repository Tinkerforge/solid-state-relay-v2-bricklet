use std::{error::Error, io, thread, time::Duration};
use tinkerforge::{ipconnection::IpConnection, solid_state_relay_v2_bricklet::*};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Solid State Relay Bricklet 2.0

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let solid_state_relay_v2_bricklet = SolidStateRelayV2Bricklet::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    // Turn relay on/off 10 times with 1 second delay
    for i in 0..5 {
        thread::sleep(Duration::from_millis(1000));
        solid_state_relay_v2_bricklet.set_state(true);
        thread::sleep(Duration::from_millis(1000));
        solid_state_relay_v2_bricklet.set_state(false);
    }

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
