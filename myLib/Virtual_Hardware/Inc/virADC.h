/**
*********************************************************************
*********
* @project_name :car0
* @file : virADC.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/27 
*********************************************************************
*********
*/
//

#ifndef CAR0_VIRADC_H
#define CAR0_VIRADC_H
#include "ADCResources.h"
#include "virGPIO.h"
class virADC {
protected:

       virtual void ADCInit()=0;    /* ADC初始化 */
       virtual void ADCInit(ADC_enum adcEnum, Pin_enum *ADCPin, uint8_t ADCPinLenth) =0;    /* ADC初始化 */
       virtual void ADCChannelSet(ADC_enum adcEnum, ADC_CH *ch, uint32_t rank, uint32_t stime) =0;    /* ADC通道设置 */
       virtual uint32_t ADCGetResult(ADC_enum adcEnum) =0;       /* 获得某个通道值 */
       virtual uint32_t ADCGetResultAverage(ADC_enum adcEnum, uint8_t times) =0;    /* 得到某个通道给定次数采样的平均值 */
       virtual uint32_t ADCContinuousGetResult(ADC_enum adcEnum) =0;       /* 获得某个通道值 */
       virtual void
       ADCContinuousGetResultAverage(ADC_enum adcEnum, uint8_t *GetNum, uint8_t GetNumLenth, uint8_t times) =0;    /* 得到某个通道给定次数采样的平均值 */

    virtual void ADCDMAInit(ADC_enum adcEnum) = 0;            /* ADC DMA采集初始化 */

    virGPIO *ADCGPIO;
};


#endif //CAR0_VIRADC_H
