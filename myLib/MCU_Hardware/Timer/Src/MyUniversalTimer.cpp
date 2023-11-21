/**
*********************************************************************
*********
* @project_name :car0
* @file : MyUniversalTimer.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/21 
*********************************************************************
*********
*/
//

#include "MyUniversalTimer.h"

uint32_t MyUniversalTimer::timerGreatPsc(Timer_enum timer, uint32_t arr, uint8_t PreemptPriority, uint8_t SubPriority) {
    m_arr=MyBaseTime::timerGreatPsc(timer, arr, PreemptPriority, SubPriority);
    return m_arr;
}

void MyUniversalTimer::timerPWMGreat(Timer_enum timer, uint8_t TIMExPWM_Channel, uint8_t dutyCycle) {
    TIM_OC_InitTypeDef timx_oc_pwm_chy = {0};                       /* 定时器输出句柄 */
    timx_oc_pwm_chy.OCMode = TIM_OCMODE_PWM1;                       /* 模式选择PWM1 */
    timx_oc_pwm_chy.Pulse = m_arr /dutyCycle;                                /* 设置比较值,此值用来确定占空比 */
    timx_oc_pwm_chy.OCPolarity = TIM_OCPOLARITY_LOW;
    HAL_TIM_PWM_ConfigChannel(&BaseTimeValue.TIMEList[timer],&timx_oc_pwm_chy,TIMExPWM_Channel);
}

void MyUniversalTimer::startPWMPeriodic(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    HAL_TIM_PWM_Start(&BaseTimeValue.TIMEList[timer],TIMExPWM_Channel);
}

void MyUniversalTimer::stopPWM(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    HAL_TIM_PWM_Stop(&BaseTimeValue.TIMEList[timer],TIMExPWM_Channel);
}

void MyUniversalTimer::deleteTimer(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    if (!BaseTimeValue.TIMEList[timer].Instance){
        return;
    }
    HAL_TIM_PWM_DeInit(&BaseTimeValue.TIMEList[timer]);
}

void MyUniversalTimer::timerPWMMultiplexPin(Pin_enum pin, uint8_t Alternate) {
    PWMAFIO.gpio_init(pin,GpioMode::af_pp,GpioPull::pullup,Alternate);
}

void MyUniversalTimer::setPWMDutyCycle(uint32_t dutyCycle, Timer_enum timer, uint8_t TIMExPWM_Channel) {
    __HAL_TIM_SetCompare(&BaseTimeValue.TIMEList[timer],TIMExPWM_Channel,dutyCycle);
}
