/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
 #ifndef MICROPY_INCLUDED_EXTMOD_BTSTACK_BTSTACK_CONFIG_H
#define MICROPY_INCLUDED_EXTMOD_BTSTACK_BTSTACK_CONFIG_H

// BTstack features that can be enabled
#define ENABLE_BLE
#define ENABLE_LE_PERIPHERAL
#define ENABLE_LE_CENTRAL
// #define ENABLE_CLASSIC
#define ENABLE_LE_DATA_CHANNELS
// #define ENABLE_LOG_INFO
// #define ENABLE_LOG_DEBUG
#define ENABLE_LOG_ERROR

// BTstack configuration. buffers, sizes, ...
#define HCI_ACL_PAYLOAD_SIZE 1021
#define MAX_NR_GATT_CLIENTS 1
#define MAX_NR_HCI_CONNECTIONS 1
#define MAX_NR_L2CAP_SERVICES  3
#define MAX_NR_L2CAP_CHANNELS  3
#define MAX_NR_RFCOMM_MULTIPLEXERS 1
#define MAX_NR_RFCOMM_SERVICES 1
#define MAX_NR_RFCOMM_CHANNELS 1
#define MAX_NR_BTSTACK_LINK_KEY_DB_MEMORY_ENTRIES  2
#define MAX_NR_BNEP_SERVICES 1
#define MAX_NR_BNEP_CHANNELS 1
#define MAX_NR_HFP_CONNECTIONS 1
#define MAX_NR_WHITELIST_ENTRIES 1
#define MAX_NR_SM_LOOKUP_ENTRIES 3
#define MAX_NR_SERVICE_RECORD_ITEMS 1
#define MAX_NR_AVDTP_STREAM_ENDPOINTS 1
#define MAX_NR_AVDTP_CONNECTIONS 1
#define MAX_NR_AVRCP_CONNECTIONS 1

#define MAX_NR_LE_DEVICE_DB_ENTRIES 4

// Link Key DB and LE Device DB using TLV on top of Flash Sector interface
// #define NVM_NUM_DEVICE_DB_ENTRIES 16

// We don't give btstack a malloc, so use a fixed-size ATT DB.
#define MAX_ATT_DB_SIZE 512

// BTstack HAL configuration
#define HAVE_EMBEDDED_TIME_MS

// Some USB dongles take longer to respond to HCI reset (e.g. BCM20702A).
#define HCI_RESET_RESEND_TIMEOUT_MS 1000

#endif // MICROPY_INCLUDED_EXTMOD_BTSTACK_BTSTACK_CONFIG_H
