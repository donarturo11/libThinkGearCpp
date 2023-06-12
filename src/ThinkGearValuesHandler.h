#ifndef THINKGEARVALUESHANDLER_H
#define THINKGEARVALUESHANDLER_H
#include "ThinkGear.h"
#include "TGData_p.h"
#include "TGEnums.h"
#include "TGVariant.h"
#include "ThinkGearEvent.h"
#include "ThinkGearEvents.h"
namespace libThinkGearCpp {
class ThinkGearEvents;
class ThinkGearValuesHandler
{
public:
    ThinkGearValuesHandler (ThinkGear *tg = 0);
    ThinkGearValuesHandler (TGRawData& data, ThinkGear *tg = 0);
	void process(TGRawData& data);
private:
    TG_AsicEegData asicEegData(TGByteVector& v);
protected:
    ThinkGearEvents* _events;
};
} // namespace libThinkGearCpp

#endif // THINKGEARHANDLEVALUES_H