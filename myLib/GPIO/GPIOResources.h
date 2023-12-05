/**
*********************************************************************
*********
* @project_name :car0
* @file : GPIOResources.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/27 
*********************************************************************
*********
*/
//

#ifndef CAR0_GPIORESOURCES_H
#define CAR0_GPIORESOURCES_H
#include "stm32f4xx.h"
using AlternateIO=uint8_t;
using CallBack = void(*)(void);
typedef void (*callback_t)(void);
typedef void (*callback_with_arg_t)(void*);
void openCorrespondRCC(GPIO_TypeDef *GPIOx);
enum class GpioMode {
    input = 0x00000000U,
    output_pp = 0x00000001U,
    output_od = 0x00000011U,
    af_pp = 0x00000002U,
    af_od = 0x00000012U,
    analog = 0x00000003U
};
enum class GpioExit{
    it_rising = 0x00110000U,
    it_falling = 0x10210000U,
    it_rising_falling = 0x10310000U,
    evt_rising = 0x10120000U,
    evt_falling = 0x10220000U,
    evt_rising_falling = 0x10320000U
};
enum class GpioSpeed{
    freq_low = 0x00000000U,
    freq_medium = 0x00000001U,
    freq_high = 0x00000002U,
    freq_very_high = 0x00000003U
};
enum class GpioPull {
    nopull = 0x00000000U,
    pullup = 0x00000001U,
    pulldown = 0x00000002U
};
//enum class GpioGroup {
//    GroupA,GroupB,GroupC,GroupD,GroupE,GroupF,GroupG,GroupH,GroupI,GroupJ,GroupK,GroupNULL
//};
//enum class AFIO_mode
//{
//    input_af  = 0x0,
//    out_pp_af = GPIO_MODE_AF_PP,
//    out_od_af = GPIO_MODE_AF_OD
//} ;
typedef enum
{
    A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,
    B0,B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,B13,B14,B15,
    C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,
    D0,D1,D2,D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,D13,D14,D15,
    E0,E1,E2,E3,E4,E5,E6,E7,E8,E9,E10,E11,E12,E13,E14,E15,
    F0,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,F14,F15,
    G0,G1,G2,G3,G4,G5,G6,G7,G8,G9,G10,G11,G12,G13,G14,G15,
    Pin_null
}Pin_enum;
#define DEFAULT_GPIO_SPEED GpioSpeed::freq_medium //GPIO初始化默认GPIO速度 可以在Resources中找到

#endif //CAR0_GPIORESOURCES_H
