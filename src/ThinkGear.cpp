#include <memory>
#include "ThinkGear.h"
#include "ThinkGear_p.h"
#include "ThinkGearEvents.h"

namespace libThinkGearCpp {
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

template <class ListenerClass>
void ThinkGear::addListener(ListenerClass *listener)
{
    _tg_p->events.connectListener(listener);    
}

template <class ListenerClass>
void ThinkGear::removeListener(ListenerClass *listener)
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
