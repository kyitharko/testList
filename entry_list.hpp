#ifndef ENTRY_LIST_H
#define ENTRY_LIST_H
#include <iostream>
#include <string>
#include <list>

#include "new_peks.hpp"

class entryList{
      public:
            entryList();
            ~entryList();
            void setEntryList(int passed_id, std::string passed_name);
            void push_back(entryList* e_list);

            int getId();
            std::string getName();
            std::list<entryList*>::iterator begin();
           std::list<entryList*>::iterator end();
      private:
           int id;
           std::string name;
           std::list<entryList*>entry_list;

};

#endif
