// This example is not self-contained.
// It requires usage of the example driver specific to your platform.
// See the HAL documentation.

#include "src/bindings/hal_common.h"
#include "src/bindings/bricklet_solid_state_relay_v2.h"

void check(int rc, const char *msg);
void example_setup(TF_HAL *hal);
void example_loop(TF_HAL *hal);

static TF_SolidStateRelayV2 ssr;

void example_setup(TF_HAL *hal) {
	// Create device object
	check(tf_solid_state_relay_v2_create(&ssr, NULL, hal), "create device object");

	// Turn relay on/off 10 times with 1 second delay
	int i;
	for (i = 0; i < 5; ++i) {
		tf_hal_sleep_us(hal, 1000 * 1000);
		check(tf_solid_state_relay_v2_set_state(&ssr, true), "call set_state");
		tf_hal_sleep_us(hal, 1000 * 1000);
		check(tf_solid_state_relay_v2_set_state(&ssr, false), "call set_state");
	}
}

void example_loop(TF_HAL *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
