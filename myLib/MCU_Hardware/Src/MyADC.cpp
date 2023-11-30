/**
*********************************************************************
*********
* @project_name :car0
* @file : MyADC.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/29 
*********************************************************************
*********
*/
//

#include "MyADC.h"
#include "MyGPIO.h"
extern void Error_Handler();
ADCManagement ADCManagementInfo;
void MyADC::ADCInit() {

}
void MyADC::ADCInit(ADC_enum adcEnum, Pin_enum *ADCPin, uint8_t ADCPinLenth) {

    if (adcEnum>MAXADC||adcEnum==ADC_enum::ADC_END)return; ADCGPIO=new MyGPIO();RankNum=0;
    for (int i = 0; i < ADCPinLenth; ++i) {
        ADCGPIO->gpio_init(ADCPin[i],GpioMode::analog,GpioPull::nopull,0) ;//初始化对应引脚
    }
    ADC_TypeDef *ADCInstance= nullptr; ADCManagementInfo.ADCx_IRQn=ADC_IRQn;
    if (adcEnum==ADC_1){
      ADCInstance=ADC1;
      __HAL_RCC_ADC1_CLK_ENABLE();
    }else if (adcEnum==ADC_2){
        ADCInstance=ADC2;  __HAL_RCC_ADC2_CLK_ENABLE();
    }else if (adcEnum==ADC_3){
        ADCInstance=ADC3;  __HAL_RCC_ADC3_CLK_ENABLE();
    }
    ADCManagementInfo.ADCList[adcEnum].Instance=ADCInstance;
    ADCManagementInfo.ADCList[adcEnum].Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    ADCManagementInfo.ADCList[adcEnum].Init.Resolution = ADC_RESOLUTION_12B;
    ADCManagementInfo.ADCList[adcEnum].Init.ScanConvMode = DISABLE;
    ADCManagementInfo.ADCList[adcEnum].Init.ContinuousConvMode = DISABLE;
    ADCManagementInfo.ADCList[adcEnum].Init.DiscontinuousConvMode = DISABLE;
    ADCManagementInfo.ADCList[adcEnum].Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    ADCManagementInfo.ADCList[adcEnum].Init.ExternalTrigConv = ADC_SOFTWARE_START;
    ADCManagementInfo.ADCList[adcEnum].Init.DataAlign = ADC_DATAALIGN_RIGHT;
    ADCManagementInfo.ADCList[adcEnum].Init.NbrOfConversion = 1;
    ADCManagementInfo.ADCList[adcEnum].Init.DMAContinuousRequests = DISABLE;
    ADCManagementInfo.ADCList[adcEnum].Init.EOCSelection = ADC_EOC_SINGLE_CONV;
}
void MyADC::ADCChannelSet(ADC_enum adcEnum, ADC_CH *ch, uint32_t rank, uint32_t stime) {
    uint8_t Rank = 0;
    if (rank)Rank = rank;
    else {
        Rank=++RankNum;
        ADCManagementInfo.ADCList[adcEnum].Init.ScanConvMode=ENABLE;
        ADCManagementInfo.ADCList[adcEnum].Init.ContinuousConvMode=ENABLE;
    }
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel =ch[adcEnum];
    sConfig.Rank = Rank;
    sConfig.SamplingTime = stime;
    if (HAL_ADC_ConfigChannel(&ADCManagementInfo.ADCList[adcEnum], &sConfig) != HAL_OK) {
        while (1);
//        Error_Handler();

    }
    ADCManagementInfo.ADCList[adcEnum].Init.NbrOfConversion = Rank;
    HAL_ADC_Init(&ADCManagementInfo.ADCList[adcEnum]);
    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC_IRQn);
}

uint32_t MyADC::ADCGetResult(ADC_enum adcEnum) {
    uint32_t temp_val=0;
    if (ADCManagementInfo.ADCx_IRQn){
        HAL_ADC_Start_IT(&ADCManagementInfo.ADCList[adcEnum]);
    }else{
        HAL_ADC_Start(&ADCManagementInfo.ADCList[adcEnum]);
    }
    temp_val=HAL_ADC_GetValue(&ADCManagementInfo.ADCList[adcEnum]);
    return temp_val;
}

uint32_t MyADC::ADCGetResultAverage(ADC_enum adcEnum, uint8_t times) {
    uint32_t temp_val = 0;
    uint8_t t;
    if (ADCManagementInfo.ADCx_IRQn){
        HAL_ADC_Start_IT(&ADCManagementInfo.ADCList[adcEnum]);
    }else{
        HAL_ADC_Start(&ADCManagementInfo.ADCList[adcEnum]);
    }
    HAL_ADC_GetValue(&ADCManagementInfo.ADCList[adcEnum]);
    for (t = 0; t < times; t++)     /* 获取times次数据 */
    {
        temp_val +=  HAL_ADC_GetValue(&ADCManagementInfo.ADCList[adcEnum]);
        HAL_Delay(5);
    }
    return temp_val / times;        /* 返回平均值 */
}
uint32_t MyADC::ADCContinuousGetResult(ADC_enum adcEnum) {

    return ADCGetResult(adcEnum);
}

void MyADC::ADCContinuousGetResultAverage(ADC_enum adcEnum, uint8_t *GetNum, uint8_t GetNumLenth, uint8_t times) {
    for (uint8_t i=0;i<GetNumLenth;i++){
        GetNum[i]=ADCGetResultAverage(adcEnum,times);
    }
}

void MyADC::ADCDMAInit(ADC_enum adcEnum, uint32_t mar) {
//    ADCDMA.DMAInitIN()
}

void MyADC::ADCDMAEnable(ADC_enum adcEnum, uint16_t ndtr) {

}

void MyADC::ADCNCHDMAInit(ADC_enum adcEnum, uint32_t tmr) {

}

void MyADC::ADCNCHDMAGPIOInit(ADC_enum adcEnum) {

}

void MyADC::ADCNCHDMAEnable(ADC_enum adcEnum, uint16_t ndtr) {

}

MyADC::~MyADC() {
    delete ADCGPIO;
}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
    if (hadc->Instance==ADC1){
        if (adcExitValue.TimeExit[0])
        adcExitValue.TimeExit[0](adcExitValue.arg[0]);
    } if (hadc->Instance==ADC2){
        if (adcExitValue.TimeExit[1])
            adcExitValue.TimeExit[1](adcExitValue.arg[1]);
    } if (hadc->Instance==ADC3){
        if (adcExitValue.TimeExit[2])
            adcExitValue.TimeExit[2](adcExitValue.arg[2]);
    }
}




