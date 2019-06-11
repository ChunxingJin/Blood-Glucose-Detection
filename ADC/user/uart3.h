#ifndef __UART3_H
#define __UART3_H
#include "config.h"

#define UNLOCK			0
#define LOCK				1	  

typedef struct
{
    unsigned char head;
    unsigned char tail;
    unsigned char direction;
    unsigned char uart_data[4];
    unsigned char lock_flag;
    unsigned char data_pt;
}receive_stack;
extern receive_stack rx_stack;
typedef struct
{
    unsigned char head;
    unsigned char tail;
    unsigned char direction;
    unsigned char uart_data[4];
}send_stack;

extern send_stack tx_stack;

void Uart3Init(void);
void Uart3Send(uint8 dat);
void tx_stack_init();
void rx_stack_init();

#endif