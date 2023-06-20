#include "ThinkGearSignaler.h"
namespace libThinkGearCpp {

ThinkGearSignaler::ThinkGearSignaler(ThinkGearEvents *ev)
{
    _events = ev; 
}

void ThinkGearSignaler::pushData(TGData d)
{
    if (!_events) {
        return;
    }
    switch (d.code()) {
        case ParserCodes::Battery: _events->onBattery(d.toUChar()); break;
        case ParserCodes::PoorSignal: _events->onPoorSignal(d.toUChar()); break;
        case ParserCodes::Attention: _events->onAttention(d.toUChar()); break;
        case ParserCodes::Meditation: _events->onMeditation(d.toUChar()); break;
        case ParserCodes::RawSignal: _events->onRaw(d.toShort()); break;
        case ParserCodes::AsicEegPowerInt: _events->onEeg(asicEegData(d.deserializeArray(8))); break;
    }
}

eegData ThinkGearSignaler::asicEegData(std::vector<uint32_t> v)
{
    eegData d;
    d.eegSum = 0;
    uint32_t *begin = &(d.eegDelta);
    uint32_t *end = &(d.eegMidGamma) + 1;
    uint32_t *item = begin;
    for ( auto i : v ) {
       *item = i;
       d.eegSum += i;
       item++; 
    }
    return d;
}
} // namespace libThinkGearCpp
