#ifndef THINKGEAREVENTS_H
#define THINKGEAREVENTS_H
#include "ThinkGearEvent.h"
#include "TGAsicEegData.h"
#include "TGData_p.h"
#include "TGEnums.h"
#include <memory>

namespace libThinkGearCpp {
class ThinkGearEvents;
typedef std::shared_ptr<ThinkGearEvents> ThinkGearEventsPtr;
class ThinkGearEvents
{
public:
    ThinkGearEvents(){}
    
    template<class ListenerClass>
    void connectListener(ListenerClass *listener) {
        TGEventConnect(&onRaw, listener, &ListenerClass::onThinkGearRaw);
        TGEventConnect(&onPoorSignal, listener, &ListenerClass::onThinkGearPoorSignal);
        TGEventConnect(&onBlinkStrength, listener, &ListenerClass::onThinkGearBlinkStrength);
        TGEventConnect(&onAttention, listener, &ListenerClass::onThinkGearAttention);
        TGEventConnect(&onMeditation, listener, &ListenerClass::onThinkGearMeditation);
        TGEventConnect(&onEeg, listener, &ListenerClass::onThinkGearEeg);
        TGEventConnect(&onConnecting, listener, &ListenerClass::onThinkGearConnecting);
        TGEventConnect(&onReady, listener, &ListenerClass::onThinkGearReady);
        TGEventConnect(&onError, listener, &ListenerClass::onThinkGearError);
    }
    
    template<class ListenerClass>
    void disconnectListener(ListenerClass *listener) {
        TGEventDisconnect(&onRaw, listener, &ListenerClass::onThinkGearRaw);
        TGEventDisconnect(&onPoorSignal, listener, &ListenerClass::onThinkGearPoorSignal);
        TGEventDisconnect(&onBlinkStrength, listener, &ListenerClass::onThinkGearBlinkStrength);
        TGEventDisconnect(&onAttention, listener, &ListenerClass::onThinkGearAttention);
        TGEventDisconnect(&onMeditation, listener, &ListenerClass::onThinkGearMeditation);
        TGEventDisconnect(&onEeg, listener, &ListenerClass::onThinkGearEeg);
        TGEventDisconnect(&onConnecting, listener, &ListenerClass::onThinkGearConnecting);
        TGEventDisconnect(&onReady, listener, &ListenerClass::onThinkGearReady);
        TGEventDisconnect(&onError, listener, &ListenerClass::onThinkGearError);
    }
    
    TGEvent<short> onRaw;
    TGEvent<unsigned char> onBattery;
    TGEvent<unsigned char> onPoorSignal;
    TGEvent<unsigned char> onBlinkStrength;
    TGEvent<unsigned char> onAttention;
    TGEvent<unsigned char> onMeditation;
    TGEvent<TG_AsicEegData> onEeg;
    TGEvent<unsigned char> onConnecting;
    TGEvent<unsigned char> onReady;
    TGEvent<unsigned char> onError;
    
};

} // namespace libThinkGearCpp

#endif // THINKGEAREVENTS_H
