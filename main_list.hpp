#ifndef _MAIN_LIST_HPP
#define _MAIN_LIST_HPP

#include <iostream>
#include <string>
#include <list>
#include "entry_list.hpp"

class mainList{
      public:
            mainList();
            ~mainList();
            void push_back(entryList* e_list);
            std::list<entryList*>::iterator begin();
            std::list<entryList*>::iterator end();
     private:
            std::list<entryList*>main_list;
};

#endif
