/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseSerial.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/7
*********************************************************************
*********
*/
//

#include "Base_Hardware/BaseSerial/Inc/BaseSerial.h"
virUsart *virUsart= nullptr;
BaseSerial Baseserial(UART_1);
void BaseSerial::set_buf_ptr() {
    switch (uart_x)
    {
#ifdef HAVE_SERIAL1
        case UART_1:
            buf = &UART1_recbuf;
            return;
#endif
#ifdef HAVE_SERIAL2
        case UART_2:
            buf = &UART2_recbuf;
            return;
#endif
#ifdef HAVE_SERIAL3
        case UART_3:
            buf = &UART3_recbuf;
            return;
#endif
#ifdef HAVE_SERIAL4
        case UART_4:
            buf = &UART4_recbuf;
            return;
#endif
#ifdef HAVE_SERIAL5
        case UART_5:
            buf = &UART5_recbuf;
            return;
#endif
#ifdef HAVE_SERIAL6
        case UART_6:
            buf = &UART6_recbuf;
            return;
#endif
        default:
            buf = nullptr;
            return;
    }
}

BaseSerial::BaseSerial(UART_enum uart) {
    this->uart_x = uart;
    set_buf_ptr();
    if (!virUsart)virUsart=new MyUsart();
}

int BaseSerial::begin(int baudrate) {
    this->baudrate = baudrate;
    virUsart->uart_init(uart_x,baudrate);
    return 1;
}

size_t BaseSerial::write(uint8_t data) {
   virUsart->uart_write_byte(uart_x,data);
    return 1;
}

size_t BaseSerial::write(const uint8_t *buffer, size_t size) {
    virUsart->uart_write_buffer(uart_x,buffer,size);
    return 1;
}

int BaseSerial::end() {
    virUsart->uart_deinit(uart_x);
    return 1;
}


