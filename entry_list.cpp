#include "entry_list.hpp"


entryList::entryList(){}
entryList::~entryList(){}

void entryList::setEntryList(int passed_id, std::string passed_name)
{
     id = passed_id;
     name = passed_name;
     std::cout << "passed_id is: " << passed_id << std::endl;
     std::cout << "passed_name comp is: " << passed_name << std::endl;
     std::cout << "id is: " << id << std::endl;
     std::cout << "name comp is: " << name << std::endl;

}


void entryList::push_back(entryList* e_list){
    entry_list.push_back(e_list);
}

