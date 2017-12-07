#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Solid State Relay Bricklet 2.0

# Turn relay on/off 10 times with 1 second delay
for i in 0 1 2 3 4; do
	sleep 1
	tinkerforge call solid-state-relay-v2-bricklet $uid set-state true
	sleep 1
	tinkerforge call solid-state-relay-v2-bricklet $uid set-state false
done
