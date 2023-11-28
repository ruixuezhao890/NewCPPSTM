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
DMA_HandleTypeDef DMAHandle[12];
void DMA2_Stream2_IRQHandler(void){
    {
        /* USER CODE BEGIN DMA2_Stream7_IRQn 0 */

        /* USER CODE END DMA2_Stream7_IRQn 0 */

        HAL_DMA_IRQHandler(&DMAHandle[UART_1]);
        /* USER CODE BEGIN DMA2_Stream7_IRQn 1 */

        /* USER CODE END DMA2_Stream7_IRQn 1 */
    }
}
void DMA2_Stream7_IRQHandler(void){
    {
        /* USER CODE BEGIN DMA2_Stream7_IRQn 0 */

        /* USER CODE END DMA2_Stream7_IRQn 0 */

        HAL_DMA_IRQHandler(&DMAHandle[UART_1+1]);
        /* USER CODE BEGIN DMA2_Stream7_IRQn 1 */

        /* USER CODE END DMA2_Stream7_IRQn 1 */
    }
}

void MyDMA::DMAInitOut(UART_HandleTypeDef *controlEquipment, UART_enum select, DMA_Stream_TypeDef *dmaStreamHandle,
                       uint32_t ch, uint32_t IQRN) {

        __HAL_RCC_DMA2_CLK_ENABLE();                        /* DMA2时钟使能 */
        __HAL_RCC_DMA1_CLK_ENABLE();                        /* DMA1时钟使能 */


        DMAHandle[select+1].Instance = dmaStreamHandle;
        DMAHandle[select+1].Init.Channel = ch;
        DMAHandle[select+1].Init.Direction = DMA_MEMORY_TO_PERIPH;
        DMAHandle[select+1].Init.PeriphInc = DMA_PINC_DISABLE;
        DMAHandle[select+1].Init.MemInc = DMA_MINC_ENABLE;
        DMAHandle[select+1].Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        DMAHandle[select+1].Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        DMAHandle[select+1].Init.Mode = DMA_NORMAL;
        DMAHandle[select+1].Init.Priority = DMA_PRIORITY_LOW;
        DMAHandle[select+1].Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(& DMAHandle[select+1]) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(controlEquipment,hdmatx, DMAHandle[select+1]);
        HAL_NVIC_SetPriority((IRQn_Type)IQRN, 0, 0);
        HAL_NVIC_EnableIRQ((IRQn_Type)IQRN);

}

void MyDMA::DMAInitIN(UART_HandleTypeDef *controlEquipment, UART_enum select, DMA_Stream_TypeDef *dmaStreamHandle,
                      uint32_t ch, uint32_t IQRN) {
    __HAL_RCC_DMA2_CLK_ENABLE();                        /* DMA2时钟使能 */
    __HAL_RCC_DMA1_CLK_ENABLE();                        /* DMA1时钟使能 */
    DMAHandle[select].Instance = dmaStreamHandle;
    DMAHandle[select].Init.Channel = ch;
    DMAHandle[select].Init.Direction = DMA_PERIPH_TO_MEMORY;
    DMAHandle[select].Init.PeriphInc = DMA_PINC_DISABLE;
    DMAHandle[select].Init.MemInc = DMA_MINC_ENABLE;
    DMAHandle[select].Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    DMAHandle[select].Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    DMAHandle[select].Init.Mode = DMA_CIRCULAR;
    DMAHandle[select].Init.Priority = DMA_PRIORITY_LOW;
    DMAHandle[select].Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(& DMAHandle[select]) != HAL_OK)
    {
        Error_Handler();
    }
    __HAL_LINKDMA(controlEquipment, hdmarx,  DMAHandle[select]);   /* 将DMA与USART1联系起来(发送DMA) */
    HAL_NVIC_SetPriority((IRQn_Type)IQRN, 0, 0);
    HAL_NVIC_EnableIRQ((IRQn_Type)IQRN);
}
