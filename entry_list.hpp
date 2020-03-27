#ifndef ENTRY_LIST_H
#define ENTRY_LIST_H
#include <iostream>
#include <string>
#include <list>

class entryList{
      public:
            entryList();
            ~entryList();
            void setEntryList(int passed_id, std::string passed_name);
            void push_back(entryList* e_list);
      private:
           int id;
           std::string name;
           std::list<entryList*>entry_list;
};

#endif
