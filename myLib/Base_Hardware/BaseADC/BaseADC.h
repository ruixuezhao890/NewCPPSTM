/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseADC.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/29 
*********************************************************************
*********
*/
//

#ifndef CAR0_BASEADC_H
#define CAR0_BASEADC_H
#include "MyADC.h"
class BaseADC :public MyADC{
private:
    ADC_enum x_ADCEnum;
public:
    BaseADC();
    BaseADC(ADC_enum adcEnum);
    template<typename TArg>
    void attach(void (*callback)(TArg), TArg arg);
    uint8_t begin(Pin_enum *ADCPin, uint8_t ADCPinLenth=1);
    uint8_t beginDMA(Pin_enum *ADCPin, uint8_t ADCPinLenth=1);
    uint8_t BaseADCChannelSet(ADC_CH *ch, uint32_t rank=1, uint32_t stime=ADC_SAMPLETIME_3CYCLES);
    uint32_t BaseADCGetValue();
    uint32_t BaseADCGetValueContinuous();
    void BaseADCDMAGetValue(uint32_t* pData, uint32_t Length);


};


#endif //CAR0_BASEADC_H
