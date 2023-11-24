/**
*********************************************************************
*********
* @project_name :car0
* @file : timeIT.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/20 
*********************************************************************
*********
*/
//

#ifndef CAR0_TIMEIT_H
#define CAR0_TIMEIT_H
#include "Resources.h"
extern uint8_t g_timxchy_cap_sta;
extern uint16_t g_timxchy_cap_val;
extern uint8_t CurrentCaptureTimer;
extern uint8_t CurrentCounterTimer;
extern uint8_t CurrentCaptureTimerChannel;
extern uint32_t g_timxchy_cnt_ofcnt;
extern uint32_t g_npwm_remain;
void CaptureStatusSwitch();
void CounterPulseNum();
void OutputCounterNUm();
extern "C"{
void TIM1_BRK_TIM9_IRQHandler(void);
void TIM1_UP_TIM10_IRQHandler(void);
void TIM1_TRG_COM_TIM11_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM5_IRQHandler(void);
void TIM6_DAC_IRQHandler(void);
void TIM7_IRQHandler(void);
void TIM8_BRK_TIM12_IRQHandler(void);
void TIM8_UP_TIM13_IRQHandler(void);
void TIM8_TRG_COM_TIM14_IRQHandler();
}


#endif //CAR0_TIMEIT_H
