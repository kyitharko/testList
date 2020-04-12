#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <iomanip>

#include "entry_list.hpp"
#include "main_list.hpp"
#include "operation.hpp"
#include "new_peks.hpp"


int main(int argc, char **argv){
	if (argc != 2) {
                std::cout << "Usage: %s is e.g., path to file\n" << argv[0] << std::endl;
                return 1;
         }

         mainList *m;
         entryList* entry_ptr;
         m = new mainList();
         operation *opt;
         std::unique_ptr <peksOpt> p_opt (new peksOpt());
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
         //to read input file
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

         //to write param

         /*FILE *file_ptr;
         file_ptr = fopen("pairing", "w");
         if (file_ptr == NULL)
         {
             std::cout << "Error!" << std::endl;
             exit(1);
         }

         std::cout << "finished file open" << std::endl;
         /* Initialize pairing */
         //p_opt->init_pbc_param_pairing(param, &pairing);
         //std::cout << "finished initialize pointer" << std::endl;

         /* Save Parameters */
         /*
         pbc_param_out_str(file_ptr, param);
         std::cout << "finished writing to file" << std::endl;
         fclose(file_ptr);
         std::cout << "finished close file" << std::endl;

         */
         //KeyGen
         /* Get the order of G1 */

         opt->init_pbc_param_pairing(p_opt);
         opt->key_gen(p_opt);
         std::cout << "finished key gen" << std::endl;

        /*
         //to create Trapdoor list [[Tw11,Tw12,....], [Tw21,Tw22,....], [Tw31,Tw32,....], .....]
         for(std::list<std::string>::iterator it = str_list.begin(); it != str_list.end(); ++it)
         {
            uri = *it;
            std::cout << "pop from str_list " << std::endl;
            entry_ptr = opt->trapdoor_opt(&uri, p_opt, &param);
            std::cout << "trapdoor created and pushed to list " << std::endl;
            m->push_back(entry_ptr);
            std::cout << "created outer list" << std::endl;
            ++outer_it;
            std::cout << "str_list is " << uri << std::endl;
         }

         time(&end);

         double read_time = double(end - start);
         f_write << "Time taken for file reading including " << i << " lines is " << read_time << std::endl;
         time(&start_ret);

         //to retrieve trapdoors
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

         */

	     double reterive_time = double(end - start_ret);
         double total_time = double(end - start);
         f_write << "Time taken for file reteriving including " << i << " lines is " << reterive_time << std::endl;
         f_write << "Time taken for file in total including " << i << " lines is " << total_time << std::endl;
         f_write.close();


         return 0;
}
