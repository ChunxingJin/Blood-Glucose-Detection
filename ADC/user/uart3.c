#include "uart3.h"
bit busy3;

send_stack tx_stack;

void tx_stack_init()
{
    tx_stack.head = 0xaa;     //协议栈头，起始位，1010 1010b
    tx_stack.direction = 0xF9;//数据流方向，0xF9表示从单片机发出
    memset(tx_stack.uart_data, 0, sizeof(tx_stack.uart_data));//把tx_stack.uart_data[]全部初始化为零
    tx_stack.tail = 0xdd;     //协议栈尾，结束位，1101 1101b，栈头和栈尾最好能互补
}

receive_stack rx_stack;

void rx_stack_init()
{
    rx_stack.head = 0x00;         //协议栈头，起始位
    rx_stack.direction = 0x00;    //数据流方向，0x09表示从单片机发出
    memset(rx_stack.uart_data, 0, sizeof(rx_stack.uart_data));//把tx_stack.uart_data[]全部初始化为零
    rx_stack.tail = 0x00;         //协议栈尾，结束位
    rx_stack.data_pt = 0x00;
    rx_stack.lock_flag = UNLOCK;
}

void Uart3Init(void)		//115200bps@11.0592MHz   //LED模块与主控  通信串口
{
	S3CON = 0x10;		//8位数据,可变波特率
	S3CON &= 0xBF;		//串口3选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
	T2L = 0xE8;		//设定定时初值
	T2H = 0xFF;		//设定定时初值
	AUXR |= 0x10;		//启动定时器2
	
	IE2	|= 0x08; //打开串口3中断
}

void Uart3Send(uint8 dat)
{
    while (busy3);
    busy3 = 1;
    S3BUF = dat;
}

void Uart3Isr() interrupt 17 using 1
{
		unsigned char receive_data;
		static unsigned char receice_step;
		if (S3CON&0X02)//发送中断
    {
        S3CON &=~ 0X02;
        busy3 = 0;
    }
    if (S3CON&0X01)//接收中断
    {
        S3CON	&=~ 0X01;//清除串口2接收中断	
//				LED4 = !LED4;
        receive_data = S3BUF;
        if(rx_stack.lock_flag == UNLOCK)                   //如果接收协议栈未锁柱
        {
					switch(receice_step)
					{
						case 0:
						{
							if(receive_data == 0xaa)
							{
									rx_stack.head = receive_data;
									receice_step++;
									rx_stack.data_pt = 0;
							}
							break;
						}
						case 1:
						{
							if(receive_data == 0x09)
							{
									rx_stack.direction = receive_data;
									receice_step++;
									rx_stack.data_pt = 0;
							}
							else
							{
								receice_step = 0;
							}
							break;
						}
						case 2:
						{
							if(rx_stack.data_pt < 3)
							{
								rx_stack.uart_data[rx_stack.data_pt] = receive_data;
								//printf("receive_data %d  rx_stack.data_pt %d\r\n",receive_data,rx_stack.data_pt);
                rx_stack.data_pt++;
							}
							else if(rx_stack.data_pt == 3) 
							{
								rx_stack.uart_data[rx_stack.data_pt] = receive_data;
								receice_step++;
								rx_stack.data_pt = 0;
							}
							break;
						}
						case 3:
						{
							if(receive_data == 0xdd)
							{
								rx_stack.tail = receive_data;
								rx_stack.data_pt = 0;
								receice_step = 0;
                rx_stack.lock_flag = LOCK;
							}
							else
							{
								receice_step = 0;
							}
							break;
						}
						default:break;
					}
				}
    }
}