/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseSystic.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6 
*********************************************************************
*********
*/
//

#ifdef Cubemx
#include "BaseSystic.h"
BaseSystic::BaseSystic(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq) {
    vir_systic=factory.greatMySystic();
    vir_systic->systick_init(plln, pllm, pllp, pllq);
}

void BaseSystic::systick_delay(uint64_t time) {
    vir_systic->systick_delay(time);
}

uint64_t BaseSystic::systick_micors(void) {
   return vir_systic->systick_micors();
}
#endif