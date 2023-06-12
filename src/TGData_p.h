#ifndef TGDATA_H
#define TGDATA_H
#include <vector>
#include "ThinkGear.h"
namespace libThinkGearCpp {
struct TGData {
    TGData() : size{0} {}
    int code;
    int size;
};

struct TGRawData : TGData
{
    void operator <<(unsigned char c) {
        v.push_back(c);
        size = v.size();
    }
    std::vector<unsigned char> v;
};

struct TGShort : TGData
{
    TGShort() {
       size = sizeof(short);
    }
    short v;
};

struct TGInt : TGData
{
    TGInt() {
        size = sizeof(int);
    }
    int v;
};

struct TGIntEegValues : TGData
{
    TG_AsicEegData data;
    /* Iterators */
    unsigned int* begin;
    unsigned int* end;
    unsigned int* it;
    /*           */
    TGIntEegValues() : begin{&(data.eegDelta)},
                       end{&(data.eegMidGamma)+1},
                       it{begin}
    {
        size = 3 * 8;
    }
    void operator <<(unsigned int val) {
        *it = val;
        *it++;
        if (*it == *end) *it = *begin;
        }
};
} // namespace libThinkGearCpp
#endif
