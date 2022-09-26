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




#include "hw_ctrl.h"
#include "oled_ssd1306.h"






void all_peripheral_deinit(){
#if BUILD_BOARD == DASHIXIONG_BOARD
	//OledInit();
	//OledFillScreen(0);
#endif
	int i = 0; 
	for(i=0; i<HI_PWM_PORT_MAX; i++){
		IoTPwmDeinit(i);
	}
	hi_i2c_deinit(HI_I2C_IDX_0);
	hi_i2c_deinit(HI_I2C_IDX_1);
	hi_spi_deinit(HI_SPI_ID_0);
	hi_spi_deinit(HI_SPI_ID_1);
	hi_uart_deinit(HI_UART_IDX_1);
	hi_uart_deinit(HI_UART_IDX_2);
	for(i=0; i<HI_GPIO_IDX_MAX; i++){
		if(i==3 || i==4){
			continue;
		}
		IoTGpioDeinit(i);
		hi_io_set_func(i,0);
	}
#if BUILD_BOARD == DASHIXIONG_BOARD
	//OledInit();
	//OledFillScreen(0);
	//OledDeinit();
#endif	
}






