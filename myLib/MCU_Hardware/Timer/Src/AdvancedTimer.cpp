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
    auto ret=timerGreatPscNoInit(timer, psc, arr, PreemptPriority, SubPriority);
    HAL_TIM_Base_Init(ret);
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

void AdvancedTimer::setOutputCompareGreat(Timer_enum timer, uint32_t psc, uint32_t arr, uint8_t PreemptPriority,
                                          uint8_t SubPriority) {
    auto temp= MyUniversalTimer::timerGreatPscNoInit(timer, psc, arr, PreemptPriority, SubPriority);
    temp->Init.AutoReloadPreload=TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_Base_Init(&BaseTimeValue.TIMEList[timer]);
    HAL_TIM_OC_Init(&BaseTimeValue.TIMEList[timer]);

}

void AdvancedTimer::startOutputCompare(Timer_enum timer, uint16_t PluseNum, uint8_t TIMExPWM_Channel) {
    TIM_OC_InitTypeDef timx_oc_comp_pwm = {0};
    timx_oc_comp_pwm.OCMode = TIM_OCMODE_TOGGLE;                        /* 比较输出模式翻转功能 */
    timx_oc_comp_pwm.Pulse = PluseNum - 1;                                   /* 设置输出比较寄存器的值 */
    timx_oc_comp_pwm.OCPolarity = TIM_OCPOLARITY_HIGH;                  /* 输出比较极性为高 */
    HAL_TIM_OC_ConfigChannel(&BaseTimeValue.TIMEList[timer], &timx_oc_comp_pwm, TIMExPWM_Channel); /* 初始化定时器的输出比较通道x */
    __HAL_TIM_ENABLE_OCxPRELOAD(&BaseTimeValue.TIMEList[timer], TIMExPWM_Channel);                 /* 通道x 预装载使能 */
    HAL_TIM_OC_Start(&BaseTimeValue.TIMEList[timer], TIMExPWM_Channel);
}

void AdvancedTimer::stopOutputCompare(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    HAL_TIM_OC_Stop(&BaseTimeValue.TIMEList[timer], TIMExPWM_Channel);
}

void AdvancedTimer::deleteOutputCompare(Timer_enum timer) {
    HAL_TIM_OC_DeInit(&BaseTimeValue.TIMEList[timer]);
}

void AdvancedTimer::timerOutputCompareMultiplexPin(Pin_enum pin, uint8_t Alternate) {
    UniversalAFIO.gpio_init(pin,GpioMode::af_pp,GpioPull::nopull,Alternate);
}



void AdvancedTimer::deadZoneGreat(Timer_enum timer, uint32_t psc, uint32_t arr, uint8_t PreemptPriority,
                                  uint8_t SubPriority){

    auto ret=MyUniversalTimer::timerGreatPscNoInit(timer,psc,arr,PreemptPriority,SubPriority);
    ret->Init.ClockDivision=TIM_CLOCKDIVISION_DIV4;
    ret->Init.AutoReloadPreload=TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_PWM_Init(ret);

}

void AdvancedTimer::deadZoneMultiplexPin(Pin_enum pin, uint8_t Alternate) {
    UniversalAFIO.gpio_init(pin,GpioMode::af_pp,GpioPull::pulldown,Alternate);
}

void AdvancedTimer::startdeadZone(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    TIM_OC_InitTypeDef tim_oc_cplm_pwm = {0};
    tim_oc_cplm_pwm.OCMode = TIM_OCMODE_PWM1;                               /* PWM模式1 */
    tim_oc_cplm_pwm.OCPolarity = TIM_OCPOLARITY_HIGH;                       /* OCy 高电平有效 */
    tim_oc_cplm_pwm.OCNPolarity = TIM_OCPOLARITY_HIGH;                      /* OCyN 高电平有效 */
    tim_oc_cplm_pwm.OCIdleState = TIM_OCIDLESTATE_SET;                      /* 当MOE=0，OCx=0 */
    tim_oc_cplm_pwm.OCNIdleState = TIM_OCNIDLESTATE_SET;                    /* 当MOE=0，OCxN=0 */
    HAL_TIM_PWM_ConfigChannel(&BaseTimeValue.TIMEList[timer], &tim_oc_cplm_pwm, TIMExPWM_Channel);
    g_sbreak_dead_time_config.OffStateRunMode = TIM_OSSR_DISABLE;           /* 运行模式的关闭输出状态 */
    g_sbreak_dead_time_config.OffStateIDLEMode = TIM_OSSI_DISABLE;          /* 空闲模式的关闭输出状态 */
    g_sbreak_dead_time_config.LockLevel = TIM_LOCKLEVEL_OFF;                /* 不用寄存器锁功能 */
    g_sbreak_dead_time_config.BreakState = TIM_BREAK_ENABLE;                /* 使能刹车输入 */
    g_sbreak_dead_time_config.BreakPolarity = TIM_BREAKPOLARITY_HIGH;       /* 刹车输入有效信号极性为高 */
    g_sbreak_dead_time_config.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE; /* 使能AOE位，允许刹车结束后自动恢复输出 */
    HAL_TIMEx_ConfigBreakDeadTime(&BaseTimeValue.TIMEList[timer], &g_sbreak_dead_time_config);
    HAL_TIM_PWM_Start(&BaseTimeValue.TIMEList[timer], TIMExPWM_Channel);         /* OCy 输出使能 */
    HAL_TIMEx_PWMN_Start(&BaseTimeValue.TIMEList[timer], TIMExPWM_Channel);      /* OCyN 输出使能 */
}

void AdvancedTimer::stopdeadZone(Timer_enum timer, uint8_t TIMExPWM_Channel) {
    HAL_TIM_PWM_Stop(&BaseTimeValue.TIMEList[timer], TIMExPWM_Channel);         /* OCy 输出使能 */
    HAL_TIMEx_PWMN_Stop(&BaseTimeValue.TIMEList[timer], TIMExPWM_Channel);      /* OCyN 输出使能 */
}

void AdvancedTimer::deletedeadZone(Timer_enum timer) {
    HAL_TIM_PWM_DeInit(&BaseTimeValue.TIMEList[timer]);         /* OCy 输出使能 */
}

void AdvancedTimer::setPWMdeadZone(Timer_enum timer, uint16_t ccr, uint8_t dtg) {
    g_sbreak_dead_time_config.DeadTime = dtg;
    HAL_TIMEx_ConfigBreakDeadTime(&BaseTimeValue.TIMEList[timer], &g_sbreak_dead_time_config);      /*重设死区时间*/
    __HAL_TIM_MOE_ENABLE(&BaseTimeValue.TIMEList[timer]);      /* MOE=1,使能主输出 */
    BaseTimeValue.TIMEList[timer].Instance->CCR1 = ccr;                      /* 设置比较寄存器 */
}


