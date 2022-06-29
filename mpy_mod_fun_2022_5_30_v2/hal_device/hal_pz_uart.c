#include "hal_pz_uart.h"
#include "uart_drv.h"
#include "uart.h"




static hal_pz_uart_t pz_uart_ctrl[HI_UART_IDX_MAX];




int hal_pz_uart_init(int uart_num,IotUartAttribute *uart_cfg){
	int ret = IOT_FAILURE;
	if(uart_num<0 || uart_num>=HI_UART_IDX_MAX){
		return IOT_FAILURE;
	}else{
		IoTUartDeinit(uart_num);
		if(uart_num == HI_UART_IDX_1){
			hi_io_set_func(0,0);    //使能引脚0、1的的UART1复用功能
			hi_io_set_func(1,0);
			IoTGpioDeinit(0);//使用GPIO，需要调用该接口 
			IoTGpioDeinit(1);//使用GPIO，需要调用该接口
			IoTGpioInit(0);//使用GPIO，需要调用该接口 
			IoTGpioInit(1);//使用GPIO，需要调用该接口 
			hi_io_set_func(0,2);    //使能引脚0、1的的UART1复用功能
			hi_io_set_func(1,2);
		}else if(uart_num == HI_UART_IDX_2){
			hi_io_set_func(11,0);    //使能引脚0、1的的UART1复用功能
			hi_io_set_func(12,0);
			IoTGpioDeinit(11);//使用GPIO，需要调用该接口 
			IoTGpioDeinit(12);//使用GPIO，需要调用该接口
			IoTGpioInit(11);//使用GPIO，需要调用该接口 
			IoTGpioInit(12);//使用GPIO，需要调用该接口 
			hi_io_set_func(11,HI_IO_FUNC_GPIO_11_UART2_TXD);    //使能引脚0、1的的UART1复用功能
			hi_io_set_func(12,HI_IO_FUNC_GPIO_12_UART2_RXD);
		}
		ret  = IoTUartInit(uart_num, uart_cfg);
		//printf("ret = %d\r\n",ret);
		if(ret == IOT_SUCCESS){
			/* 创建互斥锁 */
			int ret1=LOS_OK;
			int ret2=LOS_OK;
			if(pz_uart_ctrl[uart_num].cnt==0){
				ret1 = LOS_MuxCreate(&(pz_uart_ctrl[uart_num].rx_Mux));
				ret2 = LOS_MuxCreate(&(pz_uart_ctrl[uart_num].tx_Mux));
			}
			if(ret1==LOS_OK && ret2==LOS_OK){
				pz_uart_ctrl[uart_num].cnt++;
			}else{
				return IOT_FAILURE;
			}
		}
	}
	return ret;
}




int hal_pz_uart_deinit(int uart_num){
	if(uart_num<0 || uart_num>=HI_UART_IDX_MAX){
		return IOT_FAILURE;
	}else{
		if(pz_uart_ctrl[uart_num].cnt==1){
			LOS_MuxDelete(pz_uart_ctrl[uart_num].rx_Mux);
			LOS_MuxDelete(pz_uart_ctrl[uart_num].tx_Mux);
			pz_uart_ctrl[uart_num].rx_Mux = 0;
			pz_uart_ctrl[uart_num].tx_Mux = 0;
			IoTUartDeinit(uart_num);
			if(uart_num == HI_UART_IDX_1){
				hi_io_set_func(0,0);    //使能引脚0、1的的UART1复用功能
				hi_io_set_func(1,0);
				IoTGpioDeinit(0);//使用GPIO，需要调用该接口 
				IoTGpioDeinit(1);//使用GPIO，需要调用该接口
			}else if(uart_num == HI_UART_IDX_2){
				hi_io_set_func(11,0);    //使能引脚0、1的的UART1复用功能
				hi_io_set_func(12,0);
				IoTGpioDeinit(11);//使用GPIO，需要调用该接口 
				IoTGpioDeinit(12);//使用GPIO，需要调用该接口
			}
			pz_uart_ctrl[uart_num].cnt--;
		}else{
			if(pz_uart_ctrl[uart_num].cnt!=0){
				pz_uart_ctrl[uart_num].cnt--;
			}else{
				return IOT_FAILURE;
			}
		}
	}
	return IOT_SUCCESS;
}





/***************************** 通过最底层串口提供的SDK *****************************/





extern uart_driver_data_t *g_udd_g[UART_NUM];

hi_s32 uart_read_circ_buf_cnt(uart_circ_buf *transfer)
{
	if (transfer == NULL) {
        return (hi_s32) HI_ERR_FAILURE;
    }
	hi_u32 last_int_val = hi_int_lock();
	hi_u32 wp = transfer->wp;
    hi_u32 rp = transfer->rp;
	hi_int_restore(last_int_val);
	if(wp==rp){
		return 0;
	}else if(wp > rp){
		return wp - rp;
	}else{
		return rp - wp;
	}
}




hi_s32 uart_readable_len(uart_driver_data_t *udd){
	if (udd == HI_NULL) {
        return (hi_s32)HI_ERR_FAILURE;
    }
	return uart_read_circ_buf_cnt(udd->rx_transfer);
}







/************************************ 通过最底层串口提供的SDK **********************************/





int hal_pz_uart_len(int uart_num){
	if(uart_num<0 || uart_num>=HI_UART_IDX_MAX){
		return IOT_FAILURE;
	}

	hi_u32 port_num = (hi_u32) uart_num;
	if (port_num >= UART_NUM) {
        return (hi_s32)HI_ERR_FAILURE;
    }
	int rxbufsize =  uart_readable_len(g_udd_g[port_num]);
	return rxbufsize;
}



int hal_pz_uart_write(hi_uart_idx uart_num, const hi_u8 *data, hi_u32 data_len){
	if(uart_num<0 || uart_num>=HI_UART_IDX_MAX){
		return IOT_FAILURE;
	}
	int ret = 0;
	LOS_MuxPend(pz_uart_ctrl[uart_num].tx_Mux, LOS_WAIT_FOREVER);
	hi_uart_write(uart_num,data,data_len);
	LOS_MuxPost(pz_uart_ctrl[uart_num].tx_Mux);
	return ret;
}





int hal_pz_uart_read(hi_uart_idx uart_num, hi_u8 *data, hi_u32 data_len){
	if(uart_num<0 || uart_num>=HI_UART_IDX_MAX){
		return IOT_FAILURE;
	}
	int ret = 0;
	LOS_MuxPend(pz_uart_ctrl[uart_num].rx_Mux, LOS_WAIT_FOREVER);
	ret = hi_uart_read(uart_num,data,data_len);
	LOS_MuxPost(pz_uart_ctrl[uart_num].rx_Mux);
	return ret;
}







int hal_pz_uart_read_timeout(hi_uart_idx uart_num, hi_u8 *data, hi_u32 len, hi_u32 timeout_ms){
	if(uart_num<0 || uart_num>=HI_UART_IDX_MAX){
		return IOT_FAILURE;
	}
	int ret = 0;
	LOS_MuxPend(pz_uart_ctrl[uart_num].rx_Mux, LOS_WAIT_FOREVER);
	ret = hi_uart_read_timeout(uart_num,data,len,timeout_ms);
	LOS_MuxPost(pz_uart_ctrl[uart_num].rx_Mux);
	return ret;
}










