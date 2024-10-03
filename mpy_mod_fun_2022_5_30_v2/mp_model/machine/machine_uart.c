/*
 * Copyright (C) 2022 Polygon Zone Open Source Organization .
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http:// www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 *
 * limitations under the License.
 */



#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <hi_types_base.h>
#include <hi_early_debug.h>
#include <hi_stdlib.h>
#include <hi_errno.h>
#include <hi_uart.h>
#include <hi_io.h>
#include "iot_gpio.h" 
#include "iot_uart.h" 
#include "hi_io.h"

#include "py/obj.h"
#include "py/runtime.h"
#include "py/stream.h"
#include "py/mperrno.h"
#include "modmachine.h"
#include "machine_uart.h"
#include "hal_pz_uart.h"



MP_STATIC const char *_parity_name[] = {"None", "1", "0"};

/******************************************************************************/

MP_STATIC void machine_uart_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    machine_uart_obj_t *self = MP_OBJ_TO_PTR(self_in);
    uint32_t baudrate=115200;
    mp_printf(print, "UART(%u, baudrate=%u, bits=%u, parity=%s, stop=%u, timeout=%u",
        self->uart_num, baudrate, self->bits, _parity_name[self->parity],
        self->stop, self->timeout); 
    mp_printf(print, ")");
}



MP_STATIC int machine_uart_init_helper(machine_uart_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
	int ret = 0;
	IotUartAttribute uart_cfg = {115200, 8, 1, IOT_UART_PARITY_NONE, 0, 0, 0};
	enum { ARG_baudrate, ARG_bits, ARG_parity, ARG_stop,  ARG_timeout, ARG_timeout_char };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_baudrate, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_bits, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_parity, MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
        { MP_QSTR_stop, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_timeout, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 0} },
        //{ MP_QSTR_timeout_char, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 0} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);
    uint32_t baudrate = 115200;
    if (args[ARG_baudrate].u_int > 0) {
		baudrate = args[ARG_baudrate].u_int;
    }
	self->baudrate = baudrate;
    switch (args[ARG_bits].u_int) {
        case 0:
            break;
        case 5:
            self->bits = 5;
            break;
        case 6:
            self->bits = 6;
            break;
        case 7:
            self->bits = 7;
            break;
        case 8:
            self->bits = 8;
            break;
        default:
            mp_raise_ValueError(MP_ERROR_TEXT("invalid data bits"));
            break;
    }
    if (args[ARG_parity].u_obj != MP_OBJ_NULL) {
        if (args[ARG_parity].u_obj == mp_const_none) {
            self->parity = 0;
        } else {
            mp_int_t parity = mp_obj_get_int(args[ARG_parity].u_obj);
            if (parity & 1) {
                self->parity = 1;
            } else {
                self->parity = 2;
            }
        }
    }
    switch (args[ARG_stop].u_int) {
        case 0:
            break;
        case 1:
            self->stop = 1;
            break;
        case 2:
            self->stop = 2;
            break;
        default:
            mp_raise_ValueError(MP_ERROR_TEXT("invalid stop bits"));
            break;
    }
	
	uart_cfg.baudRate = self->baudrate;
	uart_cfg.dataBits = self->bits;
	uart_cfg.stopBits = self->stop;
	uart_cfg.parity = self->parity;
	
	self->timeout = args[ARG_timeout].u_int;
    
	if(self->timeout != 0){
		if(self->timeout>=65535){
			/* 永久阻塞 */
			self->timeout = 0;
		}
		uart_cfg.rxBlock = IOT_UART_BLOCK_STATE_BLOCK;
		uart_cfg.txBlock = IOT_UART_BLOCK_STATE_BLOCK;
	}else{
		/* 不阻塞 */
		uart_cfg.rxBlock = IOT_UART_BLOCK_STATE_NONE_BLOCK;
		uart_cfg.txBlock = IOT_UART_BLOCK_STATE_NONE_BLOCK;
	}
	ret  = hal_pz_uart_init(self->uart_num, &uart_cfg); 
	return ret;
}



MP_STATIC mp_obj_t machine_uart_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 1, MP_OBJ_FUN_ARGS_MAX, true);
    mp_int_t uart_num = mp_obj_get_int(args[0]);
    if (uart_num < 0 || uart_num >= HI_UART_IDX_MAX) {
        mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("UART(%d) does not exist"), uart_num);
    }
    if (uart_num == HI_UART_IDX_0) {
        mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("UART(%d) is disabled (dedicated to REPL)"), uart_num);
    }
    machine_uart_obj_t *self = m_new_obj(machine_uart_obj_t);
    self->base.type = &machine_uart_type;
    self->uart_num = uart_num;
    self->bits = 8;
    self->parity = 0;
    self->stop = 1;
    self->timeout = 0;
    mp_map_t kw_args;
    mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
    int ret = machine_uart_init_helper(self, n_args - 1, args + 1, &kw_args);
	if(ret != 0){
		return mp_const_none;
	}
	return MP_OBJ_FROM_PTR(self);
}




MP_STATIC mp_obj_t machine_uart_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    int ret = machine_uart_init_helper(args[0], n_args - 1, args + 1, kw_args);
	if(ret == 0){
		return mp_const_true;
	}else{
		return mp_const_false;
	}
}
MP_DEFINE_CONST_FUN_OBJ_KW(machine_uart_init_obj, 1, machine_uart_init);




MP_STATIC mp_obj_t machine_uart_deinit(mp_obj_t self_in) {
    machine_uart_obj_t *self = MP_OBJ_TO_PTR(self_in);
	hal_pz_uart_deinit(self->uart_num);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(machine_uart_deinit_obj, machine_uart_deinit);




MP_STATIC mp_obj_t machine_uart_any(mp_obj_t self_in) {
    machine_uart_obj_t *self = MP_OBJ_TO_PTR(self_in);
	hi_bool empty = HI_TRUE;
    size_t rxbufsize = hal_pz_uart_len(self->uart_num);
    return MP_OBJ_NEW_SMALL_INT(rxbufsize);
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(machine_uart_any_obj, machine_uart_any);



MP_STATIC mp_obj_t machine_uart_sendbreak(mp_obj_t self_in) {
    machine_uart_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_1(machine_uart_sendbreak_obj, machine_uart_sendbreak);



MP_STATIC const mp_rom_map_elem_t machine_uart_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&machine_uart_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&machine_uart_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR_any), MP_ROM_PTR(&machine_uart_any_obj) },
    { MP_ROM_QSTR(MP_QSTR_read), MP_ROM_PTR(&mp_stream_read_obj) },
    { MP_ROM_QSTR(MP_QSTR_readline), MP_ROM_PTR(&mp_stream_unbuffered_readline_obj) },
    { MP_ROM_QSTR(MP_QSTR_readinto), MP_ROM_PTR(&mp_stream_readinto_obj) },
    { MP_ROM_QSTR(MP_QSTR_write), MP_ROM_PTR(&mp_stream_write_obj) },
    { MP_ROM_QSTR(MP_QSTR_sendbreak), MP_ROM_PTR(&machine_uart_sendbreak_obj) },
	
};
MP_STATIC MP_DEFINE_CONST_DICT(machine_uart_locals_dict, machine_uart_locals_dict_table);




MP_STATIC mp_uint_t machine_uart_read(mp_obj_t self_in, void *buf_in, mp_uint_t size, int *errcode) {
    machine_uart_obj_t *self = MP_OBJ_TO_PTR(self_in);
    if (size == 0) {
        return 0;
    }
    unsigned int time_to_wait;
    if (self->timeout == 0) {
        time_to_wait = 0;
    } else {
        time_to_wait = self->timeout;
    }
    int bytes_read = 0;
	if(time_to_wait>0){
    	bytes_read = hal_pz_uart_read_timeout(self->uart_num,buf_in,size,time_to_wait);
	}else{
		bytes_read = hal_pz_uart_read(self->uart_num,buf_in,size);
	}
	if (bytes_read <= 0) {
        *errcode = MP_EAGAIN;
        return MP_STREAM_ERROR;
    }
    return bytes_read;
}




MP_STATIC mp_uint_t machine_uart_write(mp_obj_t self_in, const void *buf_in, mp_uint_t size, int *errcode) {
    machine_uart_obj_t *self = MP_OBJ_TO_PTR(self_in);
    int bytes_written = hal_pz_uart_write(self->uart_num,buf_in,size);
    if (bytes_written < 0) {
        *errcode = MP_EAGAIN;
        return MP_STREAM_ERROR;
    }
    return bytes_written;
}




MP_STATIC mp_uint_t machine_uart_ioctl(mp_obj_t self_in, mp_uint_t request, mp_uint_t arg, int *errcode) {
    machine_uart_obj_t *self = self_in;
    mp_uint_t ret;
    if (request == MP_STREAM_POLL) {
        mp_uint_t flags = arg;
        ret = 0;
        size_t rxbufsize = hal_pz_uart_len(self->uart_num);
        if ((flags & MP_STREAM_POLL_RD) && rxbufsize > 0) {
            ret |= MP_STREAM_POLL_RD;
        }
        if ((flags & MP_STREAM_POLL_WR) && 1) { // FIXME: uart_tx_any_room(self->uart_num)
            ret |= MP_STREAM_POLL_WR;
        }
    } else {
        *errcode = MP_EINVAL;
        ret = MP_STREAM_ERROR;
    }
    return ret;
}



MP_STATIC const mp_stream_p_t uart_stream_p = {
    .read = machine_uart_read,
    .write = machine_uart_write,
    .ioctl = machine_uart_ioctl,
    .is_text = false,
};





const mp_obj_type_t machine_uart_type = {
    { &mp_type_type },
    .name = MP_QSTR_UART,
    .print = machine_uart_print,
    .make_new = machine_uart_make_new,
    .getiter = mp_identity_getiter,
    .iternext = mp_stream_unbuffered_iter,
    .protocol = &uart_stream_p,
    .locals_dict = (mp_obj_dict_t *)&machine_uart_locals_dict,
};






