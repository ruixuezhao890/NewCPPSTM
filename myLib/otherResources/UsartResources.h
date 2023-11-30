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
#define MAXWait 0xffff
#define MAXUart 6
#define HAVE_SERIAL1
#define HAVE_SERIAL2
#define HAVE_SERIAL3
#define HAVE_SERIAL4
#define HAVE_SERIAL5
#define HAVE_SERIAL6

struct uartInfoMation{
    UART_HandleTypeDef UsartList[MAXUart]={0};//全局串口句柄
    uint8_t USARTx_IRQn[MAXUart]={0};
    //之后使用DMA的所有公共结构体内必须有下面这几个数组，里面对应的数据记得根据外设更改
    DMA_HandleTypeDef DmaHandleTypeDef[12];
    uint32_t DmaHandleInstance[12]{
            (uint32_t) DMA2_Stream2, (uint32_t) DMA2_Stream7,  // 收发
            (uint32_t) DMA1_Stream5, (uint32_t) DMA1_Stream6,
            (uint32_t) DMA1_Stream1, (uint32_t) DMA1_Stream3,
            (uint32_t) DMA1_Stream2, (uint32_t) DMA1_Stream4,
            (uint32_t) DMA1_Stream0, (uint32_t) DMA1_Stream7,
            (uint32_t) DMA2_Stream1, (uint32_t) DMA2_Stream6,
    };

    uint32_t DMA_Channel[12]{
            DMA_CHANNEL_4, DMA_CHANNEL_4,
            DMA_CHANNEL_4, DMA_CHANNEL_4,
            DMA_CHANNEL_4, DMA_CHANNEL_4,
            DMA_CHANNEL_4, DMA_CHANNEL_4,
            DMA_CHANNEL_4, DMA_CHANNEL_4,
            DMA_CHANNEL_5, DMA_CHANNEL_5,
    };
    uint32_t  DMA_IQRNNum[12]{
            DMA2_Stream2_IRQn,DMA2_Stream7_IRQn,
            DMA1_Stream5_IRQn,DMA1_Stream6_IRQn,
            DMA1_Stream1_IRQn,DMA1_Stream3_IRQn,
            DMA1_Stream2_IRQn,DMA1_Stream4_IRQn,
            DMA1_Stream0_IRQn,DMA1_Stream7_IRQn,
            DMA2_Stream1_IRQn,DMA2_Stream6_IRQn,
    };
};
extern uartInfoMation uartInfo;
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
