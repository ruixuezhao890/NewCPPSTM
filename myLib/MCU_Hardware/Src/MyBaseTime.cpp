/**
*********************************************************************
*********
* @project_name :car0
* @file : MyBaseTime.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/10
*********************************************************************
*********
*/
//

#include "MyBaseTime.h"
#include "BaseSerial.h"
#include "TimeAuxiliaryfunction.h"
virTimeValue *timeValue=&BaseTimeValue;
uint8_t OnceFlag[MAXTIMNUM]={0};
void MyBaseTime::timerGreatPsc(Timer_enum timer, uint32_t arr,
                               uint8_t PreemptPriority, uint8_t SubPriority) {
    OpenRccTime(timer);
    uint32_t PreNum;
    if (timer == Timer_enum::TIMER_1) {
        PreNum = HAL_RCC_GetPCLK2Freq();
    } else {
        PreNum = HAL_RCC_GetPCLK1Freq()*2;
    }
    PreNum=(PreNum*(arr/1000)/65000);
    timeValue->TIMEx_IRQn[timer]= getTIMEx_IRQn(timer);
    timeValue->TIMEList[timer].Instance=( TIM_TypeDef*)getTimeInstance(timer);
    timeValue->TIMEList[timer].Init.Prescaler=65000-1;
    timeValue->TIMEList[timer].Init.CounterMode=TIM_COUNTERMODE_UP;
    timeValue->TIMEList[timer].Init.Period=PreNum;
    HAL_TIM_Base_Init(&timeValue->TIMEList[timer]);
    HAL_NVIC_SetPriority((IRQn_Type)timeValue->TIMEx_IRQn[timer], PreemptPriority, SubPriority);
    HAL_NVIC_EnableIRQ((IRQn_Type)timeValue->TIMEx_IRQn[timer]);

}
void MyBaseTime::timerStop(Timer_enum timer) {
    HAL_TIM_Base_Stop_IT(&timeValue->TIMEList[timer]);
}

void MyBaseTime::timerDelete(Timer_enum timer) {
    HAL_TIM_Base_DeInit(&timeValue->TIMEList[timer]);
}

void MyBaseTime::timerStartOnce(Timer_enum timer) {

    HAL_TIM_Base_Start_IT(&timeValue->TIMEList[timer]);
    OnceFlag[timer]=1;
}

void MyBaseTime::timerStartPeriodic(Timer_enum timer) {

   HAL_TIM_Base_Start_IT(&timeValue->TIMEList[timer]);
    OnceFlag[timer]=0;

}

