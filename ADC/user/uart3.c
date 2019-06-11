#include "uart3.h"
bit busy3;

send_stack tx_stack;

void tx_stack_init()
{
    tx_stack.head = 0xaa;     //Э��ջͷ����ʼλ��1010 1010b
    tx_stack.direction = 0xF9;//����������0xF9��ʾ�ӵ�Ƭ������
    memset(tx_stack.uart_data, 0, sizeof(tx_stack.uart_data));//��tx_stack.uart_data[]ȫ����ʼ��Ϊ��
    tx_stack.tail = 0xdd;     //Э��ջβ������λ��1101 1101b��ջͷ��ջβ����ܻ���
}

receive_stack rx_stack;

void rx_stack_init()
{
    rx_stack.head = 0x00;         //Э��ջͷ����ʼλ
    rx_stack.direction = 0x00;    //����������0x09��ʾ�ӵ�Ƭ������
    memset(rx_stack.uart_data, 0, sizeof(rx_stack.uart_data));//��tx_stack.uart_data[]ȫ����ʼ��Ϊ��
    rx_stack.tail = 0x00;         //Э��ջβ������λ
    rx_stack.data_pt = 0x00;
    rx_stack.lock_flag = UNLOCK;
}

void Uart3Init(void)		//115200bps@11.0592MHz   //LEDģ��������  ͨ�Ŵ���
{
	S3CON = 0x10;		//8λ����,�ɱ䲨����
	S3CON &= 0xBF;		//����3ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
	T2L = 0xE8;		//�趨��ʱ��ֵ
	T2H = 0xFF;		//�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
	
	IE2	|= 0x08; //�򿪴���3�ж�
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
		if (S3CON&0X02)//�����ж�
    {
        S3CON &=~ 0X02;
        busy3 = 0;
    }
    if (S3CON&0X01)//�����ж�
    {
        S3CON	&=~ 0X01;//�������2�����ж�	
//				LED4 = !LED4;
        receive_data = S3BUF;
        if(rx_stack.lock_flag == UNLOCK)                   //�������Э��ջδ����
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