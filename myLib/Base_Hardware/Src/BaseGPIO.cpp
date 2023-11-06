/**
*********************************************************************
*********
* @project_name :car0
* @file : GPIO.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6 
*********************************************************************
*********
*/
//

#include "BaseGPIO.h"
GPIO::GPIO() {
    virGpio=factory.greatMyGPIO();
}

GPIO::GPIO(Pin_enum pin):GPIO() {
    this->gpio_pin=pin;
}

GPIO::GPIO(Pin_enum pin, GpioMode mode): GPIO(pin) {
    virGpio->gpio_init(pin,mode);
}

void GPIO::mode(GpioMode mode) {
    virGpio->gpio_init(gpio_pin,mode);
}

void GPIO::write(uint8_t data) {
    virGpio->gpio_write(gpio_pin,data);
}

void GPIO::toggle() {
    virGpio->gpio_toggle(gpio_pin);
}

uint8_t GPIO::read() {
    return virGpio->gpio_read(gpio_pin);
}

void GPIO::attachInterrupt(void (*callback)(void), GpioExit mode) {
    virGpio->gpio_interrupt_init(gpio_pin,callback,mode);
}

uint16_t GPIO::adc() {
    // todo 未来增加GPIO与adc的结合
    return 0;
}

GPIO::~GPIO() {
    delete virGpio;
    virGpio= nullptr;
}
