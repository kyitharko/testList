#ifndef OPERATION_H
#define OPERATION_H
#include <iostream>
#include <string>
#include <list>
#include <fstream>

#include "main_list.hpp"
#include "new_peks.hpp"

class operation{

      public:

           operation();
           ~operation();
           entryList* trapdoor_opt(std::string *uri);
           entryList* peks(std::string *uri);
           std::string getComponent(std::string *uri, size_t iComponentStart, size_t iComponentEnd);
           std::string getEntry(entryList* e_list);
           //key* key_gen();
           char h1_w(element_t *H1_W1, char *W1);

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
          element_t H1_W1;
          pbc_param_t param;
          FILE *fptr;
          pairing_t pairing;

};

#endif
