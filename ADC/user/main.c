#include "config.h"

uint16 ad1_value;
uint16 ad2_value;
uint16 ad3_value;
uint16 ad4_value;
void ptr_handle(uint8 *stack)
{
    uint8 *stack_pt;
		uint16 adc_data;
    stack_pt = stack;
		switch(*stack_pt)
		{
			case 0x01:
			{
				stack_pt++;
				ad1_value = (uint16)(*stack_pt)<<8|(*(stack_pt+1));
				if(ad1_value == 0xffff)
				{
//					ADC_CH_CHANGE(ADC_CH_1);
					LED1=1;
					Delay100ms();			
					Delay100ms();
					Delay100ms();
					Delay100ms();
					Delay100ms();
					LED1=0;
//					adc_data = Get_ADC_RES();
//					tx_stack.uart_data[2] = adc_data;
//					tx_stack.uart_data[1] = adc_data>>8;
//					tx_stack.uart_data[0] = 0x01;
//					usart_senddata();
					printf("LED1请求 %d\r\n",adc_data);
				}
				break;
			}
			case 0x02:
			{
				stack_pt++;
				ad2_value = (uint16)(*stack_pt)<<8|(*(stack_pt+1));
				if(ad2_value == 0xffff)
				{
//					ADC_CH_CHANGE(ADC_CH_2);
//					Delay100ms();
//					adc_data = Get_ADC_RES();
//					tx_stack.uart_data[2] = adc_data;
//					tx_stack.uart_data[1] = adc_data>>8;
//					tx_stack.uart_data[0] = 0x02;
//					usart_senddata();
					LED2=1;
					Delay100ms();			
					Delay100ms();
					Delay100ms();
					Delay100ms();
					Delay100ms();
					LED2=0;
					printf("LED2请求 %d\r\n",adc_data);
				}
				break;
			}
			case 0x03:
			{
				stack_pt++;
				ad3_value = (uint16)(*stack_pt)<<8|(*(stack_pt+1));
				if(ad1_value == 0xffff)
				{
//					ADC_CH_CHANGE(ADC_CH_3);
//					Delay100ms();
//					adc_data = Get_ADC_RES();
//					tx_stack.uart_data[2] = adc_data;
//					tx_stack.uart_data[1] = adc_data>>8;
//					tx_stack.uart_data[0] = 0x03;
//					usart_senddata();
					LED3=1;
					Delay100ms();			
					Delay100ms();
					Delay100ms();
					Delay100ms();
					Delay100ms();
					LED3=0;
					printf("LED3请求  %d\r\n",adc_data);
				}
				break;
			}
			case 0x04:
			{
				stack_pt++;
				ad4_value = (uint16)(*stack_pt)<<8|(*(stack_pt+1));
				if(ad1_value == 0xffff)
				{
//					ADC_CH_CHANGE(ADC_CH_4);
//					Delay100ms();
//					adc_data = Get_ADC_RES();
//					tx_stack.uart_data[2] = adc_data;
//					tx_stack.uart_data[1] = adc_data>>8;
//					tx_stack.uart_data[0] = 0x04;
//					usart_senddata();
					LED4=1;
					Delay100ms();			
					Delay100ms();
					Delay100ms();
					Delay100ms();
					Delay100ms();
					LED4=0;
					printf("LED4请求 %d\r\n",adc_data);
				}
				break;
			}
			default: break;
		}
    rx_stack.lock_flag = UNLOCK;
}
void main()
{
//	LED1 = 0;
//	LED2 = 0;
//	LED3 = 0;
//	LED4 = 0;
	Uart1Init();
  Uart2Init();
	Uart3Init();
	tx_stack_init();
	rx_stack_init();
	EA = 1;					//使能总中断
	printf(" start!!\r\n");
	Uart2SendStr("hello\r\n");
//	Uart3Send(255);
	while(1)
	{
		if(rx_stack.lock_flag == LOCK)
		{
			printf("解析\r\n");
			ptr_handle(rx_stack.uart_data);       //运行协议解析函数
		}		
	}
}