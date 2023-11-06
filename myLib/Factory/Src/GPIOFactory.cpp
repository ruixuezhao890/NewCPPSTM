/**
*********************************************************************
*********
* @project_name :car0
* @file : GPIOFactory.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6 
*********************************************************************
*********
*/
//

#include "GPIOFactory.h"
MyGPIO *GPIOFactory::greatMyGPIO(){
    return  new MyGPIO();
}