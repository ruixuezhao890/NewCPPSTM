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
#include "timeIT.h"

uint32_t MyUniversalTimer::timerGreatPsc(Timer_enum timer, uint32_t arr, uint8_t PreemptPriority, uint8_t SubPriority) {
    m_arr=MyBaseTime::timerGreatPsc(timer, arr, PreemptPriority, SubPriority);
    return m_arr;
}
TIM_HandleTypeDef MyUniversalTimer::timerGreatPsc(Timer_enum timer, uint32_t psc, uint32_t arr, uint8_t PreemptPriority,
                                                  uint8_t SubPriority) {

    auto temp=MyBaseTime::timerGreatPsc(timer, psc, arr, PreemptPriority, SubPriority);
    m_arr=temp.Init.Period;
    return   temp;

}
void MyUniversalTimer::timerPWMGreat(Timer_enum timer, uint8_t TIMExPWM_Channel, float dutyCycle) {
    if (dutyCycle>1) return;
    TIM_OC_InitTypeDef timx_oc_pwm_chy = {0};                       /* 定时器输出句柄 */
    timx_oc_pwm_chy.OCMode = TIM_OCMODE_PWM1;                       /* 模式选择PWM1 */
    timx_oc_pwm_chy.Pulse = uint32_t ((float )m_arr *dutyCycle);/* 设置比较值,此值用来确定占空比 */
    if (HighLeveFlag)timx_oc_pwm_chy.OCPolarity = TIM_OCPOLARITY_HIGH;
    else timx_oc_pwm_chy.OCPolarity = TIM_OCPOLARITY_LOW;
    HAL_TIM_PWM_ConfigChannel(&BaseTimeValue.TIMEList[timer],&timx_oc_pwm_chy,TIMExPWM_Channel);
}

void MyUniversalTimer::startPWMPeriodic(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    HAL_TIM_PWM_Start(&BaseTimeValue.TIMEList[timer],TIMExPWM_Channel);
}

void MyUniversalTimer::stopPWM(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    HAL_TIM_PWM_Stop(&BaseTimeValue.TIMEList[timer],TIMExPWM_Channel);
}

void MyUniversalTimer::deletePWMTimer(Timer_enum timer) {
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

/*Capture相关的函数接口*/
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

uint32_t MyUniversalTimer::getCaptureHighLevel() {
    uint32_t temp=0;
    if (g_timxchy_cap_sta & 0x80)           /* 成功捕获到了一次高电平 */
    {
        temp = g_timxchy_cap_sta & 0x3F;
        temp *= 0xFFFF;                     /* 溢出时间总和 */
        temp += g_timxchy_cap_val;          /* 得到总的高电平时间 */
        g_timxchy_cap_sta = 0;              /* 开启下一次捕获 */
    }
    return temp;
}
/*脉冲计数相关代码*/
void MyUniversalTimer::timerPulseCounterGreat(Timer_enum timer, uint32_t psc, uint32_t arr, uint8_t PreemptPriority,
                                              uint8_t SubPriority) {
   auto ret=MyBaseTime::timerGreatPsc(timer,psc,arr,PreemptPriority,SubPriority);
    HAL_TIM_IC_Init(&ret);
}

void MyUniversalTimer::timerPulseCounterMultiplexPin(Pin_enum pin, uint8_t Alternate) {
    UniversalAFIO.gpio_init(pin,GpioMode::af_pp,GpioPull::pulldown,Alternate);
}

void MyUniversalTimer::timerPulseCounterStart(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    TIM_SlaveConfigTypeDef tim_slave_config = {0};
    tim_slave_config.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;                  /* 从模式：外部触发模式1 */
    tim_slave_config.InputTrigger = TIM_TS_TI1FP1;                         /* 输入触发：选择 TI1FP1(TIMX_CH1) 作为输入源 */
    tim_slave_config.TriggerPolarity = TIM_TRIGGERPOLARITY_RISING;         /* 触发极性：上升沿 */
    tim_slave_config.TriggerPrescaler = TIM_TRIGGERPRESCALER_DIV1;         /* 触发预分频：无 */
    tim_slave_config.TriggerFilter = 0x0;                                  /* 滤波：本例中不需要任何滤波 */
    HAL_TIM_SlaveConfigSynchronization(&BaseTimeValue.TIMEList[timer], &tim_slave_config);
    __HAL_TIM_ENABLE_IT(&BaseTimeValue.TIMEList[timer],TIM_IT_UPDATE);
    HAL_TIM_IC_Start(&BaseTimeValue.TIMEList[timer], TIMExPWM_Channel);
}

void MyUniversalTimer::timerPulseCounterStop(Timer_enum timer, uint8_t TIMExPWM_Channel) {

}

void MyUniversalTimer::timerPulseCounterDelete(Timer_enum timer, uint8_t TIMExPWM_Channel) {

}

void MyUniversalTimer::timerPulseCounterRestart(Timer_enum timer) {
    __HAL_TIM_DISABLE(&BaseTimeValue.TIMEList[timer]);          /* 关闭定时器TIMX */
    g_timxchy_cnt_ofcnt = 0;                            /* 累加器清零 */
    __HAL_TIM_SET_COUNTER(&BaseTimeValue.TIMEList[timer], 0);   /* 计数器清零 */
    __HAL_TIM_ENABLE(&BaseTimeValue.TIMEList[timer]);           /* 使能定时器TIMX */
}

uint32_t MyUniversalTimer::timerPulseCounterCount(Timer_enum timer) {
    uint32_t count = 0;
    count = g_timxchy_cnt_ofcnt * 65536;                    /* 计算溢出次数对应的计数值 */
    count += __HAL_TIM_GET_COUNTER(&BaseTimeValue.TIMEList[timer]); /* 加上当前CNT的值 */
//    printf("gtim_timx count %d \r\n", count);
    return count;
}

void MyUniversalTimer::setHighLeveFlag(uint8_t flag) {
    HighLeveFlag=flag;
}


