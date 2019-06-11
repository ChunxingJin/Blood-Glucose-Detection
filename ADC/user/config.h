
#ifndef _CONFIG_H
#define _CONFIG_H

/* 通用头文件 */
#include <STC8A.h>
#include <intrins.h>
#include <stdio.h>
#include <string.h>



/* 数据类型定义 */
typedef  signed    char    int8;    // 8位有符号整型数
typedef  signed    int     int16;   //16位有符号整型数
typedef  signed    long    int32;   //32位有符号整型数
typedef  unsigned  char    uint8;   // 8位无符号整型数
typedef  unsigned  int     uint16;  //16位无符号整型数
typedef  unsigned  long    uint32;  //32位无符号整型数
#include "uart1.h"
#include "uart3.h"
#include "uart2.h"
#include "soft_timer.h"

/* 全局运行参数定义 */
#define FOSC   11059200L  //系统主时钟频率，即振荡器频率÷12
#define	BRT	(65536 - FOSC / 115200 / 4)

#define F125KHZ (65536-(FOSC/2/125000/12))


#define PGACOUNT      0x07

/* IO引脚分配定义 */

sbit LED1 = P4^2;
sbit LED2 = P2^4;
sbit LED3 = P1^4;
sbit LED4 = P1^0;

#endif