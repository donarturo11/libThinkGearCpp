#ifndef THINKGEARSTREAMPARSER_H
#define THINKGEARSTREAMPARSER_H

#if defined _WIN32 || defined __CYGWIN__
  #if defined(EXPORT)
    #define TGDLL __declspec(dllexport)
  #else
    #define TGDLL
  #endif
#else
  #if __GNUC__ >= 4
    #define TGDLL __attribute__( (visibility( "default" )) )
  #else
    #define TGDLL
  #endif
#endif

#ifdef __cplusplus
#include <vector>
#include <queue>
#include <memory>
#endif
#include "TGEnums.h"
#include "TGData.h"
#include "ThinkGearValueHandler.h"

#ifdef __cplusplus
namespace libThinkGearCpp {
#endif

#ifdef __cplusplus
//class ThinkGearValueHandler
class TGDLL ThinkGearStreamParser
{
public:
    
    ThinkGearStreamParser(ParserTypes type = ParserTypes::Packets, ThinkGearValueHandler *_handler = 0);
    ~ThinkGearStreamParser();
    void parseByte(unsigned char byte);
    bool isInited() const { return _status != ParserStatus::Null; }
    int availableData() { return _received_data.size(); }
    TGData getData();
    std::vector<TGData> getAllData();
    void pushToQueue(TGData data);
    ThinkGearValueHandler* valueHandler() const { return _handler; }
    static void setQueueCapacity(int cap) { queue_capacity = cap; }
    static int queueCapacity() { return queue_capacity; }
private:
    static int queue_capacity;
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
    std::unique_ptr<ThinkGearPayload> _payload;
    ThinkGearValueHandler* _handler;
    std::queue<TGData>  _received_data;
    int _queue_capacity;
};


#endif

#ifdef __cplusplus
extern "C" {
#endif    
typedef struct _tgstream_parser_t {
    ThinkGearStreamParser *parser;
    ValueHandler_C *handler;
} tgstream_parser_t;

TGDLL void tgstream_parser_init(tgstream_parser_t *self, int type, tgvalue_handler* handler);
TGDLL void tgstream_parser_delete(tgstream_parser_t *self);
TGDLL void tgstream_parser_parseByte(tgstream_parser_t *self, unsigned char c);
TGDLL int  tgstream_parser_available(tgstream_parser_t *self);
TGDLL tgdata_t tgstream_parser_getData(tgstream_parser_t *self);

#ifdef __cplusplus
} // extern "C"
} // namespace libThinkGearCpp
#endif

#endif // THINKGEARSTREAMPARSER_H
