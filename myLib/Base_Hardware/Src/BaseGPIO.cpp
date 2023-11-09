/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseGPIO.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6 
*********************************************************************
*********
*/
//

#include "BaseGPIO.h"
virGPIO *virGpio= nullptr;
BaseGPIO::BaseGPIO() {
    if (!virGpio)
    virGpio=new MyGPIO();
}

BaseGPIO::BaseGPIO(Pin_enum pin): BaseGPIO() {
    this->gpio_pin=pin;
}

BaseGPIO::BaseGPIO(Pin_enum pin, GpioMode mode): BaseGPIO(pin) {
    virGpio->gpio_init(pin,mode);
}

void BaseGPIO::mode(GpioMode mode) {
    virGpio->gpio_init(gpio_pin,mode);
}

void BaseGPIO::write(uint8_t data) {
    virGpio->gpio_write(gpio_pin,data);
}

void BaseGPIO::toggle() {
    virGpio->gpio_toggle(gpio_pin);
}

uint8_t BaseGPIO::read() {
    return virGpio->gpio_read(gpio_pin);
}

void BaseGPIO::attachInterrupt(void (*callback)(void), GpioExit mode) {
    virGpio->gpio_interrupt_init(gpio_pin,callback,mode);
}

uint16_t BaseGPIO::adc() {
    // todo 未来增加GPIO与adc的结合
    return 0;
}

BaseGPIO::~BaseGPIO() {
    delete virGpio;
    virGpio= nullptr;
}
