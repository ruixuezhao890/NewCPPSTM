/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseADC.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/29 
*********************************************************************
*********
*/
//

#include "BaseADC.h"

BaseADC::BaseADC() {

}

BaseADC::BaseADC(ADC_enum adcEnum) {
    x_ADCEnum=adcEnum;
}

uint8_t BaseADC::begin(Pin_enum *ADCPin, uint8_t ADCPinLenth) {
    ADCInit(x_ADCEnum,ADCPin,ADCPinLenth);
    return 1;
}

uint32_t BaseADC::BaseADCGetValue() {
    return MyADC::ADCGetResult(x_ADCEnum);
}

uint32_t BaseADC::BaseADCGetValueContinuous() {
    return MyADC::ADCContinuousGetResult(x_ADCEnum);
}

uint8_t BaseADC::BaseADCChannelSet(ADC_CH *ch, uint32_t rank, uint32_t stime) {
    ADCChannelSet(x_ADCEnum,ch,rank,stime);
    return 1;
}

uint8_t BaseADC::beginDMA(Pin_enum *ADCPin, uint8_t ADCPinLenth) {
    MyADC::ADCDMAInit(x_ADCEnum);
    ADCInit(x_ADCEnum,ADCPin,ADCPinLenth);
    ADCManagementInfo.ADCList[x_ADCEnum].Init.ContinuousConvMode = ENABLE;
    ADCManagementInfo.ADCList[x_ADCEnum].Init.DMAContinuousRequests = ENABLE;
    return 1;
}

void BaseADC::BaseADCDMAGetValue(uint32_t *pData, uint32_t Length) {
    ADCDMAStart(x_ADCEnum,pData,Length);
}

template<typename TArg>
void BaseADC::attach(void (*callback)(TArg), TArg arg) {
   adcExitValue.arg[x_ADCEnum]=reinterpret_cast<void*>(arg);
   adcExitValue.TimeExit[x_ADCEnum]=callback;
}
