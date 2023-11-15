/**
*********************************************************************
*********
* @project_name :car0
* @file : MyGPIO.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6
*********************************************************************
*********
*/
//

#include "MyGPIO.h"

CallBack ExitFunc[16];
void openCorrespondRCC(GPIO_TypeDef *GPIOx) {
    if (GPIOx == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        return;
    }
    if (GPIOx == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
        return;
    }
    if (GPIOx == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
        return;
    }
    if (GPIOx == GPIOD) {
        __HAL_RCC_GPIOD_CLK_ENABLE();
        return;
    }
    if (GPIOx == GPIOE) {
        __HAL_RCC_GPIOE_CLK_ENABLE();
        return;
    }
    if (GPIOx == GPIOF) {
        __HAL_RCC_GPIOF_CLK_ENABLE();
        return;
    }
    if (GPIOx == GPIOG) {
        __HAL_RCC_GPIOG_CLK_ENABLE();
        return;
    }
    if (GPIOx == GPIOH) {
        __HAL_RCC_GPIOH_CLK_ENABLE();
        return;
    }
    if (GPIOx == GPIOI) {
        __HAL_RCC_GPIOI_CLK_ENABLE();
        return;
    }
}
void MyGPIO::gpio_init(Pin_enum pin, GpioMode mode) {
    uint16_t gpio_pin = GPIO_PIN_0 << (pin & 0x0f);
    uint16_t gpio_port = (pin & 0xf0) >> 4;
    GPIO_TypeDef *GPIOx = (GPIO_TypeDef *)(GPIOA_BASE + 0x0400 * gpio_port);
    openCorrespondRCC(GPIOx);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = gpio_pin;
    GPIO_InitStruct.Mode = (uint32_t )mode;
    GPIO_InitStruct.Pull =((GpioExit)mode == GpioExit::it_falling) ?
            (uint32_t)GpioPull::pullup : (uint32_t)GpioPull::pulldown;
    GPIO_InitStruct.Speed = (uint32_t)DEFAULT_GPIO_SPEED;
    HAL_GPIO_Init(GPIOx,&GPIO_InitStruct);
}

void MyGPIO::gpio_init(Pin_enum pin, GpioMode mode, uint8_t select) {
    uint16_t gpio_pin = GPIO_PIN_0 << (pin & 0x0f);
    uint16_t gpio_port = (pin & 0xf0) >> 4;
    GPIO_TypeDef *GPIOx = (GPIO_TypeDef *)(GPIOA_BASE + 0x0400 * gpio_port);
    openCorrespondRCC(GPIOx);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = gpio_pin;
    GPIO_InitStruct.Mode = (uint32_t )mode;
    GPIO_InitStruct.Pull =((GpioExit)mode == GpioExit::it_falling) ?
                          (uint32_t)GpioPull::pullup : (uint32_t)GpioPull::pulldown;
    GPIO_InitStruct.Speed = (uint32_t)DEFAULT_GPIO_SPEED;
    GPIO_InitStruct.Alternate = select;
    HAL_GPIO_Init(GPIOx,&GPIO_InitStruct);
}

void MyGPIO::gpio_deinit(Pin_enum pin) {
    uint16_t gpio_pin = GPIO_PIN_0 << (pin & 0x0f);
    uint16_t gpio_port = (pin & 0xf0) >> 4;
    GPIO_TypeDef *GPIOx = (GPIO_TypeDef *)(GPIOA_BASE + 0x0400 * gpio_port);
    HAL_GPIO_DeInit(GPIOx,gpio_pin);
}

void MyGPIO::gpio_write(Pin_enum pin, uint8_t data) {
    uint16_t gpio_pin = GPIO_PIN_0 << (pin & 0x0f);
    uint16_t gpio_port = (pin & 0xf0) >> 4;
    GPIO_TypeDef *GPIOx = (GPIO_TypeDef *)(GPIOA_BASE + 0x0400 * gpio_port);
    HAL_GPIO_WritePin(GPIOx,gpio_pin,(GPIO_PinState)data);
}

uint8_t MyGPIO::gpio_read(Pin_enum pin) {
    uint16_t gpio_pin = GPIO_PIN_0 << (pin & 0x0f);
    uint16_t gpio_port = (pin & 0xf0) >> 4;
    GPIO_TypeDef *GPIOx = (GPIO_TypeDef *)(GPIOA_BASE + 0x0400 * gpio_port);
    return HAL_GPIO_ReadPin(GPIOx,gpio_pin);
}

void MyGPIO::gpio_toggle(Pin_enum pin) {
    uint16_t gpio_pin = GPIO_PIN_0 << (pin & 0x0f);
    uint16_t gpio_port = (pin & 0xf0) >> 4;
    GPIO_TypeDef *GPIOx = (GPIO_TypeDef *)(GPIOA_BASE + 0x0400 * gpio_port);
    HAL_GPIO_TogglePin(GPIOx,gpio_pin);
}

void MyGPIO::gpio_interrupt_init(Pin_enum pin, CallBack callBack, GpioExit mode,
                                 uint8_t PreemptPriority,uint8_t SubPriority) {
    uint16_t GPIO_PinSourcex =(pin & 0x0f);
    switch (mode)
    {
        case GpioExit::it_rising:
            gpio_init(pin,(GpioMode)GpioExit::it_rising ); //上升沿选择下拉输入
            break;
        case GpioExit::it_falling:
            gpio_init(pin, (GpioMode)GpioExit::it_falling); //下降沿选择上拉输入
            break;
        case GpioExit::it_rising_falling:
            gpio_init(pin, (GpioMode)GpioExit::it_rising_falling); //上升&下降沿选择浮空输入
            break;
        default:
            return;
    }
    auto exitx=get_exit_irqchannel(pin);
    HAL_NVIC_SetPriority((IRQn_Type)exitx, PreemptPriority, SubPriority);               /* 抢2，子优先级2 */
    HAL_NVIC_EnableIRQ((IRQn_Type)exitx);                       /* 使能中断线x */
    ExitFunc[GPIO_PinSourcex]=(callBack);
}

void MyGPIO::gpio_interrupt_deinit(Pin_enum pin) {
    uint16_t GPIO_PinSourcex =(pin & 0x0f);
    //不关掉中断 只把中断函数置为空指针
//    auto exitx=get_exit_irqchannel(pin);
//    HAL_NVIC_DisableIRQ((IRQn_Type)exitx);
    ExitFunc[GPIO_PinSourcex]= nullptr;
}


MyGPIO::~MyGPIO() {

}

uint8_t MyGPIO::get_exit_irqchannel(Pin_enum pin) {
    uint8_t pin_num = pin & 0x0f;
    if (pin_num <= 4)
    {
        return EXTI0_IRQn + pin_num;
    }
    else if (pin <= 9)
    {
        return EXTI9_5_IRQn;
    }
    else if (pin <= 15)
    {
        return EXTI15_10_IRQn;
    }
    else
    {
        return 0;
    }
}

MyGPIO::MyGPIO() {

}

void EXTI0_IRQHandler(void)
{
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
        if ( ExitFunc[0])
        ExitFunc[0]();
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
    }
}

void EXTI1_IRQHandler(void)
{
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_1) != RESET)
    {

        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
        if ( ExitFunc[1])
        ExitFunc[1]();
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
    }
}

void EXTI2_IRQHandler(void)
{
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_2) != RESET)
    {

        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2);
        if ( ExitFunc[2])
        ExitFunc[2]();
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2);
    }
}

void EXTI3_IRQHandler(void)
{
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_3) != RESET)
    {

        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
        if ( ExitFunc[3])
        ExitFunc[3]();
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
    }
}

void EXTI4_IRQHandler(void)
{
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_4) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
        if ( ExitFunc[4])
        ExitFunc[4]();
       __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
    }
}

void EXTI9_5_IRQHandler(void)
{
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_5) != RESET)
    {

        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
        if ( ExitFunc[5])
        ExitFunc[5]();
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_6) != RESET)
    {

        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);
        if ( ExitFunc[6])
        ExitFunc[6]();
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_7) != RESET)
    {

        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_7);
        if ( ExitFunc[7])
        ExitFunc[7]();
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_7);
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_8) != RESET)
    {

        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);
        if ( ExitFunc[8])
        ExitFunc[8]();
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_9) != RESET)
    {

        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);
        if ( ExitFunc[9])
        ExitFunc[9]();
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);
    }


}
void EXTI15_10_IRQHandler(){
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_10) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);
        if ( ExitFunc[10])
        ExitFunc[10]();
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_11) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);
        if ( ExitFunc[11])
        ExitFunc[11]();
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12);
        if ( ExitFunc[12])
        ExitFunc[12]();
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12);
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
        if ( ExitFunc[13])
        ExitFunc[13]();
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_14) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_14);
        if ( ExitFunc[14])
        ExitFunc[14]();
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_14);
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_15) != RESET)
    {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_15);
        if ( ExitFunc[15])
        ExitFunc[15]();
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_15);
    }
}

