#include "StringConverter.h"

std::string StringConverter::stringToHex(const std::string &input)
{
  std::ostringstream hexStream;
  hexStream << std::hex << std::setfill('0'); // Ensures leading zeros if needed

  for (unsigned char c : input)
  {
    hexStream << std::setw(2) << static_cast<int>(c); // Converts each char to hex
  }

  return hexStream.str();
}
std::string StringConverter::stringToHex(const char &c)
{
  std::ostringstream hexStream;
  hexStream << std::hex << std::setfill('0'); // Ensures leading zeros if needed
  hexStream << std::setw(2) << static_cast<int>(c); // Converts each char to hex
  return hexStream.str();
}

std::string StringConverter::stringToBinary(const char &c)
{
  std::ostringstream binaryStream;
    binaryStream << std::bitset<8>(c); // Convert each char to 8-bit binary
  return binaryStream.str();
}
std::string StringConverter::stringToBinary(const std::string &input)
{
  std::ostringstream binaryStream;

  for (unsigned char c : input)
  {
    binaryStream << std::bitset<8>(c); // Convert each char to 8-bit binary
  }

  return binaryStream.str();
}