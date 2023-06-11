#ifndef TG_PAYLOAD_PARSER_H
#define TG_PAYLOAD_PARSER_H
#include "ThinkGear.h"
#include "ThinkGearPayload.h"
#include "TGVariant.h"
#include "TGData_p.h"
#include "ThinkGearEvents.h"
#include <vector>
namespace libThinkGearCpp {
class ThinkGearPayloadParser
{
public:
    ThinkGearPayloadParser(ThinkGearPayloadPtr payload, ThinkGear* _tg=0);
    ~ThinkGearPayloadParser();
    void addRawData(unsigned char c);
private:
    void parseData();
    void process(TGRawData& data);
protected:
    ThinkGearPayloadPtr _payload;
    int _currentIndex;
    std::vector<TGRawData> _rawdata;
    ThinkGear *_tg;
    ThinkGearEvents *_events;
    //std::vector<ThinkGearData> _savedData;
};
}
#endif // TG_PAYLOAD_PARSER_H
