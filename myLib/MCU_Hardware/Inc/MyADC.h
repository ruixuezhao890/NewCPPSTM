/**
*********************************************************************
*********
* @project_name :car0
* @file : MyADC.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/29 
*********************************************************************
*********
*/
//

#ifndef CAR0_MYADC_H
#define CAR0_MYADC_H
#include "virADC.h"
#include "MyDMA.h"
class MyADC: public virADC{
protected:
    void ADCInit() override;

    void ADCInit(ADC_enum adcEnum, Pin_enum *ADCPin, uint8_t ADCPinLenth) override;

    void ADCChannelSet(ADC_enum adcEnum, ADC_CH *ch, uint32_t rank, uint32_t stime) override;

    uint32_t ADCContinuousGetResult(ADC_enum adcEnum) override;

    void ADCContinuousGetResultAverage(ADC_enum adcEnum, uint8_t *GetNum, uint8_t GetNumLenth, uint8_t times) override;

    uint32_t ADCGetResult(ADC_enum adcEnum) override;

    uint32_t ADCGetResultAverage(ADC_enum adcEnum, uint8_t times) override;

    ~MyADC() ;

    void ADCDMAInit(ADC_enum adcEnum, uint32_t mar) override;

    void ADCDMAEnable(ADC_enum adcEnum, uint16_t ndtr) override;

    void ADCNCHDMAInit(ADC_enum adcEnum, uint32_t tmr) override;

    void ADCNCHDMAGPIOInit(ADC_enum adcEnum) override;

    void ADCNCHDMAEnable(ADC_enum adcEnum, uint16_t ndtr) override;

private:
    MyDMA ADCDMA;
    uint8_t RankNum;
};


#endif //CAR0_MYADC_H
