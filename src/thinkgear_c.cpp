#include "ThinkGear.h"
#include "thinkgear_c.h"
#include <stdlib.h>
using namespace libThinkGearCpp;
namespace thinkgear_c {
class ThinkGearListener
{
public:
    ThinkGearListener(tg_listener_t *listener) {
        _listener = listener;
    }
    ~ThinkGearListener();
    void onRaw(short val);
    void onBattery(unsigned char val);
    void onPoorSignal(unsigned char val);
    void onBlinkStrength(unsigned char val);
    void onAttention(unsigned char val);
    void onMeditation(unsigned char val);
    void onEeg(TG_AsicEegData val);
    void onConnecting(unsigned char val);
    void onReady(unsigned char val);
    void onError(unsigned char val);
private:
    tg_listener_t *_listener;
};
}


/*  ThinkGear Interface */
void TG_Obj_Init(thinkgear_t *tg)
{
    tg->tg_obj = new ThinkGear();
}

void TG_Obj_Destroy(thinkgear_t *tg)
{
    delete reinterpret_cast<ThinkGear*>(tg->tg_obj);
}

ThinkGear* TG_Obj(ThinkGear *tg_cpp)
{
    return reinterpret_cast<ThinkGear*>(tg_cpp);
}

void TG_Obj_Load(thinkgear_t *tg, char c)
{
    reinterpret_cast<ThinkGear*>(tg->tg_obj)->load(c);
}

void TG_Obj_LoadBuffer(thinkgear_t *tg, char* buffer, int size)
{
    reinterpret_cast<ThinkGear*>(tg->tg_obj)->load(buffer, size);
}

void TG_Obj_AddListener(thinkgear_t *tg, tg_listener_t *listener)
{
    reinterpret_cast<ThinkGear*>(tg->tg_obj)->addListener(listener->sender);
}

void TG_Obj_RemoveListener(thinkgear_t *tg, tg_listener_t *listener)
{
    reinterpret_cast<ThinkGear*>(tg->tg_obj)->removeListener(listener->sender);
}

/*  ThinkGearListener Interface */

using namespace thinkgear_c;
void TGListener_Obj_Init(tg_listener_t *listener)
{
    listener->sender = new ThinkGearListener(listener);
}

void TGListener_Obj_Destroy(tg_listener_t *listener)
{
    delete reinterpret_cast<ThinkGearListener*>(listener->sender);
}
//==========================
extern "C" {
void TG_Init(thinkgear_t *tg)
{
    tg->ops = (thinkgear_ops*) malloc(sizeof(thinkgear_ops));
    tg->ops->load = TG_Load;
    tg->ops->load_buffer = TG_LoadBuffer;
    tg->ops->add_listener = TG_AddListener;
    tg->ops->remove_listener = TG_RemoveListener;
    TG_Obj_Init(tg);
}

void TG_Destroy(thinkgear_t *tg)
{
    free(tg->ops);
    TG_Obj_Destroy(tg);
}

void TG_Load(thinkgear_t *tg, char c)
{
    TG_Obj_Load(tg, c);
}

void TG_LoadBuffer(thinkgear_t *tg, char* buffer, int size)
{
    TG_Obj_LoadBuffer(tg, buffer, size);
}

void TG_AddListener(thinkgear_t *tg, tg_listener_t *listener)
{
    TG_Obj_AddListener(tg, listener);
}

void TG_RemoveListener(thinkgear_t *tg, tg_listener_t *listener)
{
    TG_Obj_RemoveListener(tg, listener);
}

/*------------------------------------*/
void TGListener_Init(tg_listener_t *listener)
{
    listener->ops = (tg_listener_ops*) malloc(sizeof(tg_listener_ops));
    TGListener_Obj_Init(listener);
}

void TGListener_Destroy(tg_listener_t *listener)
{
    TGListener_Obj_Destroy(listener);
    free(listener->ops);
}

} // extern "C"
