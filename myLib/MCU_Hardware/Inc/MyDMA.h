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

#include "virDMA.h"
#include "stm32f4xx.h"
#include "gpio.h"
#include "DMAResources.h"
#include "UsartResources.h"
class MyDMA{
public:

    void
    DMAInitOut(UART_HandleTypeDef *controlEquipment, UART_enum select, DMA_Stream_TypeDef *dmaStreamHandle, uint32_t ch,
               uint32_t IQRN);
    void
    DMAInitIN(UART_HandleTypeDef *controlEquipment, UART_enum select, DMA_Stream_TypeDef *dmaStreamHandle, uint32_t ch,
               uint32_t IQRN);

};
extern "C" {
void DMA2_Stream2_IRQHandler(void);
void DMA2_Stream7_IRQHandler(void);
}

#endif //CAR0_MYDMA_H
