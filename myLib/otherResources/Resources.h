/**
*********************************************************************
*********
* @project_name :car0
* @file : Resources.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6 
*********************************************************************
*********
*/
//

#ifndef CAR0_RESOURCES_H
#define CAR0_RESOURCES_H
#include "stm32f4xx.h"
//#define Cubemx //代表使用了cubemx配置时钟没有这个宏代表使用VirSystic函数配置时钟
#define STM32 1
#define ENABLE_FERRRTOS 0
typedef void (*callback_t)(void);
typedef void (*callback_with_arg_t)(void*);
#define HAVE_I2C1
#define HAVE_I2C2
#define HAVE_SPI1
#define HAVE_SPI2
#define HAVE_SPI3




#endif //CAR0_RESOURCES_H
