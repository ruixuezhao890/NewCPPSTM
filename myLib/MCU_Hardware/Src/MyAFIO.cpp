/**
*********************************************************************
*********
* @project_name :car0
* @file : MyAFIO.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6 
*********************************************************************
*********
*/
//

#include "MyAFIO.h"
/**
* @brief 函数afio_init用于实现AFIO模式下的GPIO初始化
* @param pin GPIO引脚编号
* @param mode GPIO工作模式
*/
void MyAFIO::afio_init(Pin_enum pin, AFIO_mode mode) {
    // 获取GPIO引脚编号
    uint16_t gpio_pin = GPIO_PIN_0 << (pin & 0x0f);
    // 获取GPIO端口编号
    uint16_t gpio_port = (pin & 0xf0) >> 4;
    // 获取GPIOx指针
    GPIO_TypeDef *GPIOx = (GPIO_TypeDef *)(GPIOA_BASE + 0x0400 * gpio_port);
    // 打开对应的RCC
    openCorrespondRCC(GPIOx);
    // 初始化GPIO
    GPIO_InitTypeDef gpioInitTypeDef;
    gpioInitTypeDef.Pin = gpio_pin;
    gpioInitTypeDef.Mode = (uint32_t)mode;
    gpioInitTypeDef.Speed=(uint32_t)DEFAULT_GPIO_SPEED;
    HAL_GPIO_Init(GPIOx,&gpioInitTypeDef);
}
