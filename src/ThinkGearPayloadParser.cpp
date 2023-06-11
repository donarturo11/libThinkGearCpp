#include "ThinkGearPayloadParser.h"
#include "TGEnums.h"
#include "ThinkGearValuesHandler.h"
#include <iostream>

namespace libThinkGearCpp {
class ThinkGear;
class ThinkGearEvents;
ThinkGearPayloadParser::ThinkGearPayloadParser(ThinkGearPayloadPtr payload, ThinkGear* tg)
: _currentIndex{0}, _tg{tg}
{
    if (_tg) {
        _events = _tg->events();
    }
    
    _payload = std::move(payload);
	parseData();
}

ThinkGearPayloadParser::~ThinkGearPayloadParser()
{}

void ThinkGearPayloadParser::parseData()
{
    while (_currentIndex < _payload->size()) {
        addRawData(_payload->at(_currentIndex));
    }
}

void ThinkGearPayloadParser::addRawData(unsigned char c)
{
    TGRawData data;
    data.code=_payload->at(_currentIndex);
    _currentIndex++;
    if (data.code < 0x80 ) {
        data.size = 1;
    } else {
        data.size = _payload->at(_currentIndex);
        _currentIndex++;
    }
	
	//std::cout << "Code: " << std::hex << (int)data.code << std::endl;
	//std::cout << "Plength " << std::hex << _payload->size() << std::endl;
	if (data.size > 2)
         std::cout << "size: " << std::dec << (int)data.size << std::endl;
	
    
    for (int i=0; i<data.size; i++) {
        data.v.push_back(_payload->at(_currentIndex));
        _currentIndex++;
    }
     
    ThinkGearValuesHandler tgv(data, _tg); 
}

void ThinkGearPayloadParser::process(TGRawData& data)
{
	switch(data.code) {
        case ParserCodes::Battery: std::cout << "battery=n"; break;
        default: std::cout << "unknown\n";
    }
}

} // namespace libThinkGearCpp
