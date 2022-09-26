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

// This is a translation of the cycle counter implementation in ports/stm32/machine_bitstream.c.

#include "py/mpconfig.h"
#include "py/mphal.h"

#if MICROPY_PY_MACHINE_BITSTREAM

#define NS_TICKS_OVERHEAD (6)

void IRAM_ATTR machine_bitstream_high_low(mp_hal_pin_obj_t pin, uint32_t *timing_ns, const uint8_t *buf, size_t len) {
    uint32_t pin_mask, gpio_reg_set, gpio_reg_clear;
    #if !CONFIG_IDF_TARGET_ESP32C3
    if (pin >= 32) {
        pin_mask = 1 << (pin - 32);
        gpio_reg_set = GPIO_OUT1_W1TS_REG;
        gpio_reg_clear = GPIO_OUT1_W1TC_REG;
    } else
    #endif
    {
        pin_mask = 1 << pin;
        gpio_reg_set = GPIO_OUT_W1TS_REG;
        gpio_reg_clear = GPIO_OUT_W1TC_REG;
    }

    // Convert ns to cpu ticks [high_time_0, period_0, high_time_1, period_1].
    uint32_t fcpu_mhz = ets_get_cpu_frequency();
    for (size_t i = 0; i < 4; ++i) {
        timing_ns[i] = fcpu_mhz * timing_ns[i] / 1000;
        if (timing_ns[i] > NS_TICKS_OVERHEAD) {
            timing_ns[i] -= NS_TICKS_OVERHEAD;
        }
        if (i % 2 == 1) {
            // Convert low_time to period (i.e. add high_time).
            timing_ns[i] += timing_ns[i - 1];
        }
    }

    uint32_t irq_state = mp_hal_quiet_timing_enter();

    for (size_t i = 0; i < len; ++i) {
        uint8_t b = buf[i];
        for (size_t j = 0; j < 8; ++j) {
            GPIO_REG_WRITE(gpio_reg_set, pin_mask);
            uint32_t start_ticks = mp_hal_ticks_cpu();
            uint32_t *t = &timing_ns[b >> 6 & 2];
            while (mp_hal_ticks_cpu() - start_ticks < t[0]) {
                ;
            }
            GPIO_REG_WRITE(gpio_reg_clear, pin_mask);
            b <<= 1;
            while (mp_hal_ticks_cpu() - start_ticks < t[1]) {
                ;
            }
        }
    }

    mp_hal_quiet_timing_exit(irq_state);
}

#endif // MICROPY_PY_MACHINE_BITSTREAM
