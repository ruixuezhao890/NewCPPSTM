/**
*********************************************************************
*********
* @project_name :car0
* @file : MyGPIO.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6 
*********************************************************************
*********
*/
//

#ifndef CAR0_MYGPIO_H
#define CAR0_MYGPIO_H
#include "virGPIO.h"

class MyGPIO: public virGPIO{
public:
    MyGPIO();
    void gpio_init(Pin_enum pin, GpioMode mode) override;

    void gpio_init(Pin_enum pin, GpioMode mode, uint8_t select) override;

    void gpio_deinit(Pin_enum pin) override;

    void gpio_write(Pin_enum pin, uint8_t data) override;

    void gpio_toggle(Pin_enum pin) override;

    void gpio_interrupt_init(Pin_enum pin, CallBack callBack, GpioExit mode) override;

    void gpio_interrupt_deinit(Pin_enum pin) override;

    uint8_t gpio_read(Pin_enum pin) override;

    ~MyGPIO() override;
protected:
    uint8_t get_exit_irqchannel(Pin_enum pin);
};

extern "C" {
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
}
#endif //CAR0_MYGPIO_H
