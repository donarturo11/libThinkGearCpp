#include "ThinkGearValuesHandler.h"

namespace libThinkGearCpp {
ThinkGearValuesHandler::ThinkGearValuesHandler (ThinkGear *tg)
{
    if (tg) { 
		_events = tg->events();
	}
}

ThinkGearValuesHandler::ThinkGearValuesHandler (TGRawData& data, ThinkGear *tg)
{
    if (tg) { 
		_events = tg->events();
	}
	process(data);
}

void ThinkGearValuesHandler::process(TGRawData& data)
{
    TGVariant value = data.v; 
    switch (data.code)	{
		case ParserCodes::Battery: _events->onBattery(value.toUChar()); break;
		case ParserCodes::PoorSignal: _events->onPoorSignal(value.toUChar()); break;
		case ParserCodes::Attention: _events->onAttention(value.toUChar()); break;
		case ParserCodes::Meditation: _events->onMeditation(value.toUChar()); break;
		case ParserCodes::RawSignal: _events->onRaw(value.toShort()); break; //
		case ParserCodes::AsicEegPowerInt: _events->onEeg(asicEegData(data.v)); break;
	}
     
}

TG_AsicEegData ThinkGearValuesHandler::asicEegData(TGByteVector& v)
{
    TGIntEegValues values;
    TGVariant val;
    for (int i=0; i<24; ) {
        for (int j=0; j<3; j++) {
            val << v[i];
            i++;
        }
        values << val.toUInt32();
        std::cout << val.toUInt32() << std::endl;
        val.clear();
    }
    return values.data;    
}

} // namespace libThinkGearCpp