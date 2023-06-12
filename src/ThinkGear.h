#ifndef THINKGEAR_H
#define THINKGEAR_H

#if defined _WIN32 || defined __CYGWIN__
  #if defined(EXPORT)
    #define TGDLL __declspec(dllexport)
  #else
    #define TGDLL
  #endif
#else
  #if __GNUC__ >= 4
    #define TGDLL __attribute__( (visibility( "default" )) )
  #else
    #define TGDLL
  #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif
typedef struct _TG_AsicEegData {
    unsigned int eegDelta; // 100000 / 1500000 . 0.5-2.75hz
    unsigned int eegTheta; // 300000 / 600000 . 3.5-6.75hz
    unsigned int eegLowAlpha; // 2500 / 75000 . 7.5-9.25hz
    unsigned int eegHighAlpha; // 2500 / 150000 . 10-11.75hz
    unsigned int eegLowBeta; // 1500 / 60000 . 13-16.75hz
    unsigned int eegHighBeta; // 2500 / 60000 . 18-29.75hz
    unsigned int eegLowGamma; // 5000 / 300000 . 31-39.75hz
    unsigned int eegMidGamma; // 5000 / 300000 . 41-49.75hz
} TG_AsicEegData;

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <memory>

namespace libThinkGearCpp {
class ThinkGearAbstractListener;
class ThinkGearEvents;
class ThinkGear_p;
class TGDLL ThinkGear
{
public:
    ThinkGear();
    ~ThinkGear();
    void load(char* buffer, int size);
    void load(char c);
    void addListener(ThinkGearAbstractListener *listener);
    void removeListener(ThinkGearAbstractListener *listener);
    ThinkGearEvents* events();
    bool parsing() const;
private:
    std::unique_ptr<ThinkGear_p> _tg_p;
};


class ThinkGearAbstractListener
{
public:
    virtual void onThinkGearRaw(short val) = 0;
    virtual void onThinkGearBattery(unsigned char val) = 0;
    virtual void onThinkGearPoorSignal(unsigned char val) = 0;
    virtual void onThinkGearBlinkStrength(unsigned char val) = 0;
    virtual void onThinkGearAttention(unsigned char val) = 0;
    virtual void onThinkGearMeditation(unsigned char val) = 0;
    virtual void onThinkGearEeg(TG_AsicEegData val) = 0;
    virtual void onThinkGearConnecting(unsigned char val) = 0;
    virtual void onThinkGearReady(unsigned char val) = 0;
    virtual void onThinkGearError(unsigned char val) = 0;
};

typedef std::shared_ptr<ThinkGear> ThinkGearPtr;

} // namespace libThinkGearCpp

#else
#include "thinkgear_c.h"
#endif // __cplusplus

#endif // THINKGEAR_H
