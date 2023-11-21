/**
*********************************************************************
*********
* @project_name :car0
* @file : TimeAuxiliaryfunction.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/20 
*********************************************************************
*********
*/
//

#ifndef CAR0_TIMEAUXILIARYFUNCTION_H
#define CAR0_TIMEAUXILIARYFUNCTION_H
#include "Resources.h"
void OpenRccTime(Timer_enum timer);
uint8_t getTIMEx_IRQn(Timer_enum timer);
uint32_t getTimeInstance(Timer_enum timer);
#endif //CAR0_TIMEAUXILIARYFUNCTION_H
