#ifndef STRING_CONVERTER_H
#define STRING_CONVERTER_H

#include <iostream>
#include <bitset>
#include <iomanip>
#include <sstream>

class StringConverter
{
public:
    static std::string stringToHex(const std::string &input);
    static std::string stringToBinary(const std::string &input);
};

#endif // STRING_CONVERTER_H