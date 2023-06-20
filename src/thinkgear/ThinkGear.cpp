#include <memory>
#include "ThinkGear.h"
#include "ThinkGear_p.h"
#include "ThinkGearEvents.h"
#include "ThinkGearStreamParser.h"
namespace libThinkGearCpp {

ThinkGear::ThinkGear()
{
    _tg_p = new ThinkGear_p(this);
}

ThinkGear_p::ThinkGear_p(ThinkGear* tg)
{
    _parsing = false;
    _tg = tg;
    _signaler = new ThinkGearSignaler(&_events);
    _parser = std::make_unique<ThinkGearStreamParser>(ParserTypes::Packets, _signaler);
}

ThinkGear::~ThinkGear()
{
    delete _tg_p;
}

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
    _tg_p->events()->connectListener(listener);    
}

void ThinkGear::removeListener(ThinkGearAbstractListener *listener)
{
    _tg_p->events()->disconnectListener(listener);
}

ThinkGearEvents* ThinkGear::events()
{
    return _tg_p->events();
}

bool ThinkGear::parsing() const
{
    return _tg_p->_parsing;
}

} // namespace libThinkGearCpp
