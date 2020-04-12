#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include "encode_decode.hpp"

void stringToUnsignedChar(std::string in_str, unsigned char* converted)
{
    std::vector<unsigned char> uchars;
    std::vector<char> chars{ begin(in_str), end(in_str) };
    transform(begin(in_str), end(in_str), back_inserter(in_str),
     [](unsigned char c) { return reinterpret_cast<unsigned char>(c); });
    for(auto i: uchars)
    {
       converted[i] = uchars[i];
    }
}

std::string unsignedCharToString(unsigned char* in_data, unsigned int len)
{
    std::stringstream ss;
    //std::cout << "in_data is " << endl;
    for(int i = 0; i < len; ++i)
    {
       ss << std::hex << (int)in_data[i];
       //printf("%x", in_data[i]);
    }
    //std::cout << std::endl;
    std::string out_str = ss.str();

    return out_str;
}

void stringToChar(std::string in_str, char* converted)
{
  std::string tmp = GetBinFromHex(in_str);
  std::size_t length = tmp.copy(converted, tmp.length(), 0);
  converted[length] = '\0';
}

std::string charToString(char* in_data, unsigned int len)
{
   std::string tmp = "";
   for(unsigned int i = 0; i < len; i++)
      if(in_data[i] == '0')
         tmp = tmp + '0';
      else
         tmp = tmp + '1';

   std::string result = GetHexFromBin(tmp, len);
   return result;
}


std::string GetHexFromBin(std::string sBinary, unsigned int len)
{
        std::string rest, tmp = "";
        unsigned int count = 0;

        if(len == 159)
           count = 156;
        else
           count = len;

        for (int i=0;i<count;i+=4)
        {
                tmp = sBinary.substr(i,4);
                if (!tmp.compare("0000"))
                {
                        rest = rest + "0";
                }
                else if (!tmp.compare("0001"))
                {
                        rest = rest + "1";
                }
                else if (!tmp.compare("0010"))
                {
                        rest = rest + "2";
                }
                else if (!tmp.compare("0011"))
                {
                        rest = rest + "3";
                }
                else if (!tmp.compare("0100"))
                {
                        rest = rest + "4";
                }
                else if (!tmp.compare("0101"))
                {
                        rest = rest + "5";
                }
                else if (!tmp.compare("0110"))
                {
                        rest = rest + "6";
                }
                else if (!tmp.compare("0111"))
                {
                        rest = rest + "7";
                }
                else if (!tmp.compare("1000"))
                {
                        rest = rest + "8";
                }
                else if (!tmp.compare("1001"))
                {
                        rest = rest + "9";
                }
                else if (!tmp.compare("1010"))
                {
                        rest = rest + "A";
                }
                else if (!tmp.compare("1011"))
                {
                        rest = rest + "B";
                }
                else if (!tmp.compare("1100"))
                {
                        rest = rest + "C";
                }
                else if (!tmp.compare("1101"))

                {
                        rest = rest + "D";
                }
                else if (!tmp.compare("1110"))
                {
                        rest = rest + "E";
                }
                else if (!tmp.compare("1111"))
                {
                        rest = rest + "F";
                }
                else
                {
                        continue;
                }
        }
        if(count == 156)
        {
          tmp = sBinary.substr(count, 3);
          rest.append(tmp);

        }
        return rest;
}


std::string GetBinFromHex(std::string sHex)
{
        std::string tmp, rest ="";
        int len = 0;
        if(sHex.length() == 42)
          len = 39;
        else
          len = sHex.length();

        for (int i=0;i<len;i++)
        {
                tmp = sHex[i];
                if (!tmp.compare("0"))
                {
                        rest = rest + "0000";
                }
                else if (!tmp.compare("1"))
                {
                        rest = rest + "0001";
                }
                else if (!tmp.compare("2"))
                {
                        rest = rest + "0010";
                }
                else if (!tmp.compare("3"))
                {
                        rest = rest + "0011";
                }
                else if (!tmp.compare("4"))
                {
                        rest = rest + "0100";
                }
                else if (!tmp.compare("5"))
                {
                        rest = rest + "0101";
                }
                else if (!tmp.compare("6"))
                {
                        rest = rest + "0110";
                }
                else if (!tmp.compare("7"))
                {
                        rest = rest + "0111";
                }
                else if (!tmp.compare("8"))
                {
                        rest = rest + "1000";
                }
                else if (!tmp.compare("9"))
                {
                        rest = rest + "1001";
                }
                else if (!tmp.compare("A"))
                {
                        rest = rest + "1010";
                }
                else if (!tmp.compare("B"))
                {
                        rest = rest + "1011";
                }
                else if (!tmp.compare("C"))
                {
                        rest = rest + "1100";
                }
                else if (!tmp.compare("D"))
                {
                        rest = rest + "1101";
                }
                else if (!tmp.compare("E"))
                {
                        rest = rest + "1110";
                }
                else if (!tmp.compare("F"))
                {
                        rest = rest + "1111";
                }
                else
                {
                        continue;
                }
        }
          if(len == 39)
            {
            tmp = sHex.substr(len, 3);
            rest.append(sHex, len, 3);
            }

        return rest;
}


