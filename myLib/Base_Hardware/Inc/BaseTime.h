/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseTime.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/11 
*********************************************************************
*********
*/
//

#ifndef CAR0_BASETIME_H
#define CAR0_BASETIME_H
#include "headfile.h"

class BaseTime {
private:
    GenericTIMMode m_genericMode;
    Timer_enum time_x;
public:
    BaseTime(Timer_enum timer);
   int beginBaseTime(uint32_t arr, uint32_t psc);
/**
* @brief 初始化定时器 PWM 通道并配置相应的 GPIO。
*
* @param timer 选择的定时器。
* @param arr 定时器自动装载寄存器的值，影响 PWM 周期。
* @param psc 定时器预分频值，影响 PWM 频率。
* @param genericMode 泛型定时器模式，包含 PWM 通道的相关配置信息。
*
* @note 该函数初始化定时器的 PWM 通道，并配置与之关联的 GPIO。
*       使用前需要确保相关的定时器和 GPIO 初始化已完成。
*
* @code
* // 示例用法:
 * BaseTime baseTime(TIMER_14);
 * GenericTIMMode genericTimMode={GenericMode::TIME_PWM,F9,GPIO_AF9_TIM14,TIM_CHANNEL_1};
 * baseTime.beginGenericTime(500-1,84-1,genericTimMode);*/

int beginGenericTime(uint32_t arr, uint32_t psc, GenericTIMMode genericMode);
int beginAdvancedTime(uint32_t arr, uint32_t psc);
int TimeStart();
int TimeStop();
int TimeReset();
uint32_t TimeGetCurrentFrequency();
uint32_t TimeGetCurrentValue();
uint32_t TimeGetRemainingTime();
void TimeSetCallBack(CallBack callBack);
void TimeClearCallBack();
//Pwm相关
    uint32_t TimePWM_getFrequency() const;
    float TimePWM_getDutyCycle() const;
    void TimePWM_setPhase(float phase);
    void TimePWM_setPulseWidth(uint32_t pulse_width);
    void TimePWM_start();
    void TimePWM_stop();
    void TimePWM_set_duty_cycle(uint16_t duty_cycle);
    uint32_t TimeCaputerHigihLevel();



};


#endif //CAR0_BASETIME_H
