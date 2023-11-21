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
uint32_t MyBaseTime::timerGreatPsc(Timer_enum timer, uint32_t arr,
                                   uint8_t PreemptPriority, uint8_t SubPriority) {
    OpenRccTime(timer);
    uint32_t PreNum;
    if (timer == Timer_enum::TIMER_1||(timer>=Timer_enum::TIMER_8&&timer<=Timer_enum::TIMER_11)) {
        PreNum = HAL_RCC_GetPCLK2Freq()*2;//获取定时器的最大频率 此时单片机以最大的频率运行，如果定时时间不正确可以
        //将这里的*2去掉 下面也是如此
    } else {
        PreNum = HAL_RCC_GetPCLK1Freq()*2;
    }
    PreNum=(PreNum*(arr/1000)/65535);//自动计算arr
    timeValue->TIMEx_IRQn[timer]= getTIMEx_IRQn(timer);
    timeValue->TIMEList[timer].Instance=( TIM_TypeDef*)getTimeInstance(timer);
    timeValue->TIMEList[timer].Init.Prescaler=65535-1;
    timeValue->TIMEList[timer].Init.CounterMode=TIM_COUNTERMODE_UP;
    timeValue->TIMEList[timer].Init.Period=PreNum;
    HAL_TIM_Base_Init(&timeValue->TIMEList[timer]);
    HAL_NVIC_SetPriority((IRQn_Type)timeValue->TIMEx_IRQn[timer], PreemptPriority, SubPriority);
    HAL_NVIC_EnableIRQ((IRQn_Type)timeValue->TIMEx_IRQn[timer]);
    return PreNum;
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

