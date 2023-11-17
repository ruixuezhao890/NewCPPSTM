/**
*********************************************************************
*********
* @project_name ：car0
* @file ：virTime.h
* @author ：zen3
* @brief ：这个头文件定义了抽象类virTime，作为定时器和PWM功能的接口。
* @attention ：无
* @date ：2023/11/9
*********************************************************************
*********
*/

#ifndef CAR0_VIRTIME_H
#define CAR0_VIRTIME_H

#include "Resources.h"
struct GenericTIMMode{
    GenericMode genericMode;
    Pin_enum pwmChannelIO;
    Pin_enum CaptureChannelIO;
    Pin_enum CounterChannelIO;
    AlternateIO alternateMode;
    uint8_t Tim_Channel;
    uint8_t Tim_CaptureChannel;
};
struct  AdvancedTIMMode{
    AdvancedMode advancedMode;
};
class virTime {
protected:
    /**
   * @brief 保护构造函数，防止直接实例化该类。
   */
    virTime();
public:
    /**
     * @brief 初始化基础定时器，使用指定的参数。
     * @param timer 选择的定时器。
     * @param arr 定时器计数器的初始值。
     * @param period 定时器的周期。
     */
    virtual void timer_BasicTimerInit(Timer_enum timer, uint32_t arr, uint32_t psc) = 0;

    /**
     * @brief 初始化通用定时器，使用指定的参数。
     * @param timer 选择的定时器。
     * @param arr 定时器计数器的初始值。
     * @param period 定时器的周期。
     */
    virtual void timer_GenericTimerInit(Timer_enum timer, uint32_t arr, uint32_t psc,
                                        GenericTIMMode genericMode) = 0;

    /**
     * @brief 初始化高级定时器，使用指定的参数。
     * @param timer 选择的定时器。
     * @param arr 定时器计数器的初始值。
     * @param period 定时器的周期。
     */
    virtual void timer_AdvancedTimerInit(Timer_enum timer, uint32_t arr, uint32_t psc,
                                         AdvancedTIMMode advancedMode) = 0;

    /**
     * @brief 启动指定的定时器。
     * @param timer 要启动的选择的定时器。
     */
    virtual void timer_start(Timer_enum timer) = 0;

    /**
     * @brief 停止指定的定时器。
     * @param timer 要停止的选择的定时器。
     */
    virtual void timer_stop(Timer_enum timer) = 0;

    /**
     * @brief 重置指定的定时器。
     * @param timer 要重置的选择的定时器。
     */
    virtual void timer_reset(Timer_enum timer) = 0;

    /**
     * @brief 检查指定的定时器是否正在运行。
     * @param timer 选择的定时器。
     * @return 如果定时器正在运行，则为true；否则为false。
     */
    virtual bool timer_is_running(Timer_enum timer) = 0;

    /**
     * @brief 获取定时器计数器的当前值。
     * @param timer 选择的定时器。
     * @return 定时器计数器的当前值。
     */
    virtual uint32_t timer_getCurrentValue(Timer_enum timer) = 0;

    /**
     * @brief 获取指定定时器的周期。
     * @param timer 选择的定时器。
     * @return 定时器的周期（HZ）。
     */
    virtual uint32_t timer_getPeriod(Timer_enum timer) = 0;

    /**
     * @brief 获取距离下一次定时器触发还剩多少时间。
     * @param timer 选择的定时器。
     * @return 距离下一次触发的剩余时间。
     */
    virtual uint32_t timer_getRemainingTime(Timer_enum timer) = 0;

    /**
     * @brief 为指定的定时器设置回调函数。
     * @param timer 选择的定时器。
     * @param callback 要设置的回调函数。
     */
    virtual void timer_set_callback(Timer_enum timer, void (*callback)()) = 0;

    /**
     * @brief 清除指定定时器的回调函数。
     * @param timer 选择的定时器。
     */
    virtual void timer_clear_callback(Timer_enum timer) = 0;

    // 与PWM相关的函数

   /* /**
     * @brief 在指定的定时器上使用给定的频率和占空比初始化PWM。
     * @param timer 选择的定时器。
     * @param frequency 期望的PWM输出频率。
     * @param duty_cycle PWM信号的初始占空比。
     *//*
    virtual void pwm_init(Timer_enum timer, uint32_t frequency, float duty_cycle) = 0;*/

    /**
     * @brief 获取指定定时器上PWM信号的当前频率。
     * @param timer 选择的定时器。
     * @return PWM信号的当前频率。
     */
    virtual uint32_t pwm_getFrequency(Timer_enum timer) const = 0;

/**
 * @brief 获取指定定时器上PWM信号的当前占空比。
 * @param timer 选择的定时器。
 * @param setData 用于占空比计算的数据。
 * @param genericMode 泛型定时器模式。
 * @return PWM信号的当前占空比。
 */
    virtual float pwm_getDutyCycle(Timer_enum timer, GenericTIMMode genericMode) const = 0;

/**
 * @brief 设置指定定时器上PWM信号的相位。
 * @param timer 选择的定时器。
 * @param phase 所需的PWM信号相位。
 * @param genericMode 泛型定时器模式。
 */
    virtual void pwm_setPhase(Timer_enum timer, float phase, GenericTIMMode genericMode) = 0;

/**
 * @brief 设置指定定时器上PWM信号的脉宽。
 * @param timer 选择的定时器。
 * @param pulse_width 所需的PWM信号脉宽。
 * @param genericMode 泛型定时器模式。
 */
    virtual void pwm_setPulseWidth(Timer_enum timer, uint32_t pulse_width, GenericTIMMode genericMode) = 0;

/**
 * @brief 启动指定定时器上的PWM输出。
 * @param timer 选择的定时器。
 * @param genericMode 泛型定时器模式。
 */
    virtual void pwm_start(Timer_enum timer, GenericTIMMode genericMode) = 0;

/**
 * @brief 停止指定定时器上的PWM输出。
 * @param timer 选择的定时器。
 * @param genericMode 泛型定时器模式。
 */
    virtual void pwm_stop(Timer_enum timer, GenericTIMMode genericMode) = 0;

/**
 * @brief 设置指定定时器上PWM信号的占空比。
 * @param timer 选择的定时器。
 * @param duty_cycle 所需的PWM信号占空比。
 * @param genericMode 泛型定时器模式。
 */
    virtual void pwm_set_duty_cycle(Timer_enum timer, uint16_t duty_cycle, GenericTIMMode genericMode) = 0;

/**
 * @brief 为指定定时器上的PWM信号设置回调函数。
 * @param timer 选择的定时器。
 * @param callback 要设置的回调函数。
 * @param genericMode 泛型定时器模式。
 */
    virtual void pwm_setInterruptCallback(Timer_enum timer, void (*callback)(void), GenericTIMMode genericMode) = 0;

    virtual uint32_t CaptureHighLevelTime();
};
#endif