/**
*********************************************************************
*********
* @project_name :car0
* @file : GPIO.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6 
*********************************************************************
*********
*/
//

#ifndef CAR0_GPIO_H
#define CAR0_GPIO_H
#include "headfile.h"
class GPIO {
private:
    virGPIO *virGpio;
    Pin_enum gpio_pin;
    GPIOFactory factory;
public:
    GPIO();
    GPIO(Pin_enum pin);
    GPIO(Pin_enum pin, GpioMode mode);
    void mode(GpioMode mode);
    void write(uint8_t data);
    void toggle();
    uint8_t read();
    void attachInterrupt(void (*callback)(void), GpioExit mode);

    uint16_t adc();
    ~GPIO();
};


#endif //CAR0_GPIO_H
