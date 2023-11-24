/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseGPIO.h
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
#include "Factory.h"

class BaseGPIO {
private:
    Pin_enum gpio_pin;

public:
    BaseGPIO();
    BaseGPIO(Pin_enum pin);
    BaseGPIO(Pin_enum pin, GpioMode mode);
    void mode(GpioMode mode);
    void write(uint8_t data);
    void toggle();
    uint8_t read();
    void BaseSetCallBack(void (*callback)(void), GpioExit mode,uint8_t PreemptPriority,uint8_t SubPriority);

    uint16_t adc();
    ~BaseGPIO();
protected:

};


#endif //CAR0_GPIO_H
