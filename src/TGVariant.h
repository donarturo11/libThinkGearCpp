#ifndef TGVARIANT_H
#define TGVARIANT_H
#include <vector>
#include <cstdint>

namespace libThinkGearCpp {
typedef std::vector<unsigned char> TGByteVector;

union TGVariantUnion {
    float Float;
    uint32_t UInt32;
    int32_t Int32;
    unsigned char byteArray[4];
};

class TGVariant
{
public:
    TGVariant() : _size{0}, _value{0} {}
    TGVariant(int8_t val) { setInt32((int32_t) val); }
    TGVariant(uint8_t val) { setUInt32((uint32_t) val); }
    TGVariant(short val) { setShort(val); }
    TGVariant(uint32_t val) { setUInt32(val); }
    TGVariant(int32_t val) { setInt32(val); }
    TGVariant(float val) { setFloat(val); }
    TGVariant(TGByteVector vec) : _size{0} 
        { setByteArray(vec); }
    TGVariant(unsigned char* data, int size) : _size{0}
        { setByteArray(data, size); }
    ~TGVariant() {}
    /* operators */
    void operator=(short s) { setShort(s); }
    void operator=(uint32_t ui) { setUInt32(ui); }
    void operator=(int32_t i) { setInt32(i); }
    void operator=(float f) { setFloat(f); }
    void operator=(TGByteVector vec) { setByteArray(vec); }
    void operator<< (unsigned char c) { add(c); }
    void operator<<(TGByteVector v) { setByteArray(v); }
    /* setters */
    void setFloat(float val) { _value.Float = val; _size = sizeof(float); }
    void setUInt32(uint32_t val) { _value.UInt32 = val; _size = sizeof(uint32_t); }
    void setInt32(int32_t val) { _value.Int32 = val; _size = sizeof(int32_t); }
    void setShort(short val){ setInt32(val); _size = sizeof(short); }
    void setByteArray(unsigned char* arr, int size);
    void setByteArray(TGByteVector vec);
    /* getters */
    uint32_t toUInt32() const { return _value.UInt32; }
    int32_t toInt32() const {return _value.Int32;}
    float toFloat() const { return _value.Float; }
    short toShort() const { return (_value.Int32 & 0xFFFF); }
    unsigned char toUChar() const { return (_value.Int32 & 0xFF); }
    char toChar() const { return (_value.UInt32 & 0xFF); }
    unsigned char * toByteArray() const;
    TGByteVector toByteVector() const;
    int size() const { return _size; }
    /* modifiers */
    void putAt(int index, unsigned char c);
    void putAtNumber(int numberIdx, unsigned char c);
    void add(unsigned char c);
    void clear() { _value.UInt32=0; _size=0; }
    unsigned char at(int index) const { return (_value.UInt32 >> byteShift(index)) & 0xFF; }
private:
    int byteShift(int index) const;
    void fill();
protected:
    TGVariantUnion _value;
    int _size;
};
} // namespace libThinkGearCpp
    
    

#endif // TGVARIANT_H
