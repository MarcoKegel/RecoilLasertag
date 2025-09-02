#include <cstddef>
#include <string>
#include <cstdint>
#ifndef BUFFER_HELPER_H
#define BUFFER_HELPER_H

class BufferHelper{
public:
    static uint8_t read_8bit(const std::string &data, size_t offset)
    {
        if (offset >= data.size())
        {
            return 0;
        }
        return static_cast<uint8_t>(data[offset]);
    }

    static uint8_t read_8bit(const uint8_t* data, size_t size, size_t offset)
    {
        if (data == nullptr || offset >= size)
        {
            return 0;
        }
        return data[offset];
    }
    

    static uint16_t read_16bit (const std::string &data, size_t offset)
    {
        if ((offset+2) >= data.size())
        {
            return 0;
        }
        return static_cast<uint16_t>(data[offset]) | (static_cast<uint16_t>(data[offset + 1]) << 8);
    }
};


#endif // BUFFER_HELPER_H