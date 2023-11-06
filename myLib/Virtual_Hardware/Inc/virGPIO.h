/**
*********************************************************************
*********
* @project_name :car0
* @file : virGPIO.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6 
*********************************************************************
*********
*/
//

#ifndef CAR0_VIRGPIO_H
#define CAR0_VIRGPIO_H


#include "Resources.h"

using CallBack=void(*)(void);
#define DEFAULT_GPIO_SPEED GpioSpeed::freq_medium //GPIO初始化默认GPIO速度 可以在Resources中找到
class virGPIO {
protected:
    virGPIO();
public:
   virtual void gpio_init(Pin_enum pin, GpioMode mode)=0;
   virtual void gpio_deinit(Pin_enum pin)=0;
   virtual void gpio_write(Pin_enum pin, uint8_t data)=0;
   virtual void gpio_toggle(Pin_enum pin)=0;
   virtual void gpio_interrupt_init(Pin_enum pin, CallBack callBack, GpioExit mode)=0;
   virtual void gpio_interrupt_deinit(Pin_enum pin)=0;
   virtual uint8_t gpio_read(Pin_enum pin)=0;
   virtual ~virGPIO();

};

extern CallBack ExitFunc[16];
#endif //CAR0_VIRGPIO_H