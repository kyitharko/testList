#include <iostream>
#include <string>
#include <list>
#include <fstream>

#include "entry_list.hpp"
#include "main_list.hpp"
#include "operation.hpp"


int main(int argc, char **argv){
	if (argc != 2) {
                std::cout << "Usage: %s is e.g., path to file\n" << argv[0] << std::endl;
                return 1;
         }

         mainList *m;
         entryList* entry_ptr;
         m = new mainList();
         operation *opt;
         std::string address = *(++argv);
         std::list<entryList*>::iterator outer_it;
         outer_it = m->begin();
         std::list<entryList*>::iterator inner_it;
         std::list<std::string>str_list;
         std::string str;
         entryList* e_list;
         entryList* entry_tmp;
         std::string uri;
         int i = 0;

         std::ifstream f_ptr(address.c_str());
         std::ofstream f_write;
         f_write.open("result");
         time_t start, end, start_ret;
         time(&start);
         if(!f_ptr)
         {
            std::cerr << "Error while opening the file!!!!!!" << std::endl;
            return false;
         }

         if(f_ptr.is_open())
            while(std::getline(f_ptr, str))
            {
                 if(str.size() > 0)
                 {
                    str_list.push_back(str);
                    i++;
                 }
            }

         f_ptr.close();


         for(std::list<std::string>::iterator it = str_list.begin(); it != str_list.end(); ++it)
         {
            uri = *it;
            entry_ptr = opt->run(uri);
            m->push_back(entry_ptr);
            ++outer_it;
         }

         time(&end);

         double read_time = double(end - start);
         f_write << "Time taken for file reading including " << i << " lines is " << read_time << std::endl;
         time(&start_ret);

         for(std::list<entryList*>::iterator it = m->begin(); it != m->end(); ++it)
         {
             e_list = *it;
             for(inner_it=e_list->begin(); inner_it != e_list->end(); ++inner_it)
             {
                 entry_tmp = *inner_it;
                 int id = entry_tmp->getId();
                 std::string name = entry_tmp->getName();
             }
         }

         time(&end);
         double reterive_time = double(end - start_ret);
         double total_time = double(end - start);
         f_write << "Time taken for file reteriving including " << i << " lines is " << reterive_time << std::endl;
         f_write << "Time taken for file in total including " << i << " lines is " << total_time << std::endl;
         f_write.close();


         return 0;
}
