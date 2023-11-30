/**
*********************************************************************
*********
* @project_name :car0
* @file : MyDMA.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/27 
*********************************************************************
*********
*/
//

#ifndef CAR0_MYDMA_H
#define CAR0_MYDMA_H
#include "stm32f4xx.h"
#include "gpio.h"
#include "UsartResources.h"
#include "ADCResources.h"
#include <type_traits>
class MyDMA{
public:
    void DMAInitUsartIN(UART_enum select,uartInfoMation *config);
    void DMAInitUsartOUT(UART_enum select,uartInfoMation *config);

    void DMAInitADCIN(ADC_enum select,ADCManagement *config);
//    void DMAInitDACOUT(UART_enum select,uartInfoMation *config);
protected:
    template<class T>
    void DMAInitIN(uint8_t select,T *config);


};
extern "C" {
void DMA2_Stream2_IRQHandler(void);
void DMA2_Stream7_IRQHandler(void);
void DMA1_Stream6_IRQHandler(void);
void DMA1_Stream5_IRQHandler(void);
void DMA1_Stream4_IRQHandler(void);
void DMA1_Stream3_IRQHandler(void);
void DMA1_Stream2_IRQHandler(void);
void DMA1_Stream1_IRQHandler(void);
void DMA1_Stream0_IRQHandler(void);
void DMA1_Stream7_IRQHandler(void);
void DMA2_Stream6_IRQHandler(void);
void DMA2_Stream1_IRQHandler(void);
void DMA2_Stream0_IRQHandler(void);
void DMA2_Stream4_IRQHandler(void);
void ADC_IRQHandler(void);
}

#endif //CAR0_MYDMA_H
