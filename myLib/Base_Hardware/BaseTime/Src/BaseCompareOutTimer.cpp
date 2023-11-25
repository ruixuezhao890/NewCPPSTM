/**
*********************************************************************
*********
* @project_name :car0
* @file : BaseCompareOutTimer.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/24 
*********************************************************************
*********
*/
//

#include "Base_Hardware/BaseTime/Inc/BaseCompareOutTimer.h"

BaseCompareOutTimer::BaseCompareOutTimer() {

}

BaseCompareOutTimer::BaseCompareOutTimer(Timer_enum timerEnum, uint8_t PreemptPriority, uint8_t SubPriority) {
 _timer=timerEnum;this->PreemptPriority=PreemptPriority;this->SubPriority=SubPriority;
}

BaseCompareOutTimer::BaseCompareOutTimer(Timer_enum timerEnum, Pin_enum pin, uint8_t AFMode, uint8_t PreemptPriority,
                                         uint8_t SubPriority) {
    _timer=timerEnum;this->PreemptPriority=PreemptPriority;this->SubPriority=SubPriority;
    AdvancedTimer::timerOutputCompareMultiplexPin(pin,AFMode);

}

BaseCompareOutTimer::~BaseCompareOutTimer() {

}
BaseCompareOutTimer::BaseCompareOutTimer(Timer_enum timerEnum, std::vector<Pin_enum> pin, uint8_t AFMode,
                                         uint8_t PreemptPriority, uint8_t SubPriority) {
    _timer=timerEnum;this->PreemptPriority=PreemptPriority;this->SubPriority=SubPriority;
    for (auto i:pin){
        AdvancedTimer::timerOutputCompareMultiplexPin(i,AFMode);
    }


}

void BaseCompareOutTimer::stopCompareOut() {
    for (int i = 0; i < m_TIMExCompareOut_Channel.size(); ++i) {
        AdvancedTimer::stopOutputCompare(_timer,(m_TIMExCompareOut_Channel[i]));
    }

}

void BaseCompareOutTimer::deletCompareOut() {
    AdvancedTimer::deleteOutputCompare(_timer);
}


void BaseCompareOutTimer::ConfigCompareOut() {
    AdvancedTimer::setOutputCompareGreat(_timer, m_psc, m_arr,PreemptPriority,SubPriority);
}

void BaseCompareOutTimer::startCompareOut(uint32_t arr, uint32_t psc, std::vector<uint16_t> &PulseNum,
                                          std::vector<uint8_t> &TIMExCapture_Channel) {
    m_arr=arr;m_psc=psc;m_TIMExCompareOut_Channel=TIMExCapture_Channel;
    ConfigCompareOut();
    for(size_t i=0;i<TIMExCapture_Channel.size();i++){
        AdvancedTimer::startOutputCompare(_timer,PulseNum[i],TIMExCapture_Channel[i]);
    }
}


