#include "TGData.h"
namespace libThinkGearCpp {
TGData::TGData(tgdata_t *d)
{
    int size = d->size;
    _code = d->code;
    _value = std::vector<uint8_t>(d->value, (d->value)+size);
}

TGData::TGData(uint8_t code, uint8_t size, uint8_t *value)
{
    _code = code;
    _value = std::vector<uint8_t>(value, value+size);
}

uint32_t TGData::toUInt32FromArray(uint8_t size, uint8_t *data)
{
    uint32_t val = 0;
    uint8_t shift = (size-1) * 8;
    for (int i=0; i<size; i++) {
        val |= data[i] << shift;
        shift -= 8;
    }
    return val;
}

uint32_t TGData::toUInt32FromRow(uint8_t row_idx, uint8_t row_width)
{
    uint8_t* row = getRow(row_idx, row_width);
    return toUInt32FromArray(row_width, row);
}

uint8_t* TGData::getRow(uint8_t row_idx, uint8_t row_width)
{
    uint8_t pos = row_idx * row_width;
    auto data = _value.data();
    return data + pos;
}

std::vector<uint8_t> TGData::getStructItem(uint8_t item_idx, uint8_t* sizes)
{
    uint8_t pos = 0;
    uint8_t item_size = 0;
    for (int i=0; i < item_idx; i++) {
        item_size = sizes[i];
        pos += item_size;
    }
    auto begin = _value.begin() + pos;
    auto end = begin + item_size;
    return std::vector<uint8_t>(begin, end);
}

std::vector<uint32_t> TGData::deserializeArray(uint8_t capacity)
{
    std::vector<uint32_t> values;
    uint8_t row_width = size() / capacity;
    for (int i = 0; i < capacity; i++)
        values.push_back(toUInt32FromRow(i, row_width));
    return values;
}

tgdata_t TGData::TGData_c() const
{
    tgdata_t data;
    data.code = _code;
    data.size = 0;
    for (auto it : _value) {
        data.value[data.size] = it;
        data.size++;
    }
    return data;
}

extern "C" {

uint32_t tgdata_toUInt32(tgdata_t *self)
{
    TGData d(self);
    return d.toUInt32();
}

short tgdata_toShort(tgdata_t *self)
{
    TGData d(self);
    return d.toShort();
}

unsigned char tgdata_toUChar(tgdata_t *self)
{
    TGData d(self);
    return d.toUChar();
}

uint32_t tgdata_toUInt32FromArray(tgdata_t *self, uint8_t size, uint8_t *data)
{
    TGData d(self);
    return d.toUInt32FromArray(size, data);
}

uint32_t tgdata_toUInt32FromRow(tgdata_t *self, uint8_t row_idx, uint8_t row_width)
{
    TGData d(self);
    return d.toUInt32FromRow(row_idx, row_width);
}

uint8_t* tgdata_getRow(tgdata_t *self, uint8_t row_idx, uint8_t row_width)
{
    TGData d(self);
    return d.getRow(row_idx, row_width);
}

uint32_t toUInt32(tgdata_t *self)
{
    TGData d(self);
    return d.toUInt32();
}

short toShort(tgdata_t *self)
{
    TGData d(self);
    return d.toShort();
}

unsigned char toUChar(tgdata_t *self)
{
    TGData d(self);
    return d.toUChar();
}

} // extern "C"

} // namespace libThinkGearCpp
