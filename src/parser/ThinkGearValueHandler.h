#ifndef THINKGEARVALUEHANDLER_H
#define THINKGEARVALUEHANDLER_H

#ifdef __cplusplus
namespace libThinkGearCpp {
extern "C" {
#endif
typedef struct _tgvalue_handler {
    void* customData;
    void (*handleData)(void* customData, tgdata_t *d);
    void* handler_obj;
} tgvalue_handler;
#ifdef __cplusplus
} // extern "C"
} // namespace libThinkGearCpp
#endif

#ifdef __cplusplus
namespace libThinkGearCpp {

class ThinkGearPayload;
class ThinkGearValueHandler
{
public:
    ThinkGearValueHandler() = default;
    virtual ~ThinkGearValueHandler() {};
    virtual void pushData(TGData data) = 0;
};

class ValueHandler_C : public ThinkGearValueHandler
{
public:
    ValueHandler_C(tgvalue_handler* handler)
    {
        _handler=handler;
        _handler->handler_obj=this;
    }
    void pushData(TGData data)
    {
        tgdata_t d = data.TGData_c();
        _handler->handleData(_handler, &d);
    }
    tgvalue_handler* _handler;
};

} // namespace libThinkGearCpp
#endif // __cplusplus



#endif // THINKGEARVALUEHANDLER_H