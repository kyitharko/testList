#include <fstream>

#include "operation.hpp"
#include "entry_list.hpp"

#include "main_list.hpp"
#include "peks.hpp"

operation::operation(){}
operation::~operation(){}

entryList* operation::trapdoor(std::string &uri)
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


entryList* operation::peks(std::string &uri)
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


key* operation::key_gen()
{
    /* Order of group G1 and G2 */
        double P;

        /* Apriv = α and Apub = [g, h=g^α] */
        key key;

        /* Trapdoor */
        element_t Tw;

        /* H1(W) */
        element_t H1_W1;

        /* PBC data types */
        pbc_param_t param;
        FILE *fptr;
        fptr = fopen("pairing", "w");
        if (fptr == NULL)
        {
          std::cout << "Error!" << std::endl;
          exit(1);
        }
        pairing_t pairing;

        /* Initialize pairing */
        init_pbc_param_pairing(param, pairing);
        pbc_param_out_str(fptr, param);
        fclose(fptr);
        std::ifstream in("pairing");
        if (fptr == NULL)
        {
          std::cout << "Error!" << std::endl;
          exit(1);
        }
        std::string line, text;
        while(std::getline(in, line))
        {
          text += line + "\n";
        }
        const char* param_str = text.c_str();
        pbc_param_t param1;
        pbc_param_init_set_str(param1, param_str);
        /* Get the order of G1 */
        P = mpz_get_d(pairing->r);
        /* KeyGen */
        KeyGen(&key, param, pairing);
}
