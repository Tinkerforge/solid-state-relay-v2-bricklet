/* solid-state-relay-v2-bricklet
 * Copyright (C) 2017 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.h: TFP protocol message handling
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

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/bootloader/bootloader.h"

// Default functions
BootloaderHandleMessageResponse handle_message(const void *data, void *response);
void communication_tick(void);
void communication_init(void);

// Constants
#define SOLID_STATE_RELAY_V2_BOOTLOADER_MODE_BOOTLOADER 0
#define SOLID_STATE_RELAY_V2_BOOTLOADER_MODE_FIRMWARE 1
#define SOLID_STATE_RELAY_V2_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2
#define SOLID_STATE_RELAY_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3
#define SOLID_STATE_RELAY_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

#define SOLID_STATE_RELAY_V2_BOOTLOADER_STATUS_OK 0
#define SOLID_STATE_RELAY_V2_BOOTLOADER_STATUS_INVALID_MODE 1
#define SOLID_STATE_RELAY_V2_BOOTLOADER_STATUS_NO_CHANGE 2
#define SOLID_STATE_RELAY_V2_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3
#define SOLID_STATE_RELAY_V2_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4
#define SOLID_STATE_RELAY_V2_BOOTLOADER_STATUS_CRC_MISMATCH 5

#define SOLID_STATE_RELAY_V2_STATUS_LED_CONFIG_OFF 0
#define SOLID_STATE_RELAY_V2_STATUS_LED_CONFIG_ON 1
#define SOLID_STATE_RELAY_V2_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2
#define SOLID_STATE_RELAY_V2_STATUS_LED_CONFIG_SHOW_STATUS 3

// Function and callback IDs and structs
#define FID_SET_STATE 1
#define FID_GET_STATE 2
#define FID_SET_MONOFLOP 3
#define FID_GET_MONOFLOP 4

#define FID_CALLBACK_MONOFLOP_DONE 5

typedef struct {
	TFPMessageHeader header;
	bool state;
} __attribute__((__packed__)) SetState;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetState;

typedef struct {
	TFPMessageHeader header;
	bool state;
} __attribute__((__packed__)) GetState_Response;

typedef struct {
	TFPMessageHeader header;
	bool state;
	uint32_t time;
} __attribute__((__packed__)) SetMonoflop;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetMonoflop;

typedef struct {
	TFPMessageHeader header;
	bool state;
	uint32_t time;
	uint32_t time_remaining;
} __attribute__((__packed__)) GetMonoflop_Response;

typedef struct {
	TFPMessageHeader header;
	bool state;
} __attribute__((__packed__)) MonoflopDone_Callback;


// Function prototypes
BootloaderHandleMessageResponse set_state(const SetState *data);
BootloaderHandleMessageResponse get_state(const GetState *data, GetState_Response *response);
BootloaderHandleMessageResponse set_monoflop(const SetMonoflop *data);
BootloaderHandleMessageResponse get_monoflop(const GetMonoflop *data, GetMonoflop_Response *response);

// Callbacks
bool handle_monoflop_done_callback(void);

#define COMMUNICATION_CALLBACK_TICK_WAIT_MS 1
#define COMMUNICATION_CALLBACK_HANDLER_NUM 1
#define COMMUNICATION_CALLBACK_LIST_INIT \
	handle_monoflop_done_callback, \


#endif
