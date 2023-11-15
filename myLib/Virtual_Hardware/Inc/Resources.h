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
#define DEFAULT_GPIO_SPEED GpioSpeed::freq_medium //GPIO初始化默认GPIO速度 可以在Resources中找到
using AlternateIO=uint8_t;
void openCorrespondRCC(GPIO_TypeDef *GPIOx);
//enum class GpioGroup {
//    GroupA,GroupB,GroupC,GroupD,GroupE,GroupF,GroupG,GroupH,GroupI,GroupJ,GroupK,GroupNULL
//};
//enum class AFIO_mode
//{
//    input_af  = 0x0,
//    out_pp_af = GPIO_MODE_AF_PP,
//    out_od_af = GPIO_MODE_AF_OD
//} ;
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
typedef struct
{
    volatile uint8_t buf[256];      //接收缓冲区
    volatile uint8_t write_index;   //写指针
    volatile uint8_t read_index;    //读指针
    volatile uint16_t data_size;    //缓冲区接收到的数据长度
    /* data */
}__rec_buf;
#define HAVE_SERIAL1
#define HAVE_SERIAL2
#define HAVE_SERIAL3
#define HAVE_SERIAL4
#define HAVE_SERIAL5
#define HAVE_SERIAL6
#define HAVE_TIMER1
#define HAVE_TIMER2
#define HAVE_TIMER3
#define HAVE_TIMER4
#define HAVE_TIMER5
#define HAVE_TIMER6
#define HAVE_TIMER7
#define HAVE_TIMER8
#define HAVE_TIMER9
#define HAVE_TIMER10
#define HAVE_TIMER11
#define HAVE_TIMER12
#define HAVE_TIMER13
#define HAVE_TIMER14
#define HAVE_I2C1
#define HAVE_I2C2
#define HAVE_SPI1
#define HAVE_SPI2
#define HAVE_SPI3

typedef enum
{
#ifdef HAVE_SERIAL1
    UART_1,
#endif
#ifdef HAVE_SERIAL2
    UART_2 ,
#endif
#ifdef HAVE_SERIAL3
    UART_3 ,
#endif
#ifdef HAVE_SERIAL4
    UART_4 ,
#endif
#ifdef HAVE_SERIAL5
    UART_5 ,
#endif
#ifdef HAVE_SERIAL6
    UART_6 ,
#endif
    UART_END // 占位符，未使用
} UART_enum;
typedef enum
{
#ifdef HAVE_TIMER1
    TIMER_1,
#endif
#ifdef HAVE_TIMER2
    TIMER_2,
#endif
#ifdef HAVE_TIMER3
    TIMER_3,
#endif
#ifdef HAVE_TIMER4
    TIMER_4,
#endif
#ifdef HAVE_TIMER5
    TIMER_5,
#endif
#ifdef HAVE_TIMER6
    TIMER_6,
#endif
#ifdef HAVE_TIMER7
    TIMER_7,
#endif
#ifdef HAVE_TIMER8
    TIMER_8,
#endif
#ifdef HAVE_TIMER9
    TIMER_9,
#endif
#ifdef HAVE_TIMER10
    TIMER_10,
#endif
#ifdef HAVE_TIMER11
    TIMER_11,
#endif
#ifdef HAVE_TIMER12
    TIMER_12,
#endif
#ifdef HAVE_TIMER13
    TIMER_13,
#endif
#ifdef HAVE_TIMER14
    TIMER_14,
#endif
    TIMER_END // 占位符，未使用
} Timer_enum;
#ifdef HAVE_SERIAL1
extern __rec_buf UART1_recbuf;
#endif
#ifdef HAVE_SERIAL2
extern __rec_buf UART2_recbuf;
#endif
#ifdef HAVE_SERIAL3
extern __rec_buf UART3_recbuf;
#endif
#ifdef HAVE_SERIAL4
extern __rec_buf UART4_recbuf;
#endif
#ifdef HAVE_SERIAL5
extern __rec_buf UART5_recbuf;
#endif
#ifdef HAVE_SERIAL6
extern __rec_buf UART6_recbuf;
#endif
enum class GenericMode{
    TIME_PWM,
    TIME_Capture,
    TIME_PulseCounting
};
enum class AdvancedMode{
    TIME_SpecifyPWM,
    TIME_Compare,
    TIME_DeadZoneControl,
    TIME_InputMode
};

#endif //CAR0_RESOURCES_H
