#include "entry_list.hpp"


entryList::entryList(){}
entryList::~entryList(){}

void entryList::setEntryList(int passed_id, std::string passed_name)
{
     id = passed_id;
     name = passed_name;
}


void entryList::push_back(entryList* e_list){
    entry_list.push_back(e_list);
}


std::list<entryList*>::iterator entryList::begin()
{
    std::list<entryList*>::iterator it;
    it = entry_list.begin();
    return it;
}


std::list<entryList*>::iterator entryList::end()
{
    std::list<entryList*>::iterator it;
    it = entry_list.end();
    return it;
}


int entryList::getId()
{
   return id;
}


std::string entryList::getName()
{
   return name;
}
