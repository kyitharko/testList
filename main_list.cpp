#include "main_list.hpp"

mainList::mainList(){}
mainList::~mainList(){}


void mainList::push_back(entryList* e_list){
    main_list.push_back(e_list);
}


std::list<entryList*>::iterator mainList::begin()
{
    std::list<entryList*>::iterator it;
    it = main_list.begin();
    return it;
}



std::list<entryList*>::iterator mainList::end()
{
    std::list<entryList*>::iterator it;
    it = main_list.end();
    return it;
}
