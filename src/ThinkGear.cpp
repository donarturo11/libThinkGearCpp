#include <memory>
#include "ThinkGear.h"
#include "ThinkGear_p.h"
#include "ThinkGearEvents.h"

namespace libThinkGearCpp {
#ifdef __cplusplus
extern "C"
#endif
unsigned int tg_eegint_sum(tg_eegint_t* data)
{
    int sum=0;
    for(unsigned int *it=&(data->eegDelta); it!= &(data->eegMidGamma)+1; it++) {
        sum += *it;
    }
    return sum;
}


ThinkGear::ThinkGear() : 
_tg_p {std::make_unique<ThinkGear_p>(this)}
{}

ThinkGear::~ThinkGear()
{}

void ThinkGear::load(char* buffer, int size)
{
    for (int i=0; i<size; i++) {
		_tg_p->load(buffer[i]);
	}
}

void ThinkGear::load(char c)
{
	_tg_p->load(c);
}

void ThinkGear::addListener(ThinkGearAbstractListener *listener)
{
    _tg_p->events.connectListener(listener);    
}

void ThinkGear::removeListener(ThinkGearAbstractListener *listener)
{
    _tg_p->events.disconnectListener(listener);
}

ThinkGearEvents* ThinkGear::events()
{
    return &(_tg_p->events);
}

bool ThinkGear::parsing() const
{
    return _tg_p->parsing;
}

} // namespace libThinkGearCpp
