/**
*********************************************************************
*********
* @project_name :car0
* @file : ADCResources.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/27 
*********************************************************************
*********
*/
//

#ifndef CAR0_ADCRESOURCES_H
#define CAR0_ADCRESOURCES_H
#include "Resources.h"
#define MAXADC 3
#define HAVE_ADC1
#define HAVE_ADC2
#define HAVE_ADC3
//#define HAVE_ADC4
//#define HAVE_ADC5
//#define HAVE_ADC6
struct ADCExitValue{
    callback_with_arg_t TimeExit[MAXADC];
    void* arg[MAXADC];
};
struct ADCManagement{
    ADC_HandleTypeDef ADCList[MAXADC];
    uint8_t ADCx_IRQn;
    //DMA相关的数组，TODO 根据开发手册自行更改
    DMA_HandleTypeDef DmaHandleTypeDef[MAXADC];
    uint32_t DmaHandleInstance[MAXADC]{
            (uint32_t) DMA2_Stream4, (uint32_t) DMA2_Stream2,  // 收发
            (uint32_t) DMA2_Stream0,
    };

    uint32_t DMA_Channel[MAXADC]{
            DMA_CHANNEL_0, DMA_CHANNEL_1,
            DMA_CHANNEL_2,
    };
    uint32_t  DMA_IQRNNum[MAXADC]{
            DMA2_Stream4_IRQn,DMA2_Stream2_IRQn,
            DMA2_Stream0_IRQn,
    };
};

extern ADCManagement ADCManagementInfo;

typedef enum
{
#ifdef HAVE_ADC1
    ADC_1,
#endif
#ifdef HAVE_ADC2
    ADC_2,
#endif
#ifdef HAVE_ADC3
    ADC_3,
#endif
#ifdef HAVE_ADC4
    ADC_4,
#endif
#ifdef HAVE_ADC5
    ADC_5,
#endif
#ifdef HAVE_ADC6
    ADC_6,
#endif
    ADC_END // 占位符，未使用
} ADC_enum;
typedef enum
{
    ADC_CH0 = ADC_CHANNEL_0,
    ADC_CH1 = ADC_CHANNEL_1,
    ADC_CH2 = ADC_CHANNEL_2,
    ADC_CH3 = ADC_CHANNEL_3,
    ADC_CH4 = ADC_CHANNEL_4,
    ADC_CH5 = ADC_CHANNEL_5,
    ADC_CH6 = ADC_CHANNEL_6,
    ADC_CH7 = ADC_CHANNEL_7,
    ADC_CH8 = ADC_CHANNEL_8,
    ADC_CH9 = ADC_CHANNEL_9,
    ADC_CH10 = ADC_CHANNEL_10,
    ADC_CH11 = ADC_CHANNEL_11,
    ADC_CH12 = ADC_CHANNEL_12,
    ADC_CH13 = ADC_CHANNEL_13,
    ADC_CH14 = ADC_CHANNEL_14,
    ADC_CH15 = ADC_CHANNEL_15,
    ADC_DEFAULT = 0xff
} ADC_CH;
extern ADCExitValue adcExitValue;
#endif //CAR0_ADCRESOURCES_H
