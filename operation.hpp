#ifndef OPERATION_H
#define OPERATION_H
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <memory>

#include "main_list.hpp"
#include "new_peks.hpp"

class operation{

      public:

           operation();
           ~operation();
           entryList* trapdoor_opt(std::string *uri, std::unique_ptr <peksOpt> &p_opt);
           std::string peks(std::string *uri, std::unique_ptr <peksOpt> &p_opt);
           std::string getComponent(std::string *uri, size_t iComponentStart, size_t iComponentEnd);
           std::string getEntry(entryList* e_list);
           void key_gen(std::unique_ptr <peksOpt> &p_opt);
           void h1_w(const char *W1, std::unique_ptr <peksOpt> &p_opt);
           entryList* createPeksList(std::string *uri);

     private:
          entryList* entry_list_outer = new entryList();
          size_t iComponentStart = 0;
          size_t iComponentEnd = 0;
          std::string str;
          std::list<entryList*>::iterator inner_it;
          int i = 0;
          /* Order of group G1 and G2 */
          double P;

          /* Apriv = α and Apub = [g, h=g^α] */
          //key key;

          /* Trapdoor */
          element_t Tw;

          /* H1(W) */
          element_t H1_W;
          pbc_param_t param;
          FILE *fptr;
          pairing_t pairing;
          std::string peks_str;
          int len;


};

#endif
