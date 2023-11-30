/**
*********************************************************************
*********
* @project_name :car0
* @file : MyDMA.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/29 
*********************************************************************
*********
*/
//
#include "MyDMA.h"
#include "MyUsart.h"
void DMA2_Stream1_IRQHandler(void) {

    HAL_DMA_IRQHandler(&uartInfo.DmaHandleTypeDef[UART_6]);


}
void DMA2_Stream6_IRQHandler(void)
{

    HAL_DMA_IRQHandler(&uartInfo.DmaHandleTypeDef[UART_6 + 1]);

}
void DMA1_Stream0_IRQHandler(void)
{

    HAL_DMA_IRQHandler(&uartInfo.DmaHandleTypeDef[UART_5 ]);

}
void DMA1_Stream7_IRQHandler(void)
{
    /* USER CODE BEGIN DMA1_Stream7_IRQn 0 */

    /* USER CODE END DMA1_Stream7_IRQn 0 */
    HAL_DMA_IRQHandler(&uartInfo.DmaHandleTypeDef[UART_5 + 1]);

}

void DMA1_Stream1_IRQHandler(void)
{

    HAL_DMA_IRQHandler(&uartInfo.DmaHandleTypeDef[UART_3 ]);

}


void DMA1_Stream2_IRQHandler(void)
{

    HAL_DMA_IRQHandler(&uartInfo.DmaHandleTypeDef[UART_4 ]);

}

void DMA1_Stream3_IRQHandler(void)
{

    HAL_DMA_IRQHandler(&uartInfo.DmaHandleTypeDef[UART_3 + 1]);

}


void DMA1_Stream4_IRQHandler(void)
{

    HAL_DMA_IRQHandler(&uartInfo.DmaHandleTypeDef[UART_4 + 1]);

}


void DMA1_Stream5_IRQHandler(void)
{

    HAL_DMA_IRQHandler(&uartInfo.DmaHandleTypeDef[UART_2 ]);

}


void DMA1_Stream6_IRQHandler(void)
{

    HAL_DMA_IRQHandler(&uartInfo.DmaHandleTypeDef[UART_2 + 1]);

}
void DMA2_Stream2_IRQHandler(void){
    {
        HAL_DMA_IRQHandler(&uartInfo.DmaHandleTypeDef[UART_1]);
        HAL_DMA_IRQHandler(&ADCManagementInfo.DmaHandleTypeDef[ADC_2]);
    }
}
void DMA2_Stream7_IRQHandler(void){
    {
        HAL_DMA_IRQHandler(&uartInfo.DmaHandleTypeDef[UART_1 + 1]);
    }
}
void DMA2_Stream4_IRQHandler(void)
{

    HAL_DMA_IRQHandler(&ADCManagementInfo.DmaHandleTypeDef[ADC_1]);

}
void DMA2_Stream0_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&ADCManagementInfo.DmaHandleTypeDef[ADC_3]);

}
void MyDMA::DMAInitUsartIN(UART_enum select, uartInfoMation *config) {
    DMAInitIN(select,config);
    __HAL_LINKDMA(&config->UsartList[select], hdmarx,  config->DmaHandleTypeDef[select]);

}

void MyDMA::DMAInitUsartOUT(UART_enum select, uartInfoMation *config) {
    DMAInitIN(select+1,config);
    __HAL_LINKDMA(&config->UsartList[select+1], hdmatx,  config->DmaHandleTypeDef[select+1]);
}

void MyDMA::DMAInitADCIN(ADC_enum select, ADCManagement *config) {
    DMAInitIN(select,config);
    __HAL_LINKDMA(&config->ADCList[select],DMA_Handle,config->DmaHandleTypeDef[select]);
}

template<class T>
void MyDMA::DMAInitIN(uint8_t select,T *config) {
    __HAL_RCC_DMA2_CLK_ENABLE();                        /* DMA2时钟使能 */
    __HAL_RCC_DMA1_CLK_ENABLE();                        /* DMA1时钟使能 */
      config->DmaHandleTypeDef[select].Instance = (DMA_Stream_TypeDef*)config->DmaHandleInstance[select];
      config->DmaHandleTypeDef[select].Init.Channel = config->DMA_Channel[select];
      config->DmaHandleTypeDef[select].Init.Direction = DMA_PERIPH_TO_MEMORY;
      config->DmaHandleTypeDef[select].Init.PeriphInc = DMA_PINC_DISABLE;
      config->DmaHandleTypeDef[select].Init.MemInc = DMA_MINC_ENABLE;
      config->DmaHandleTypeDef[select].Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
      config->DmaHandleTypeDef[select].Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
      config->DmaHandleTypeDef[select].Init.Mode = DMA_NORMAL;
      config->DmaHandleTypeDef[select].Init.Priority = DMA_PRIORITY_LOW;
      config->DmaHandleTypeDef[select].Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&config->DmaHandleTypeDef[select]) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_NVIC_SetPriority((IRQn_Type)config->DMA_IQRNNum[select], 0, 0);
    HAL_NVIC_EnableIRQ((IRQn_Type)config->DMA_IQRNNum[select]);
}
