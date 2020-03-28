#include "operation.hpp"
#include "entry_list.hpp"

#include "main_list.hpp"

operation::operation(){}
operation::~operation(){}

entryList* operation::run(std::string &uri)
{
     entryList* entry_list_outer = new entryList();
     size_t iComponentStart = 0;
     size_t iComponentEnd = 0;
     std::string str;
     std::list<entryList*>::iterator inner_it;
     int i = 0;
     iComponentEnd = uri.find("/", iComponentStart + 1);
     while (iComponentStart < uri.size()) {
           iComponentEnd = uri.find("/", iComponentStart + 1);
           if (iComponentEnd == std::string::npos)
              iComponentEnd = uri.size();
           str = getComponent(uri, iComponentStart + 1, iComponentEnd);
           iComponentStart = iComponentEnd;
           entryList *e_list;
           e_list = new entryList();
           e_list->setEntryList(i, str);
           i++;
           entry_list_outer->push_back(e_list);
           inner_it = e_list->begin();
           ++inner_it;
           //delete e_list;
      }
     return entry_list_outer;
}


std::string operation::getComponent(std::string uri, size_t iComponentStart, size_t iComponentEnd)
{
     return uri.substr(iComponentStart, iComponentEnd - iComponentStart);
}


std::string operation::getEntry(entryList *e_list)
{
     std::list<entryList*>::iterator inner_it;
     for(inner_it=e_list->begin(); inner_it != e_list->end(); ++inner_it)
     {
         entryList* entry_tmp = *inner_it;
     }
}
