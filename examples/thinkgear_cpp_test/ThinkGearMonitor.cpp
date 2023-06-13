#include "ThinkGearMonitor.h"
#include <iostream>

ThinkGearMonitor::ThinkGearMonitor()
{

}

ThinkGearMonitor::~ThinkGearMonitor()
{
    std::cout << "Max Eeg value (dec): " << std::dec <<  max << std::endl;
    std::cout << "Max Eeg value (hex): 0x" << std::hex << max  << std::endl;
    std::cout << "Diff to max (dec): " << std::dec <<  0xFFFFFF-max << std::endl;
    std::cout << "Diff to max (hex): 0x" << std::hex << 0xFFFFFF-max  << std::endl;
    std::cout << std::dec << std::endl;
}

void ThinkGearMonitor::onThinkGearRaw(short val)
{
    msg.displayValue("Raw", val);
}

void ThinkGearMonitor::onThinkGearBattery(unsigned char val)
{
    msg.displayValue("Battery", val);
}

void ThinkGearMonitor::onThinkGearPoorSignal(unsigned char val)
{
    msg.displayValue("Poor signal", val);
}

void ThinkGearMonitor::onThinkGearAttention(unsigned char val)
{
    msg.displayValue("Attention: ", val);
}

void ThinkGearMonitor::onThinkGearMeditation(unsigned char val)
{
    msg.displayValue("On meditation",  val);
}

void ThinkGearMonitor::onThinkGearEeg(TG_AsicEegData val)
{
    msg.displayEeg(val);
    countMax(val);
}

void ThinkGearMonitor::onThinkGearConnecting(unsigned char val)
{

}

void ThinkGearMonitor::onThinkGearReady(unsigned char val)
{

}

void ThinkGearMonitor::onThinkGearError(unsigned char val)
{

}

void ThinkGearMonitor::countMax(TG_AsicEegData val)
{
    int localSum=0;
    for(unsigned int *it=&(val.eegDelta); it!= &(val.eegMidGamma)+1; it++) {
        if (*it > max) max = *it;
        localSum += *it;
    }
    for(unsigned int *it=&(val.eegDelta); it!= &(val.eegMidGamma)+1; it++) {
        std::cout << std::dec << (float)((float)*it / (float)localSum) << std::endl;
        std::cout << std::dec << ((float)*it / (float)1000) << "%" << std::endl;
    }
    std::cout << "Max Eeg value: " << max << std::endl;
}
