#ifndef THINKGEAR_C_H
#define THINKGEAR_C_H

#if defined(LIBTHINKGEARCPP_EXPORT)
  #if defined _WIN32 || defined __CYGWIN__
    #define THINKGEARAPI __declspec(dllexport)
  #else
    #define THINKGEARAPI __attribute__((visibility("default")))
  #endif
#else
  #define THINKGEARAPI //__declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _thinkgear_t thinkgear_t;
typedef struct _thinkgear_ops thinkgear_ops;
typedef struct _tg_listener_t tg_listener_t;
typedef struct _tg_listener_ops tg_listener_ops;
typedef struct _TG_AsicEegData TG_AsicEegData;

typedef struct _thinkgear_t {
    void *tg_obj;
    thinkgear_ops *ops;
} thinkgear_t;

typedef struct _thinkgear_ops {
    void (*load)(thinkgear_t *tg, char c);
    void (*load_buffer)(thinkgear_t *tg, char* buffer, int size);
    void (*add_listener)(thinkgear_t *tg, tg_listener_t *listener);
    void (*remove_listener)(thinkgear_t *tg, tg_listener_t *listener);
} thinkgear_ops;

typedef struct _tg_listener_t {
    void *receiver;
    void *sender;
    tg_listener_ops *ops;
} tg_listener_t;

typedef struct _tg_listener_ops {
    void (*onRaw)(void* receiver, short val);
    void (*onBattery)(void* receiver, unsigned char val);
    void (*onPoorSignal)(void* receiver, unsigned char val);
    void (*onBlinkStrength)(void* receiver, unsigned char val);
    void (*onAttention)(void* receiver, unsigned char val);
    void (*onMeditation)(void* receiver, unsigned char val);
    void (*onEeg)(void* receiver, TG_AsicEegData val);
    void (*onConnecting)(void* receiver, unsigned char val);
    void (*onReady)(void* receiver, unsigned char val);
    void (*onError)(void* receiver, unsigned char val);
} tg_listener_ops;

void TG_Init(thinkgear_t *tg);
void TG_Destroy(thinkgear_t *tg);
void TG_Load(thinkgear_t *tg, char c);
void TG_LoadBuffer(thinkgear_t *tg, char *buffer, int size);
void TG_AddListener(thinkgear_t *tg, tg_listener_t *listener);
void TG_RemoveListener(thinkgear_t *tg, tg_listener_t *listener);

void TGListener_Init(tg_listener_t *listener);
void TGListener_Destroy(tg_listener_t *listener);

#ifdef __cplusplus
}
#endif        



#endif // THINKGEAR_C_H
