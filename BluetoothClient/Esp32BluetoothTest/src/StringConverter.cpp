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

std::string StringConverter::stringToBinary(const std::string &input)
{
  std::ostringstream binaryStream;

  for (unsigned char c : input)
  {
    binaryStream << std::bitset<8>(c); // Convert each char to 8-bit binary
  }

  return binaryStream.str();
}