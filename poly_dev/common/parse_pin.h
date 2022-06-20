#include <hi_types_base.h>
#include <hi_early_debug.h>
#include <hi_stdlib.h>
#include <hi_errno.h>
#include <hi_gpio.h>
#include <hi_pwm.h>
#include <hi_adc.h>
#include <hi_io.h>


typedef struct gpio_func {
    hi_gpio_idx gpio_id;
    hi_u8 func;
} gpio_func;

typedef struct pwm_func {
    hi_pwm_port pwm_ch;
    hi_u8 func;
} pwm_func;

typedef struct s_pin {
    hi_io_name io_name;
    gpio_func gpio_aux;
    pwm_func pwm_aux;
    hi_adc_channel_index adc_ch;
} s_pin;

typedef struct d_pin {
    s_pin close_v_pin;
    s_pin apart_v_pin;
} d_pin;


s_pin parse_single_pin(hi_u8 pin_num);
d_pin parse_double_pin(hi_u8 pin_num);