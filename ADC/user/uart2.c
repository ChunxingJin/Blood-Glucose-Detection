#include "uart2.h"
//#include "reg51.h"
//#include "intrins.h"

//#define FOSC            11059200UL
//#define BRT             (65536 - FOSC / 115200 / 4)

//sfr     AUXR        =   0x8e;
//sfr     T2H         =   0xd6;
//sfr     T2L         =   0xd7;
//sfr     S2CON       =   0x9a;
//sfr     S2BUF       =   0x9b;
//sfr     IE2         =   0xaf;

bit busy2;
char wptr;
char rptr;
char buffer[16];

void Uart2Isr() interrupt 8
{
    if (S2CON & 0x02)
    {
        S2CON &= ~0x02;
        busy2 = 0;
    }
    if (S2CON & 0x01)
    {
        S2CON &= ~0x01;
        buffer[wptr++] = S2BUF;
        wptr &= 0x0f;
    }
}

void Uart2Init()
{
	S2CON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
	T2L = 0xE8;		//�趨��ʱ��ֵ
	T2H = 0xFF;		//�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
	IE2	|= 0x01;//�򿪴���2�ж�
    wptr = 0x00;
    rptr = 0x00;
    busy2 = 0;
}

void Uart2Send(char dat)
{
    while (busy2);
    busy2 = 1;
    S2BUF = dat;
}

void Uart2SendStr(char *p)
{
    while (*p)
    {
        Uart2Send(*p++);
    }
}

#if 0
void main()
{
    Uart2Init();
    IE2 = 0x01;
    EA = 1;
    Uart2SendStr("Uart Test !\r\n");

    while (1)
    {
        if (rptr != wptr)
        {
            Uart2Send(buffer[rptr++]);
            rptr &= 0x0f;
        }
    }
}
#endif