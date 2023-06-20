#ifndef THINKGEAR_PRIV_H
#define THINKGEAR_PRIV_H
#include "ThinkGear.h"
#include "TGEnums.h"
#include "ThinkGearSignaler.h"
#include "ThinkGearStreamParser.h"
#include <memory>
namespace libThinkGearCpp {
class ThinkGear;
class ThinkGearSignaler;
class ThinkGear_p
{
public:
    ThinkGear_p(ThinkGear* tg=0);
    ~ThinkGear_p(){}
	void load(unsigned char c) {
		_parser->parseByte(c);
	}
    ThinkGearEvents* events() { return &(_events); }
    ThinkGearEvents _events;
    bool _parsing;
    std::unique_ptr<ThinkGearStreamParser> _parser;
    ThinkGear* _tg;
    ThinkGearSignaler* _signaler;
};



} // namespace libThinkGearCpp

#endif // THINKGEAR_PRIV_H
