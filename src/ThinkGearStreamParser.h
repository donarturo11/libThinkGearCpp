#ifndef THINKGEARSTREAMPARSER_H
#define THINKGEARSTREAMPARSER_H
#include <vector>
#include "ThinkGearPayload.h"
#include "ThinkGearEvent.h"
#include "ThinkGearEvents.h"
#include "TGEnums.h"
#include "ThinkGear.h"
namespace libThinkGearCpp {

class ThinkGear;
class ThinkGearStreamParser
{
public:
    ThinkGearStreamParser(ParserTypes type = ParserTypes::Packets, ThinkGear* tg=0);
    ~ThinkGearStreamParser();
    void parseByte(unsigned char byte);
    bool isInited() const { return _status != ParserStatus::Null; }
    TGEvent<ParserStatus> onParserStatusChanged;
    TGEvent<ReceiveStatus> onReceiveStatusChanged;
    template<class ListenerClass>
    void connectListener(ListenerClass *listener) {
        TGEventConnect(onParserStatusChanged, listener, 
                           ListenerClass::onThinkGearParserStatusChanged);
        TGEventConnect(onReceiveStatusChanged, listener, 
                           ListenerClass::onThinkGearReceiveStatusChanged);        
    }
    
    template<class ListenerClass>
    void disconnectListener(ListenerClass *listener) {
        TGEventDisconnect(onParserStatusChanged, listener,
                              ListenerClass::onThinkGearParserStatusChanged);
        TGEventDisconnect(onReceiveStatusChanged, listener, 
                              ListenerClass::onThinkGearReceiveStatusChanged);
    }
private:
    void init();
    void receiveSyncByte();
    void reset();
    void initPayload();
    void writePayload();
    void checkPayload();
    void parsePayload();
    void twoByteRawInit();
    void twoByteRawParse();
protected:
    ParserTypes     _type;
    ParserStatus    _status;
    ReceiveStatus   _receive_status;
    unsigned char   _lastByte;
    ThinkGearPayloadPtr _payload;
    ThinkGear    *_tg;
};

} // namespace libThinkGearCpp

#endif
