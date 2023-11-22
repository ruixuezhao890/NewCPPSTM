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
TIM_HandleTypeDef MyUniversalTimer::timerGreatPsc(Timer_enum timer, uint32_t psc, uint32_t arr, uint8_t PreemptPriority,
                                                  uint8_t SubPriority) {
   auto temp=MyBaseTime::timerGreatPsc(timer, psc, arr, PreemptPriority, SubPriority);
    return temp ;
}
void MyUniversalTimer::timerPWMGreat(Timer_enum timer, uint8_t TIMExPWM_Channel, float dutyCycle) {
    if (dutyCycle>1) return;
    TIM_OC_InitTypeDef timx_oc_pwm_chy = {0};                       /* 定时器输出句柄 */
    timx_oc_pwm_chy.OCMode = TIM_OCMODE_PWM1;                       /* 模式选择PWM1 */
    timx_oc_pwm_chy.Pulse = uint32_t ((float )m_arr *dutyCycle);                                /* 设置比较值,此值用来确定占空比 */
    timx_oc_pwm_chy.OCPolarity = TIM_OCPOLARITY_LOW;
    HAL_TIM_PWM_ConfigChannel(&BaseTimeValue.TIMEList[timer],&timx_oc_pwm_chy,TIMExPWM_Channel);
}

void MyUniversalTimer::startPWMPeriodic(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    HAL_TIM_PWM_Start(&BaseTimeValue.TIMEList[timer],TIMExPWM_Channel);
}

void MyUniversalTimer::stopPWM(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    HAL_TIM_PWM_Stop(&BaseTimeValue.TIMEList[timer],TIMExPWM_Channel);
}

void MyUniversalTimer::deletePWMTimer(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    if (!BaseTimeValue.TIMEList[timer].Instance){
        return;
    }
    HAL_TIM_PWM_DeInit(&BaseTimeValue.TIMEList[timer]);
}

void MyUniversalTimer::timerPWMMultiplexPin(Pin_enum pin, uint8_t Alternate) {
    UniversalAFIO.gpio_init(pin, GpioMode::af_pp, GpioPull::pullup, Alternate);
}

void MyUniversalTimer::setPWMDutyCycle(uint32_t dutyCycle, Timer_enum timer, uint8_t TIMExPWM_Channel) {
    __HAL_TIM_SetCompare(&BaseTimeValue.TIMEList[timer],TIMExPWM_Channel,dutyCycle);
}

void MyUniversalTimer::timerCaptureGreat(Timer_enum timer, uint32_t psc, uint32_t arr, uint8_t PreemptPriority,
                                         uint8_t SubPriority) {

   auto ret=MyBaseTime::timerGreatPsc(timer,psc,arr,PreemptPriority,SubPriority);
    HAL_TIM_IC_Init(&ret);

}

void MyUniversalTimer::timerCaptureMultiplexPin(Pin_enum pin, uint8_t Alternate) {
    UniversalAFIO.gpio_init(pin,GpioMode::af_pp,GpioPull::pulldown,Alternate);
}

void MyUniversalTimer::startCapturePeriodic(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    TIM_IC_InitTypeDef timIcInitTypeDef;
    timIcInitTypeDef.ICPolarity = TIM_ICPOLARITY_RISING;
    timIcInitTypeDef.ICSelection = TIM_ICSELECTION_DIRECTTI;
    timIcInitTypeDef.ICPrescaler=TIM_ICPSC_DIV1;
    timIcInitTypeDef.ICFilter=0;
    HAL_TIM_IC_ConfigChannel(&BaseTimeValue.TIMEList[timer],&timIcInitTypeDef,TIMExPWM_Channel);
    __HAL_TIM_ENABLE_IT(&BaseTimeValue.TIMEList[timer],TIM_IT_UPDATE);
    HAL_TIM_IC_Start_IT(&BaseTimeValue.TIMEList[timer],TIMExPWM_Channel);
}

void MyUniversalTimer::stopCapture(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    HAL_TIM_IC_Stop(&BaseTimeValue.TIMEList[timer],TIMExPWM_Channel);
}

void MyUniversalTimer::deleteCaptureTimer(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    if (!BaseTimeValue.TIMEList[timer].Instance){
        return;
    }
    HAL_TIM_IC_DeInit(&BaseTimeValue.TIMEList[timer]);
}


