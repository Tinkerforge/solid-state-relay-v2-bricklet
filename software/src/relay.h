/* solid-state-relay-v2-bricklet
 * Copyright (C) 2017 Olaf Lüke <olaf@tinkerforge.com>
 *
 * relay.h: Relay driver
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

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	bool state_new;
	bool state;

	bool monoflop_new;
	bool monoflop_in_progress;
	bool monoflop_state;
	bool monoflop_done;
	uint32_t monoflop_time;
	uint32_t monoflop_time_remaining;
	uint32_t monoflop_start;
} Relay;

void relay_init(void);
void relay_tick(void);
