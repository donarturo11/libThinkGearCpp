#ifndef THINKGEAR_PRIV_H
#define THINKGEAR_PRIV_H
#include "ThinkGear.h"
#include "ThinkGearEvents.h"
#include "ThinkGearStreamParser.h"
#include <memory>
namespace libThinkGearCpp {
class ThinkGear_p
{
public:
    ThinkGear_p(ThinkGear* tg=0) : parsing{false}, _tg{tg} {
        stream_parser = std::make_unique<ThinkGearStreamParser>(ParserTypes::Packets, tg);
        }
    ~ThinkGear_p(){};
	void load(unsigned char c) {
		stream_parser->parseByte(c);
	}
    ThinkGearEvents events;
    bool parsing;
    std::unique_ptr<ThinkGearStreamParser> stream_parser;
    ThinkGear* _tg;
};



} // namespace libThinkGearCpp

#endif // THINKGEAR_PRIV_H
