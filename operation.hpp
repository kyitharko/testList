#ifndef OPERATION_H
#define OPERATION_H
#include <iostream>
#include <string>
#include <list>

#include "main_list.hpp"

class operation{

      public:

           operation();
           ~operation();
           entryList* trapdoor(std::string &uri);
           entryList* peks(std::string &uri);
           std::string getComponent(std::string uri, size_t iComponentStart, size_t iComponentEnd);
           std::string getEntry(entryList* e_list);

};

#endif
