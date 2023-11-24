/**
*********************************************************************
*********
* @project_name :car0
* @file : AdvancedTimer.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/23 
*********************************************************************
*********
*/
//

#include "AdvancedTimer.h"
#include "timeIT.h"
void AdvancedTimer::setOutputPWMNum(Timer_enum timer, uint32_t NumPWM) {
    if (NumPWM == 0) return;
    g_npwm_remain = NumPWM;                                                   /* 保存脉冲个数 */
    HAL_TIM_GenerateEvent(&BaseTimeValue.TIMEList[timer], TIM_EVENTSOURCE_UPDATE); /* 产生一次更新事件,在中断里面处理脉冲输出 */
    __HAL_TIM_ENABLE(&BaseTimeValue.TIMEList[timer]);                              /* 使能定时器TIMX */
}

void AdvancedTimer::setOutputPWMNumGreat(Timer_enum timer, uint32_t psc, uint32_t arr, uint8_t TIMExPWM_Channel,
                                         uint8_t PreemptPriority, uint8_t SubPriority) {
    timerGreatPsc(timer,psc,arr,PreemptPriority,SubPriority);
    setHighLeveFlag(1);//设置比较极性为高
    timerPWMGreat(timer,TIMExPWM_Channel,0.5);
    __HAL_TIM_ENABLE_IT(&BaseTimeValue.TIMEList[timer],TIM_IT_UPDATE);
}

void AdvancedTimer::startOutputPWMNum(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    HAL_TIM_PWM_Start(&BaseTimeValue.TIMEList[timer],TIMExPWM_Channel);
}

void AdvancedTimer::stopOutputPWMNum(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    HAL_TIM_PWM_Stop(&BaseTimeValue.TIMEList[timer],TIMExPWM_Channel);
}

void AdvancedTimer::deleteOutputPWMNum(Timer_enum timer) {
    HAL_TIM_PWM_DeInit(&BaseTimeValue.TIMEList[timer]);
}
