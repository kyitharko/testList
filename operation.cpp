#include "operation.hpp"
#include "entry_list.hpp"

#include "main_list.hpp"

operation::operation(){}
operation::~operation(){}

void operation::run(mainList* m, std::string* uri, std::list<int>::iterator outer_it)
{
     entryList* entry_list_outer = new entryList();
     size_t iComponentStart = 0;
     size_t iComponentEnd = 0;
     std::string str;
     std::string temp;
     temp = *uri;
     std::list<int>::iterator inner_it;
     iComponentEnd = uri->find("/", iComponentStart + 1);
     while (iComponentStart < uri->size()) {
           iComponentEnd = uri->find("/", iComponentStart + 1);
           if (iComponentEnd == std::string::npos)
              iComponentEnd = uri->size();
           str = getComponent(temp, iComponentStart + 1, iComponentEnd);
           iComponentStart = iComponentEnd;
           std::cout << "got component >>>> " << str << std::endl;
           entryList *e_list;
           e_list = new entryList();
           e_list->setEntryList(i, str);
           std::cout << "setEntryList finisted!!!" << std::endl;
           i++;
           std::cout << "this is i: " << i << std::endl;
           entry_list_outer->push_back(e_list);
           inner_it = e_list->begin();
           ++inner_it;
           std::cout << "pushed back to list" << std::endl;
           delete e_list;
      }
      m->push_back(entry_list_outer);
      ++outer_it;
}


std::string operation::getComponent(std::string uri, size_t iComponentStart, size_t iComponentEnd)
{
       return uri.substr(iComponentStart, iComponentEnd - iComponentStart);
}

