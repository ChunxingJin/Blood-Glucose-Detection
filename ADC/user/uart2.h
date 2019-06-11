#ifndef __UART2_H
#define __UART2_H
#include "config.h"



void Uart2Init();
void Uart2Send(char dat);
void Uart2SendStr(char *p);
#endif