#include "ThinkGear.h"
#include "thinkgear_c.h"
#include <stdlib.h>
namespace thinkgear_c {
class ThinkGearListener : public libThinkGearCpp::ThinkGearAbstractListener
{
public:
    ThinkGearListener(tg_listener_t *listener) {
        _listener = listener;
        _receiver = listener->receiver;
        _listener->sender = this;
    }
    ~ThinkGearListener(){ };
    void onThinkGearRaw(short val){ _listener->ops->onRaw(_receiver, val); }
    void onThinkGearBattery(unsigned char val){ _listener->ops->onBattery(_receiver, val); }
    void onThinkGearPoorSignal(unsigned char val){ _listener->ops->onPoorSignal(_receiver, val); }
    void onThinkGearBlinkStrength(unsigned char val){ _listener->ops->onBlinkStrength(_receiver, val); }
    void onThinkGearAttention(unsigned char val){ _listener->ops->onAttention(_receiver, val); }
    void onThinkGearMeditation(unsigned char val){ _listener->ops->onMeditation(_receiver, val); }
    void onThinkGearEeg(TG_AsicEegData val){ _listener->ops->onEeg(_receiver, val); }
    void onThinkGearConnecting(unsigned char val){ _listener->ops->onConnecting(_receiver, val); }
    void onThinkGearReady(unsigned char val){ _listener->ops->onReady(_receiver, val); }
    void onThinkGearError(unsigned char val){ _listener->ops->onError(_receiver, val); }
private:
    tg_listener_t *_listener;
    void *_receiver;
};
}


extern "C" {

using namespace libThinkGearCpp;
using namespace thinkgear_c;

ThinkGear* TG_Obj(thinkgear_t *tg_cpp)
{
    return reinterpret_cast<ThinkGear*>(tg_cpp->tg_obj);
}

ThinkGearListener* TGListener_Obj(tg_listener_t* listener)
{
    return reinterpret_cast<ThinkGearListener*>(listener->sender);
}

void TG_Init(thinkgear_t *tg)
{
    tg->ops = (thinkgear_ops*) malloc(sizeof(thinkgear_ops));
    tg->ops->load = TG_Load;
    tg->ops->load_buffer = TG_LoadBuffer;
    tg->ops->add_listener = TG_AddListener;
    tg->ops->remove_listener = TG_RemoveListener;
    tg->tg_obj = new ThinkGear();
}

void TG_Destroy(thinkgear_t *tg)
{
    free(tg->ops);
    delete reinterpret_cast<ThinkGear*>(tg->tg_obj);
}

void TG_Load(thinkgear_t *tg, char c)
{
    auto tg_obj = TG_Obj(tg);
    tg_obj->load(c);
}

void TG_LoadBuffer(thinkgear_t *tg, char* buffer, int size)
{
    auto tg_obj = TG_Obj(tg);
    tg_obj->load(buffer, size);
}

void TG_AddListener(thinkgear_t *tg, tg_listener_t *listener)
{
    auto tg_obj = TG_Obj(tg);
    auto list_obj = reinterpret_cast<ThinkGearListener*>(listener->sender);
    tg_obj->addListener(list_obj);
}

void TG_RemoveListener(thinkgear_t *tg, tg_listener_t *listener)
{
    auto tg_obj = TG_Obj(tg);
    auto list_obj = reinterpret_cast<ThinkGearListener*>(listener->sender);
    tg_obj->removeListener(list_obj);
}

/*------------------------------------*/
void TGListener_Init(tg_listener_t *listener)
{
    listener->ops = (tg_listener_ops*) malloc(sizeof(tg_listener_ops));
    listener->sender = new ThinkGearListener(listener);
}

void TGListener_Destroy(tg_listener_t *listener)
{
    delete reinterpret_cast<ThinkGearListener*>(listener->sender);
    free(listener->ops);
}

} // extern "C"
