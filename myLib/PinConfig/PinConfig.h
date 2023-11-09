/**
*********************************************************************
*********
* @project_name :car0
* @file : PinConfig.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/9 
*********************************************************************
*********
*/
//

#ifndef CAR0_PINCONFIG_H
#define CAR0_PINCONFIG_H
typedef enum
{
#ifdef HAVE_SERIAL1
    UART1_TX = A9,
    UART1_RX = A10,
#endif
#ifdef HAVE_SERIAL2
    UART2_TX = A2,
    UART2_RX = A3,
#endif
#ifdef HAVE_SERIAL3
    UART3_TX = B10,
    UART3_RX = B11,
#endif
#ifdef HAVE_SERIAL4
    UART4_TX = C10,
    UART4_RX = C11,
#endif
#ifdef HAVE_SERIAL5
    UART5_TX = C12,
    UART5_RX = D2,
#endif
#ifdef HAVE_SERIAL6
    UART6_TX = C12,
    UART6_RX = D2,
#endif
    UARTn_Pin_End //占位，没用
} UART_pin;
#endif //CAR0_PINCONFIG_H
