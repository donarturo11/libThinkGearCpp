#ifndef THINKGEARSIGNALER_H
#define THINKGEARSIGNALER_H
#include "TGData.h"
#include "TGEegData.h"
#include "TGEnums.h"
#include "ThinkGearEvents.h"
#include "ThinkGearValueHandler.h"
namespace libThinkGearCpp {

class ThinkGear;
class ThinkGearEvents;
class ThinkGearValueHandler;

class ThinkGearSignaler : public ThinkGearValueHandler
{
public:
    ThinkGearSignaler(ThinkGearEvents *ev = 0);
    void pushData(TGData d);
private:
    eegData asicEegData(std::vector<uint32_t> v);
protected:
    ThinkGearEvents* _events;
};
} // namespace libThinkGearCpp

#endif // THINKGEARSIGNALER_H
