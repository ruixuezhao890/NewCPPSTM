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


#include "GPIOResources.h"

/**
 * @brief GPIO抽象类，用于定义通用的GPIO操作接口。
 */
using CallBack = void(*)(void);

class virGPIO {
protected:
    /**
     * @brief 保护构造函数，防止直接实例化该类。
     */
    virGPIO();

public:
    /**
     * @brief 初始化GPIO引脚。
     * @param pin 选择的GPIO引脚。
     * @param mode GPIO模式。
     */
    virtual void gpio_init(Pin_enum pin, GpioMode mode) = 0;

    /**
     * @brief 初始化GPIO引脚，可额外指定引脚的其他配置。
     * @param pin 选择的GPIO引脚。
     * @param mode GPIO模式。
     * @param select 其他引脚配置。
     */
    virtual void gpio_init(Pin_enum pin, GpioMode mode, uint8_t select) = 0;

    virtual void gpio_init(Pin_enum pin, GpioMode mode,GpioPull pull, uint8_t select) = 0;

    /**
     * @brief 复位GPIO引脚的配置。
     * @param pin 选择的GPIO引脚。
     */
    virtual void gpio_deinit(Pin_enum pin) = 0;

    /**
     * @brief 设置GPIO引脚的输出状态。
     * @param pin 选择的GPIO引脚。
     * @param data 输出数据，可以是0或1。
     */
    virtual void gpio_write(Pin_enum pin, uint8_t data) = 0;

    /**
     * @brief 切换GPIO引脚的输出状态。
     * @param pin 选择的GPIO引脚。
     */
    virtual void gpio_toggle(Pin_enum pin) = 0;

    /**
     * @brief 初始化GPIO引脚中断。
     * @param pin 选择的GPIO引脚。
     * @param callBack 中断回调函数。
     * @param mode 中断触发模式。
     * @param PreemptPriority 中断抢占优先级。
     * @param SubPriority 中断响应优先级。
     */
    virtual void gpio_interrupt_init(Pin_enum pin, CallBack callBack, GpioExit mode,
                                     uint8_t PreemptPriority, uint8_t SubPriority) = 0;

    /**
     * @brief 复位GPIO引脚的中断配置。
     * @param pin 选择的GPIO引脚。
     */
    virtual void gpio_interrupt_deinit(Pin_enum pin) = 0;

    /**
     * @brief 读取GPIO引脚的输入状态。
     * @param pin 选择的GPIO引脚。
     * @return 输入状态，可以是0或1。
     */
    virtual uint8_t gpio_read(Pin_enum pin) = 0;

    /**
     * @brief 虚构函数，确保派生类的正确清理。
     */
    virtual ~virGPIO();
};


extern CallBack ExitFunc[16];
#endif //CAR0_VIRGPIO_H
