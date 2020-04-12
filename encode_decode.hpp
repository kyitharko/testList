#ifndef ENCODE_DECODE_HPP
#define ENCODE_DECODE_HPP
#include <string>
void stringToUnsignedChar(std::string in_str, unsigned char* converted);
std::string unsignedCharToString(unsigned char* in_data, unsigned int len);
void stringToChar(std::string in_str, char* converted);
std::string charToString(char* in_data, unsigned int len);
std::string GetHexFromBin(std::string sBinary, unsigned int len);
std::string GetBinFromHex(std::string sHex);
#endif
