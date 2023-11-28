/**
*********************************************************************
*********
* @project_name :car0
* @file : MyUsart.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6
*********************************************************************
*********
*/
//

#ifndef CAR0_MYUSART_H
#define CAR0_MYUSART_H
#include "virUsart.h"
extern uint8_t openDMATransmit;
class MyUsart :public virUsart{
public:
    void uart_init(UART_enum uart, uint32_t baudrate) override;

    void uart_deinit(UART_enum uart) override;

    void uart_write_byte(UART_enum uart, uint8_t data) override;

    void uart_write_buffer(UART_enum uart, const uint8_t *buf, int len) override;

    void uart_write_string(UART_enum uart, const char *str) override;

    uint16_t uart_rec_size(UART_enum uart) override;

    uint8_t uart_read_byte(UART_enum uart) override;

    void uart_dma_init(UART_enum uart) override;

    void uart_dma_write_buffer(UART_enum uart, const uint8_t *buf, int len) override;

protected:
    __rec_buf* selectBuff(UART_enum uart);

};
extern "C"{
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void UART4_IRQHandler(void);
void UART5_IRQHandler(void);
void USART6_IRQHandler(void);

}

#endif //CAR0_MYUSART_H
