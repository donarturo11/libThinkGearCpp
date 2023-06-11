#include "TGVariant.h"
#include <cstring>
#include <memory>

namespace libThinkGearCpp {

void TGVariant::setByteArray(unsigned char* arr, int size)
{
    clear();
    for (int i=0; i<size; i++) add(arr[i]);
    fill();
}

void TGVariant::setByteArray(TGByteVector vec)
{
    clear();
    for (auto c : vec) add(c);
    fill();
}

unsigned char * TGVariant::toByteArray() const
{
    unsigned char* arr = new unsigned char[_size];
    for (int i=0; i<_size; i++) {
        arr[i] = at(i);
    }
    return std::move(arr);
}

TGByteVector TGVariant::toByteVector() const
{
    TGByteVector vec;
    for (int i=0; i<_size; i++)
        vec.push_back(at(i));
    return vec;
}

void TGVariant::add(unsigned char c)
{
    _value.UInt32 = _value.UInt32 << 8;
    _value.UInt32 |= c;
    if (_size < sizeof(TGVariantUnion))
        _size++;
}

void TGVariant::putAtNumber(int numberIdx, unsigned char c)
{
    int idx = (sizeof(TGVariantUnion) - _size) + numberIdx;
    putAt(idx,c);
}

void TGVariant::putAt(int index, unsigned char c)
{
    int shift = (sizeof(TGVariantUnion)-1)*8 - (index*8);
    int mask = ~(0xFF << shift);
    _value.UInt32 &= mask;
    _value.UInt32 |= c << shift;  
}

/* private */

int TGVariant::byteShift(int index) const
{
    int maxShift = (_size-1) * 8;
    return maxShift - (index*8);
}

void TGVariant::fill()
{
    if (_size == sizeof(TGVariantUnion)) return;
    int32_t mask=0;
    if ((char)at(0)<0) {
        mask = 0xFF;
        for (int i=0; i<_size; i++){
            mask |= 0xFF << i*8;
        }
        _value.UInt32 |= ~mask;
    }
}

} // namespace libThinkGearCpp
