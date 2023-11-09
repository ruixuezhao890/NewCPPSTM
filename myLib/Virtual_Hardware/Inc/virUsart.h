/**
*********************************************************************
*********
* @project_name :car0
* @file : virUsart.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6
*********************************************************************
*********
*/
//

#ifndef CAR0_VIRUSART_H
#define CAR0_VIRUSART_H
#include "Resources.h"

class virUsart {
public:
    virtual void uart_init(UART_enum uart, uint32_t baudrate)=0;
    virtual void uart_deinit(UART_enum uart)=0;
    virtual void uart_write_byte(UART_enum uart, uint8_t data)=0;
    virtual void uart_write_buffer(UART_enum uart, const uint8_t *buf, int len)=0;
    virtual void uart_write_string(UART_enum uart, const char *str)=0;
    virtual uint16_t uart_rec_size(UART_enum uart)=0;
    virtual uint8_t uart_read_byte(UART_enum uart)=0;

    virtual void uart_dma_init(UART_enum uart)=0;
    virtual void uart_dma_write_buffer(UART_enum uart, const uint8_t *buf, int len)=0;
};


#endif //CAR0_VIRUSART_H
