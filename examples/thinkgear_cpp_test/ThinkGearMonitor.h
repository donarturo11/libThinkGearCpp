#ifndef THINKGEARMONITOR_H
#define THINKGEARMONITOR_H
#include "thinkgearcpp/ThinkGear.h"
#include "ThinkGearMessages.h"
//struct TG_AsicEegData;

class ThinkGearMonitor : public libThinkGearCpp::ThinkGearAbstractListener
{
public:
    ThinkGearMonitor();
    ~ThinkGearMonitor();
    void onThinkGearRaw(short val);
    void onThinkGearBattery(unsigned char val);
    void onThinkGearPoorSignal(unsigned char val);
    void onThinkGearAttention(unsigned char val);
    void onThinkGearMeditation(unsigned char val);
    void onThinkGearEeg(TG_AsicEegData val);
    void onThinkGearConnecting(unsigned char val);
    void onThinkGearReady(unsigned char val);
    void onThinkGearError(unsigned char val);
    void onThinkGearBlinkStrength(unsigned char val) {}
    void countMax(TG_AsicEegData val);
private:
    ThinkGearMessages msg;
    int max;
};

#endif // THINKGEARMONITOR_H
