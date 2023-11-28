/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseSerial.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/7
*********************************************************************
*********
*/
//

#ifndef CAR0_BASESERIAL_H
#define CAR0_BASESERIAL_H
#include "headfile.h"
#include "inputStream.h"
#include "outputStream.h"
class BaseSerial:public MyUsart,public outputStream,public inputStream{
private:
    UART_enum uart_x;
    int baudrate;
    void set_buf_ptr();
public:
    BaseSerial(UART_enum uart);
    int begin(int baudrate);
    int beginDMA(int baudrate);
    int end() ;

    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *buffer, size_t size);



};

extern BaseSerial Baseserial;
#endif //CAR0_BASESERIAL_H
