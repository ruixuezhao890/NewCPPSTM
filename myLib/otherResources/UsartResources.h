/**
*********************************************************************
*********
* @project_name :car0
* @file : UsartResources.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/27 
*********************************************************************
*********
*/
//

#ifndef CAR0_USARTRESOURCES_H
#define CAR0_USARTRESOURCES_H
#include "stm32f4xx.h"
#define HAVE_SERIAL1
#define HAVE_SERIAL2
#define HAVE_SERIAL3
#define HAVE_SERIAL4
#define HAVE_SERIAL5
#define HAVE_SERIAL6
typedef struct
{
    volatile uint8_t buf[256];      //接收缓冲区
    volatile uint8_t write_index;   //写指针
    volatile uint8_t read_index;    //读指针
    volatile uint16_t data_size;    //缓冲区接收到的数据长度
    /* data */
}__rec_buf;
#ifdef HAVE_SERIAL1
extern __rec_buf UART1_recbuf;
#endif
#ifdef HAVE_SERIAL2
extern __rec_buf UART2_recbuf;
#endif
#ifdef HAVE_SERIAL3
extern __rec_buf UART3_recbuf;
#endif
#ifdef HAVE_SERIAL4
extern __rec_buf UART4_recbuf;
#endif
#ifdef HAVE_SERIAL5
extern __rec_buf UART5_recbuf;
#endif
#ifdef HAVE_SERIAL6
extern __rec_buf UART6_recbuf;
#endif
typedef enum
{
#ifdef HAVE_SERIAL1
    UART_1,
#endif
#ifdef HAVE_SERIAL2
    UART_2 ,
#endif
#ifdef HAVE_SERIAL3
    UART_3 ,
#endif
#ifdef HAVE_SERIAL4
    UART_4 ,
#endif
#ifdef HAVE_SERIAL5
    UART_5 ,
#endif
#ifdef HAVE_SERIAL6
    UART_6 ,
#endif
    UART_END // 占位符，未使用
} UART_enum;



#endif //CAR0_USARTRESOURCES_H
