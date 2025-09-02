#include <cstddef>
#include <string>
#include <ArduinoLog.h>
#ifndef BUFFER_HELPER_H
#define BUFFER_HELPER_H

class BufferHelper 
{
public:
    static uint8_t read_8bit (const std::string &data, const size_t &offset)
    {
        if ((offset+1) >= data.size())
        {
            Log.errorln("BufferHelper::read: Offset %zu is out of bounds for data size %zu", offset, data.size());
            return 0;
        }
        return static_cast<uint8_t>(data[offset]);
    }

    static uint16_t read_16bit (const std::string &data, const size_t &offset)
    {
        if ((offset+2) >= data.size())
        {
            Log.errorln("BufferHelper::read: Offset %zu is out of bounds for data size %zu", offset, data.size());
            return 0;
        }
        return static_cast<uint16_t>(data[offset]) | (static_cast<uint16_t>(data[offset + 1]) << 8);
    }
};


#endif // BUFFER_HELPER_H