/**
*********************************************************************
*********
* @project_name :car0
* @file : Factory.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6 
*********************************************************************
*********
*/
//

#ifndef CAR0_FACTORY_H
#define CAR0_FACTORY_H
#include "MyGPIO.h"
#include "MyAFIO.h"
#include "MySystic.h"
class Factory {
public:
   MyGPIO * greatMyGPIO();
   MyAFIO * greatMyAFIO();

#if !Cubemx
   MySystic* greatMySystic();
#endif
};


#endif //CAR0_FACTORY_H
