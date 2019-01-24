package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
	"github.com/Tinkerforge/go-api-bindings/solid_state_relay_v2_bricklet"
	"time"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your Solid State Relay Bricklet 2.0.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	ssr, _ := solid_state_relay_v2_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Turn relay on/off 10 times with 1 second delay
	for i := 0; i < 5; i++ {
		time.Sleep(1000 * time.Millisecond)
		ssr.SetState(true)
		time.Sleep(1000 * time.Millisecond)
		ssr.SetState(false)
	}

	fmt.Print("Press enter to exit.")
	fmt.Scanln()
}
