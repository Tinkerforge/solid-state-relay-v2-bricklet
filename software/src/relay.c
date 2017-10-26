/* solid-state-relay-v2-bricklet
 * Copyright (C) 2017 Olaf Lüke <olaf@tinkerforge.com>
 *
 * relay.c: Relay driver
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "relay.h"

#include <string.h>

#include "bricklib2/utility/util_definitions.h"
#include "bricklib2/hal/system_timer/system_timer.h"
#include "configs/config_relay.h"

#include "xmc_gpio.h"

Relay relay;

static void relay_update(void) {
	XMC_GPIO_SetOutputLevel(RELAY_PIN, relay.state ? XMC_GPIO_OUTPUT_LEVEL_HIGH : XMC_GPIO_OUTPUT_LEVEL_LOW);
}

void relay_init(void) {
	memset(&relay, 0, sizeof(Relay));

	const XMC_GPIO_CONFIG_t config_pin =  {
		.mode         = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
		.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW
	};

	XMC_GPIO_Init(RELAY_PIN, &config_pin);
}

void relay_tick(void) {
	if(relay.state_new) {
		relay.state_new = false;
		relay_update();

		relay.monoflop_new = false;
		relay.monoflop_in_progress = false;
		relay.monoflop_time_remaining = 0;
	}

	if(relay.monoflop_new) {
		relay.monoflop_start = system_timer_get_ms();
		relay.state = relay.monoflop_state;
		relay_update();
		relay.monoflop_new = false;
		relay.monoflop_in_progress =  true;
	}

	if(relay.monoflop_in_progress) {
		uint32_t time_diff = system_timer_get_ms() - relay.monoflop_start;
		relay.monoflop_time_remaining = MAX(0, relay.monoflop_time - time_diff);

		if(relay.monoflop_time_remaining == 0) {
			relay.state = !relay.monoflop_state;
			relay_update();
			relay.monoflop_in_progress = false;
			relay.monoflop_done = true;
		}
	}
}
