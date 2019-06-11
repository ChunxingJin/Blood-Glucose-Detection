
#ifndef _CONFIG_H
#define _CONFIG_H

/* ͨ��ͷ�ļ� */
#include <STC8A.h>
#include <intrins.h>
#include <stdio.h>
#include <string.h>



/* �������Ͷ��� */
typedef  signed    char    int8;    // 8λ�з���������
typedef  signed    int     int16;   //16λ�з���������
typedef  signed    long    int32;   //32λ�з���������
typedef  unsigned  char    uint8;   // 8λ�޷���������
typedef  unsigned  int     uint16;  //16λ�޷���������
typedef  unsigned  long    uint32;  //32λ�޷���������
#include "uart1.h"
#include "uart3.h"
#include "uart2.h"
#include "soft_timer.h"

/* ȫ�����в������� */
#define FOSC   11059200L  //ϵͳ��ʱ��Ƶ�ʣ�������Ƶ�ʡ�12
#define	BRT	(65536 - FOSC / 115200 / 4)

#define F125KHZ (65536-(FOSC/2/125000/12))


#define PGACOUNT      0x07

/* IO���ŷ��䶨�� */

sbit LED1 = P4^2;
sbit LED2 = P2^4;
sbit LED3 = P1^4;
sbit LED4 = P1^0;

#endif