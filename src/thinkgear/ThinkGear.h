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

#include "TGEegData.h"

#ifdef __cplusplus
#include <memory>

namespace libThinkGearCpp {
class ThinkGearAbstractListener;
class ThinkGearEvents;
class ThinkGearStreamParser;
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
    ThinkGear_p* _tg_p;
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
    virtual void onThinkGearEeg(eegData val) = 0;
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
