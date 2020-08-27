#include "bindings/hal_common.h"
#include "bindings/bricklet_solid_state_relay_v2.h"

#define UID "XYZ" // Change XYZ to the UID of your Solid State Relay Bricklet 2.0

void check(int rc, const char* msg);

void example_setup(TF_HalContext *hal);
void example_loop(TF_HalContext *hal);


static TF_SolidStateRelayV2 ssr;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_solid_state_relay_v2_create(&ssr, UID, hal), "create device object");

	// Turn relay on/off 10 times with 1 second delay
	int i;
	for(i = 0; i < 5; ++i) {
		tf_hal_sleep_us(hal, 1000 * 1000);
		check(tf_solid_state_relay_v2_set_state(&ssr, true), "call set_state");
		tf_hal_sleep_us(hal, 1000 * 1000);
		check(tf_solid_state_relay_v2_set_state(&ssr, false), "call set_state");
	}
}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
