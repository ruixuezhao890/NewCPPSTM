/**
*********************************************************************
*********
* @project_name :car0
* @file : MySystic.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6 
*********************************************************************
*********
*/
//

#ifndef CAR0_MYSYSTIC_H
#define CAR0_MYSYSTIC_H

#include "virSystic.h"
#ifdef Cubemx
class MySystic: public virSystic{
public:
    void systick_init(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq) override;

    void systick_delay(uint64_t time) override;

    uint64_t systick_micors(void) override;
protected:
    uint8_t sys_stm32_clock_init(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq);

};

#endif
#endif //CAR0_MYSYSTIC_H
