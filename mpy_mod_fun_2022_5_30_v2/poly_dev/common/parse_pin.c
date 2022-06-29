#include "parse_pin.h"
#include "polygon_sys_cfg.h"












#if HARDWARE_TYPE ==  HW_TYPE_DASHIXIONG
#if 0
s_pin parse_single_pin(hi_u8 pin_num)
{
    s_pin rst;

    switch (pin_num){
        case 0:
            rst.io_name = HI_IO_NAME_GPIO_7;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_7;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_7_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM0;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_7_PWM0_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_3;
            break;
        case 1:
            rst.io_name = HI_IO_NAME_GPIO_5;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_5;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_5_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM2;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_5_PWM2_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_2;
            break;
        case 2:
            rst.io_name = HI_IO_NAME_GPIO_0;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_0;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_0_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM3;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_0_PWM3_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
        case 3:
            rst.io_name = HI_IO_NAME_GPIO_1;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_1;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_1_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM4;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_1_PWM4_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
            
            break;
        case 4:
			
            rst.io_name = HI_IO_NAME_GPIO_2;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_2;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_2_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM2;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_2_PWM2_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
        case 5:
            rst.io_name = HI_IO_NAME_GPIO_11;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_11;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_11_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM2;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_11_PWM2_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_5;
            break;
        case 6: 
			rst.io_name = HI_IO_NAME_GPIO_13;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_13;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_13_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM4;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_13_PWM4_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_6;
			break;
        case 7: 
			rst.io_name = HI_IO_NAME_GPIO_14;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_14;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_14_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM5;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_14_PWM5_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
			break;
        case 8: 
            rst.io_name = HI_IO_NAME_GPIO_9;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_9;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_9_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM0;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_9_PWM0_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_4;
            break;
		case 9:
			rst.io_name = HI_IO_NAME_GPIO_10;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_10;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_10_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM1;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_9_PWM0_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
			break;
		case 10:
			rst.io_name = HI_IO_NAME_GPIO_12;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_12;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_12_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM3;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_12_PWM3_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_0;
			break;
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
        default: 
            rst.io_name = HI_IO_NAME_MAX;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_MAX;
            rst.gpio_aux.func = 0;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.pwm_aux.func = 0;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
    }
    return rst;
}
#endif
#ifdef _OLD_VERSION_H
s_pin parse_single_pin(hi_u8 pin_num)
{
    s_pin rst;
	rst.io_name = HI_IO_NAME_MAX;
    rst.gpio_aux.gpio_id = HI_GPIO_IDX_MAX;
    rst.gpio_aux.func = 0;
    rst.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
    rst.pwm_aux.func = 0;
    rst.adc_ch = HI_ADC_CHANNEL_BUTT;
    switch (pin_num){
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6: 
			break;
        case 7: 
			break;
        case 8: 
            rst.io_name = HI_IO_NAME_GPIO_12;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_12;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_12_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM3;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_12_PWM3_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_0;
            break;
		case 9:
			rst.io_name = HI_IO_NAME_GPIO_10;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_10;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_10_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM1;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_10_PWM1_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
			break;
		case 10:
			rst.io_name = HI_IO_NAME_GPIO_9;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_9;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_9_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM0;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_9_PWM0_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_4;
			break;
		case 11:
			rst.io_name = HI_IO_NAME_GPIO_5;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_5;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_5_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM2;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_5_PWM2_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_2;
			break;
		case 12:
			rst.io_name = HI_IO_NAME_GPIO_7;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_7;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_7_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM0;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_7_PWM0_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_3;
			break;
		case 13:
			rst.io_name = HI_IO_NAME_GPIO_1;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_1;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_1_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM4;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_1_PWM4_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
			break;
		case 14:
			rst.io_name = HI_IO_NAME_GPIO_0;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_0;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_0_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM3;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_0_PWM3_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
			break;
		case 15:
			rst.io_name = HI_IO_NAME_GPIO_11;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_11;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_11_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM2;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_11_PWM2_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_5;
			break;
		case 16:
			rst.io_name = HI_IO_NAME_GPIO_2;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_2;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_2_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM2;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_2_PWM2_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
			break;
		case 17:
			break;
        default: 
            break;
    }
    return rst;
}

#elif _OLD_VERSION_V2_1_H
s_pin parse_single_pin(hi_u8 pin_num)
{
    s_pin rst;
	rst.io_name = HI_IO_NAME_MAX;
    rst.gpio_aux.gpio_id = HI_GPIO_IDX_MAX;
    rst.gpio_aux.func = 0;
    rst.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
    rst.pwm_aux.func = 0;
    rst.adc_ch = HI_ADC_CHANNEL_BUTT;
    switch (pin_num){
        case 0:
			/*串口不可用*/
			/*
			rst.io_name = HI_IO_NAME_GPIO_3;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_3;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_3_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM3;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_3_PWM5_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
			*/
            break;
        case 1:
			rst.io_name = HI_IO_NAME_GPIO_7;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_7;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_7_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM0;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_7_PWM0_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_3;
            break;
        case 2:
			rst.io_name = HI_IO_NAME_GPIO_10;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_10;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_10_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM1;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_10_PWM1_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
        case 3:
			
            break;
        case 4:
			
            break;
        case 5:
			/*串口不可用*/
			/*
			rst.io_name = HI_IO_NAME_GPIO_4;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_4;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_4_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM1;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_4_PWM1_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_1;
            */
            break;
        case 6: 
			
			break;
        case 7: 
			
			break;
        case 8: 
            rst.io_name = HI_IO_NAME_GPIO_5;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_5;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_5_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM2;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_5_PWM2_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_2;
            break;
		case 9:
			rst.io_name = HI_IO_NAME_GPIO_6;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_6;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_6_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM3;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_6_PWM3_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
			break;
		case 10:
			rst.io_name = HI_IO_NAME_GPIO_8;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_8;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_8_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM1;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_8_PWM1_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
			break;
		case 11:
			rst.io_name = HI_IO_NAME_GPIO_2;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_2;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_2_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM2;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_2_PWM2_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
			break;
		case 12:
			rst.io_name = HI_IO_NAME_GPIO_9;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_9;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_9_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM0;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_9_PWM0_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_4;
			break;
		case 13:
			rst.io_name = HI_IO_NAME_GPIO_1;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_1;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_1_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM4;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_1_PWM4_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
			break;
		case 14:
			rst.io_name = HI_IO_NAME_GPIO_0;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_0;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_0_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM3;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_0_PWM3_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
			break;
		case 15:
			rst.io_name = HI_IO_NAME_GPIO_11;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_11;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_11_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM2;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_11_PWM2_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_5;
			break;
		case 16:
			rst.io_name = HI_IO_NAME_GPIO_12;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_12;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_12_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM3;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_12_PWM3_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_0;
			break;
		case 17:
			break;
        default: 
            break;
    }
    return rst;
}
#else



s_pin parse_single_pin(hi_u8 pin_num)
{
    s_pin rst;
	rst.io_name = HI_IO_NAME_MAX;
    rst.gpio_aux.gpio_id = HI_GPIO_IDX_MAX;
    rst.gpio_aux.func = 0;
    rst.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
    rst.pwm_aux.func = 0;
    rst.adc_ch = HI_ADC_CHANNEL_BUTT;
    switch (pin_num){
        case 0:
			
            break;
        case 1:
			rst.io_name = HI_IO_NAME_GPIO_7;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_7;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_7_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM0;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_7_PWM0_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_3;
            break;
        case 2:
			rst.io_name = HI_IO_NAME_GPIO_9;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_9;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_9_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM0;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_9_PWM0_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_4;
            break;
        case 3:
			
            break;
        case 4:
            break;
        case 5:
			rst.io_name = HI_IO_NAME_GPIO_10;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_10;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_10_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM1;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_10_PWM1_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
        case 6: 
			break;
        case 7: 
			break;
        case 8: 
           	rst.io_name = HI_IO_NAME_GPIO_8;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_8;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_8_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM1;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_8_PWM1_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
		case 9:
			break;
		case 10:
			break;
		case 11:
			rst.io_name = HI_IO_NAME_GPIO_2;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_2;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_2_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM2;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_2_PWM2_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
			break;
		case 12:
			rst.io_name = HI_IO_NAME_GPIO_6;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_6;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_6_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM3;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_6_PWM3_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
			break;
		case 13:
			rst.io_name = HI_IO_NAME_GPIO_12;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_12;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_12_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM3;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_12_PWM3_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_0;
			break;
		case 14:
			rst.io_name = HI_IO_NAME_GPIO_11;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_11;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_11_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM2;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_11_PWM2_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_5;
			break;
		case 15:
			rst.io_name = HI_IO_NAME_GPIO_0;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_0;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_0_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM3;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_0_PWM3_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
			break;
		case 16:
			break;
		case 17:
			break;
        default: 
            break;
    }
    return rst;
}



#endif




#elif HARDWARE_TYPE == HW_TYPE_TIANQI
s_pin parse_single_pin(hi_u8 pin_num)
{
    s_pin rst;

    switch (pin_num){
        case 0:
            rst.io_name = HI_IO_NAME_GPIO_14;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_14;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_14_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM5;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_14_PWM5_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
        case 1:
            rst.io_name = HI_IO_NAME_GPIO_2;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_2;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_2_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM2;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_2_PWM2_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
        case 2:
            rst.io_name = HI_IO_NAME_GPIO_7;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_7;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_7_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM0;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_7_PWM0_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_3;
            break;
        case 3:
            rst.io_name = HI_IO_NAME_GPIO_12;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_12;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_12_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM3;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_12_PWM3_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_0;
            break;
        case 4:
            rst.io_name = HI_IO_NAME_GPIO_5;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_5;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_5_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.pwm_aux.func = 0;
            rst.adc_ch = HI_ADC_CHANNEL_2;
            break;
        case 5:
            rst.io_name = HI_IO_NAME_GPIO_9;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_9;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_9_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.pwm_aux.func = 0;
            rst.adc_ch = HI_ADC_CHANNEL_4;
            break;
        case 6: 
        case 7: 
        case 8: 
            rst.io_name = HI_IO_NAME_GPIO_0;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_0;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_0_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.pwm_aux.func = 0;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
        default: 
            rst.io_name = HI_IO_NAME_MAX;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_MAX;
            rst.gpio_aux.func = 0;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.pwm_aux.func = 0;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
    }

    return rst;
}


#endif




d_pin parse_double_pin(hi_u8 pin_num)
{
    d_pin rst;

    switch (pin_num){
        case 0:
            rst.close_v_pin.io_name = HI_IO_NAME_GPIO_14;
            rst.close_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_14;
            rst.close_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_14_GPIO;
            rst.close_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_PWM5;
            rst.close_v_pin.pwm_aux.func = HI_IO_FUNC_GPIO_14_PWM5_OUT;
            rst.close_v_pin.adc_ch = HI_ADC_CHANNEL_BUTT;

            rst.apart_v_pin.io_name = HI_IO_NAME_GPIO_10;
            rst.apart_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_10;
            rst.apart_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_10_GPIO;
            rst.apart_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.apart_v_pin.pwm_aux.func = 0;
            rst.apart_v_pin.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
        case 1:
            rst.close_v_pin.io_name = HI_IO_NAME_GPIO_2;
            rst.close_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_2;
            rst.close_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_2_GPIO;
            rst.close_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_PWM2;
            rst.close_v_pin.pwm_aux.func = HI_IO_FUNC_GPIO_2_PWM2_OUT;
            rst.close_v_pin.adc_ch = HI_ADC_CHANNEL_BUTT;

            rst.apart_v_pin.io_name = HI_IO_NAME_GPIO_8;
            rst.apart_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_8;
            rst.apart_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_8_GPIO;
            rst.apart_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_PWM1;
            rst.apart_v_pin.pwm_aux.func = HI_IO_FUNC_GPIO_8_PWM1_OUT;
            rst.apart_v_pin.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
        case 2:
            rst.close_v_pin.io_name = HI_IO_NAME_GPIO_7;
            rst.close_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_7;
            rst.close_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_7_GPIO;
            rst.close_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_PWM0;
            rst.close_v_pin.pwm_aux.func = HI_IO_FUNC_GPIO_7_PWM0_OUT;
            rst.close_v_pin.adc_ch = HI_ADC_CHANNEL_3;
            
            rst.apart_v_pin.io_name = HI_IO_NAME_GPIO_13;
            rst.apart_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_13;
            rst.apart_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_13_GPIO;
            rst.apart_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_PWM4;
            rst.apart_v_pin.pwm_aux.func = HI_IO_FUNC_GPIO_13_PWM4_OUT;
            rst.apart_v_pin.adc_ch = HI_ADC_CHANNEL_6;
            break;
        case 3:
            rst.close_v_pin.io_name = HI_IO_NAME_GPIO_12;
            rst.close_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_12;
            rst.close_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_12_GPIO;
            rst.close_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_PWM3;
            rst.close_v_pin.pwm_aux.func = HI_IO_FUNC_GPIO_12_PWM3_OUT;
            rst.close_v_pin.adc_ch = HI_ADC_CHANNEL_0;

            rst.apart_v_pin.io_name = HI_IO_NAME_GPIO_11;
            rst.apart_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_11;
            rst.apart_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_11_GPIO;
            rst.apart_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.apart_v_pin.pwm_aux.func = 0;
            rst.apart_v_pin.adc_ch = HI_ADC_CHANNEL_5;
            break;
        case 6: 
        case 7:
        case 8:
            rst.close_v_pin.io_name = HI_IO_NAME_GPIO_0;
            rst.close_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_0;
            rst.close_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_0_GPIO;
            rst.close_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.close_v_pin.pwm_aux.func = 0;
            rst.close_v_pin.adc_ch = HI_ADC_CHANNEL_BUTT;

            rst.apart_v_pin.io_name = HI_IO_NAME_GPIO_1;
            rst.apart_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_1;
            rst.apart_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_1_GPIO;
            rst.apart_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.apart_v_pin.pwm_aux.func = 0;
            rst.apart_v_pin.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
        default:
            rst.close_v_pin.io_name = HI_IO_NAME_MAX;
            rst.close_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_MAX;
            rst.close_v_pin.gpio_aux.func = 0;
            rst.close_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.close_v_pin.pwm_aux.func = 0;
            rst.close_v_pin.adc_ch = HI_ADC_CHANNEL_BUTT;
			
            rst.apart_v_pin.io_name = HI_IO_NAME_MAX;
            rst.apart_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_MAX;
            rst.apart_v_pin.gpio_aux.func = 0;
            rst.apart_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.apart_v_pin.pwm_aux.func = 0;
            rst.apart_v_pin.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
    }

    return rst;
}

/*
 ver 2.0:
s_pin parse_single_pin(hi_u8 pin_num)
{
    s_pin rst;

    switch (pin_num){
        case 0:
            rst.io_name = HI_IO_NAME_GPIO_6;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_6;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_6_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.pwm_aux.func = 0;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
        case 1:
            rst.io_name = HI_IO_NAME_GPIO_14;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_14;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_14_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM5;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_14_PWM5_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
        case 2:
            rst.io_name = HI_IO_NAME_GPIO_7;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_7;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_7_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM0;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_7_PWM0_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_3;
            break;
        case 3:
            rst.io_name = HI_IO_NAME_GPIO_12;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_12;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_12_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM3;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_12_PWM3_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_0;
            break;
        case 4:
            rst.io_name = HI_IO_NAME_GPIO_13;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_13;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_13_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_PWM4;
            rst.pwm_aux.func = HI_IO_FUNC_GPIO_13_PWM4_OUT;
            rst.adc_ch = HI_ADC_CHANNEL_6;
            break;
        case 5:
            rst.io_name = HI_IO_NAME_GPIO_9;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_9;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_9_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.pwm_aux.func = 0;
            rst.adc_ch = HI_ADC_CHANNEL_4;
            break;
        case 6:
            rst.io_name = HI_IO_NAME_GPIO_2;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_2;
            rst.gpio_aux.func = HI_IO_FUNC_GPIO_2_GPIO;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.pwm_aux.func = 0;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
        default:
            rst.io_name = HI_IO_NAME_MAX;
            rst.gpio_aux.gpio_id = HI_GPIO_IDX_MAX;
            rst.gpio_aux.func = 0;
            rst.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.pwm_aux.func = 0;
            rst.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
    }

    return rst;
}

d_pin parse_double_pin(hi_u8 pin_num)
{
    d_pin rst;

    switch (pin_num){
        case 0:
            rst.close_v_pin.io_name = HI_IO_NAME_GPIO_6;
            rst.close_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_6;
            rst.close_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_6_GPIO;
            rst.close_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.close_v_pin.pwm_aux.func = 0;
            rst.close_v_pin.adc_ch = HI_ADC_CHANNEL_BUTT;

            rst.apart_v_pin.io_name = HI_IO_NAME_GPIO_5;
            rst.apart_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_5;
            rst.apart_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_5_GPIO;
            rst.apart_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.apart_v_pin.pwm_aux.func = 0;
            rst.apart_v_pin.adc_ch = HI_ADC_CHANNEL_2;
        case 1:
            rst.close_v_pin.io_name = HI_IO_NAME_GPIO_14;
            rst.close_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_14;
            rst.close_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_14_GPIO;
            rst.close_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_PWM5;
            rst.close_v_pin.pwm_aux.func = HI_IO_FUNC_GPIO_14_PWM5_OUT;
            rst.close_v_pin.adc_ch = HI_ADC_CHANNEL_BUTT;

            rst.apart_v_pin.io_name = HI_IO_NAME_GPIO_10;
            rst.apart_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_10;
            rst.apart_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_10_GPIO;
            rst.apart_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.apart_v_pin.pwm_aux.func = 0;
            rst.apart_v_pin.adc_ch = HI_ADC_CHANNEL_BUTT;
        case 2:
            rst.close_v_pin.io_name = HI_IO_NAME_GPIO_7;
            rst.close_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_7;
            rst.close_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_7_GPIO;
            rst.close_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_PWM0;
            rst.close_v_pin.pwm_aux.func = HI_IO_FUNC_GPIO_7_PWM0_OUT;
            rst.close_v_pin.adc_ch = HI_ADC_CHANNEL_3;

            rst.apart_v_pin.io_name = HI_IO_NAME_GPIO_11;
            rst.apart_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_11;
            rst.apart_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_11_GPIO;
            rst.apart_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_PWM2;
            rst.apart_v_pin.pwm_aux.func = HI_IO_FUNC_GPIO_11_PWM2_OUT;
            rst.apart_v_pin.adc_ch = HI_ADC_CHANNEL_5;
            break;
        case 3:
            rst.close_v_pin.io_name = HI_IO_NAME_GPIO_12;
            rst.close_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_12;
            rst.close_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_12_GPIO;
            rst.close_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_PWM3;
            rst.close_v_pin.pwm_aux.func = HI_IO_FUNC_GPIO_12_PWM3_OUT;
            rst.close_v_pin.adc_ch = HI_ADC_CHANNEL_0;

            rst.apart_v_pin.io_name = HI_IO_NAME_GPIO_8;
            rst.apart_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_8;
            rst.apart_v_pin.gpio_aux.func = HI_IO_FUNC_GPIO_8_GPIO;
            rst.apart_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_PWM1;
            rst.apart_v_pin.pwm_aux.func = HI_IO_FUNC_GPIO_8_PWM1_OUT;
            rst.apart_v_pin.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
        default:
            rst.close_v_pin.io_name = HI_IO_NAME_MAX;
            rst.close_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_MAX;
            rst.close_v_pin.gpio_aux.func = 0;
            rst.close_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.close_v_pin.pwm_aux.func = 0;
            rst.close_v_pin.adc_ch = HI_ADC_CHANNEL_BUTT;

            rst.apart_v_pin.io_name = HI_IO_NAME_MAX;
            rst.apart_v_pin.gpio_aux.gpio_id = HI_GPIO_IDX_MAX;
            rst.apart_v_pin.gpio_aux.func = 0;
            rst.apart_v_pin.pwm_aux.pwm_ch = HI_PWM_PORT_MAX;
            rst.apart_v_pin.pwm_aux.func = 0;
            rst.apart_v_pin.adc_ch = HI_ADC_CHANNEL_BUTT;
            break;
    }

    return rst;
}
*/
