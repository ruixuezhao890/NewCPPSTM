/**
*********************************************************************
*********
* @project_name :car0
* @file : virSystic.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6 
*********************************************************************
*********
*/
//

#ifndef CAR0_VIRSYSTIC_H
#define CAR0_VIRSYSTIC_H
#include "Resources.h"
#ifdef Cubemx
#define delay_ms(n) systick_delay(n * 1000) /*!<延时n毫秒(ms)*/
#define delay_us(n) systick_delay(n)        /*!<延时n微秒(us)*/
#define millis() (systick_micors() / 1000)  /*!<获取系统运行到到调用时的毫秒(ms)数*/
#define micors() systick_micors()           /*!<获取系统运行到到调用时的微秒(us)数*/
class virSystic {
public:
    virtual void systick_init(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq)=0;
    virtual void systick_delay(uint64_t time)=0;
    virtual uint64_t systick_micors(void)=0;
};

#endif
#endif //CAR0_VIRSYSTIC_H
