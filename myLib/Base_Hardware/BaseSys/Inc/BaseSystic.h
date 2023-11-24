/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseSystic.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6 
*********************************************************************
*********
*/
//

#ifndef CAR0_BASESYSTIC_H
#define CAR0_BASESYSTIC_H
#ifdef Cubemx
#include "Factory.h"
class BaseSystic{
private:
    virSystic*  vir_systic;
    Factory factory;
    //void systick_init(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq);
public:
    BaseSystic(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq);
    void systick_delay(uint64_t time);
    uint64_t systick_micors(void);
};
#endif

#endif //CAR0_BASESYSTIC_H
