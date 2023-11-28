/**
*********************************************************************
*********
* @project_name :car0
* @file : DMAResources.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/27 
*********************************************************************
*********
*/
//
#include "DMAResources.h"
uint32_t DmaHandle[12]{
        (uint32_t) DMA2_Stream2, (uint32_t) DMA2_Stream7,  // 收发
        (uint32_t) DMA1_Stream5, (uint32_t) DMA1_Stream6,
        (uint32_t) DMA1_Stream1, (uint32_t) DMA1_Stream3,
        (uint32_t) DMA1_Stream2, (uint32_t) DMA1_Stream4,
        (uint32_t) DMA1_Stream0, (uint32_t) DMA1_Stream7,
        (uint32_t) DMA2_Stream1, (uint32_t) DMA2_Stream6,
};

uint32_t DMA_Channel[12]{
        DMA_CHANNEL_4, DMA_CHANNEL_4,
        DMA_CHANNEL_4, DMA_CHANNEL_4,
        DMA_CHANNEL_4, DMA_CHANNEL_4,
        DMA_CHANNEL_4, DMA_CHANNEL_4,
        DMA_CHANNEL_4, DMA_CHANNEL_4,
        DMA_CHANNEL_5, DMA_CHANNEL_5,
};
uint32_t  DMA_IQRNNum[]{
        DMA2_Stream2_IRQn,DMA2_Stream7_IRQn,
        DMA1_Stream5_IRQn,DMA1_Stream6_IRQn,
        DMA1_Stream1_IRQn,DMA1_Stream3_IRQn,
        DMA1_Stream2_IRQn,DMA1_Stream4_IRQn,
        DMA1_Stream0_IRQn,DMA1_Stream7_IRQn,
        DMA2_Stream1_IRQn,DMA2_Stream6_IRQn,
};


