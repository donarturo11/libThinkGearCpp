#ifndef THINKGEAR_H
#define THINKGEAR_H

#if defined _WIN32 || defined __CYGWIN__
  #if defined(LIBTHINKGEARCPP_EXPORT)
    #define LIBTHINKGEARCPP_DLL_PUBLIC __declspec(dllexport)
  #else
    #define LIBTHINKGEARCPP_DLL_PUBLIC
  #endif
#else
  #if __GNUC__ >= 4
    #define LIBTHINKGEARCPP_DLL_PUBLIC __attribute__( (visibility( "default" )) )
  #else
    #define LIBTHINKGEARCPP_DLL_PUBLIC
  #endif
#endif

#include <memory>
namespace libThinkGearCpp {
class ThinkGearEvents;
class ThinkGear_p;
class ThinkGear
{
public:
    ThinkGear();
    ~ThinkGear();
    void load(char* buffer, int size);
    void load(char c);
    
    template <class ListenerClass>
        void addListener(ListenerClass *listener);
    template <class ListenerClass>
        void removeListener(ListenerClass *listener);
    
    ThinkGearEvents* events();
    bool parsing() const;
private:
    std::unique_ptr<ThinkGear_p> _tg_p;
};

typedef std::shared_ptr<ThinkGear> ThinkGearPtr;

} // namespace libThinkGearCpp
#endif // THINKGEAR_H
