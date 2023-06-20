#ifndef TGEVENT_H
#define TGEVENT_H
#include <list>
#include <functional>
#include <memory>
namespace libThinkGearCpp {
template<typename T>
class TGEventListener
{
public:
    using ListenerFn = std::function<void(T)>;
    template<class ListenerClass>
    TGEventListener(ListenerClass* listener, ListenerFn method) {
        using std::placeholders::_1;
        _function = std::make_unique< ListenerFn >( std::move(method) );
        _listener = listener;
    }
    ~TGEventListener(){ _listener = nullptr; }
    void* listener() {
        return _listener;
    }
    void operator()(T t) { (*_function)(t); }
    void notify(T t) { (*_function)(t); }
private:
    std::unique_ptr< ListenerFn > _function;
    void* _listener;
};

class TGAbstractEvent{};

template<typename T>
class TGEvent : public TGAbstractEvent
{
public:
    using ListenerFn = std::function<void(T)>;
    using EventListener = std::shared_ptr<TGEventListener<T>>;
    template<class ListenerClass, typename ListenerMethod>
    void subscribe(ListenerClass* l, ListenerMethod m) {
        using std::placeholders::_1;
        ListenerFn list_fn = std::bind(m, l, _1);
        auto listener = std::make_shared<TGEventListener<T>>(l,list_fn);
        _listeners.emplace_back(std::move(listener));
    }
    template<class ListenerClass, typename ListenerMethod>
    void unsubscribe(ListenerClass* listener, ListenerMethod method) {
        auto it = _listeners.begin();
        while (it != _listeners.end()) {
            auto l = (*it)->listener();
            if(l == listener) {
                _listeners.erase(it);
                break;
            }
            it++;
        }
    }
    void unsubscribeAll(){ _listeners.clear(); }
    void operator()(T args){ notify(args); }
    void notify(T args) {
        for (auto l : _listeners) {
            (*l)(args);
        }
    }
    std::list< std::shared_ptr<TGEventListener<T>> > _listeners;
};

template <typename T>
class TGEventCallback {
    public:
    TGEventCallback(void (*fn)(T t, void* d), void *data=nullptr) {
        callback_fn = fn;
        _data = data;
        event.subscribe(this, &TGEventCallback::call);
    }
    ~TGEventCallback() {
        event.unsubscribe(this, &TGEventCallback::call);
        callback_fn = nullptr;
        _data = nullptr;
    }
    void call(T t) {
        callback_fn(t, _data);
    }
    void (*callback_fn)(T, void*);
    void *_data;
    TGEvent<T> event;
};

template <typename T, class ListenerClass, typename ListenerMethod>
void TGEventConnect(TGEvent<T> *event, ListenerClass *listener, ListenerMethod listenerfn)
{
    event->subscribe(listener, listenerfn);
}

template <typename T, class ListenerClass, typename ListenerMethod>
void TGEventDisconnect(TGEvent<T> *event, ListenerClass *listener, ListenerMethod listenerfn)
{
    event->unsubscribe(listener, listenerfn);
}

template <typename T>
void TGEventDisconnectAll(TGEvent<T> *event)
{
    event->unsubscribeAll();
}

template <typename T>
void TGEventNotify(TGEvent<T> *event, T t)
{
    event->notify(t);
}

} // namespace libThinkGearCpp 

#endif // TGEVENT_H
