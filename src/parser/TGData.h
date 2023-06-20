#ifndef TGDATA_H
#define TGDATA_H
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

#include <stdint.h>

#ifdef __cplusplus
#include <vector>
namespace libThinkGearCpp {
extern "C" {
#endif
typedef struct _tgdata_t
{
    uint8_t code;
    uint8_t size;
    uint8_t value[64];
} tgdata_t;

TGDLL uint32_t tgdata_toUInt32FromArray(tgdata_t *self, uint8_t size, uint8_t *data);
TGDLL uint32_t tgdata_toUInt32FromRow(tgdata_t *self, uint8_t row_idx, uint8_t row_width);
TGDLL uint32_t toUInt32(tgdata_t *self);
TGDLL short toShort(tgdata_t *self);
TGDLL unsigned char toUChar(tgdata_t *self);
TGDLL uint8_t* tgdata_getRow(tgdata_t *self, uint8_t row_idx, uint8_t row_width);

#ifdef __cplusplus
} // extern "C"
#endif

class TGDLL TGData
{
public:
    TGData(tgdata_t *d);
    TGData(uint8_t code, uint8_t size, uint8_t *value);
    uint32_t toUInt32FromArray(uint8_t size, uint8_t *data);
    uint32_t toUInt32() { return toUInt32FromRow(0, 4); }
    short toShort() { return toUInt32FromRow(0, 2); }
    unsigned char toUChar() { return toUInt32FromRow(0, 1); }
    uint32_t toUInt32FromRow(uint8_t row_idx, uint8_t row_width);
    uint8_t* getRow(uint8_t row_idx, uint8_t row_width);
    std::vector<uint8_t> getStructItem(uint8_t item_idx, uint8_t* sizes);
    std::vector<uint32_t> deserializeArray(uint8_t capacity);
    int size() const { return _value.size(); }
    unsigned char code() const { return _code; }
    tgdata_t TGData_c() const;
protected:
    uint8_t _code;
    std::vector<uint8_t> _value;
};

} // namespace libThinkGearCpp


#endif // TGDATA_H
