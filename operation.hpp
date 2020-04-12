#ifndef OPERATION_H
#define OPERATION_H
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <memory>

#include "main_list.hpp"
#include "new_peks.hpp"

class peksOpt;

class operation{

      public:

           operation();
           ~operation();


      private:
          entryList* entry_list_outer = new entryList();
          size_t iComponentStart = 0;
          size_t iComponentEnd = 0;
          std::list<entryList*>::iterator inner_it;
          int i = 0;
          /* Order of group G1 and G2 */
          double P;
          pairing_t pairing;
          pbc_param_t param;
          /* Trapdoor */
          element_t Tw;

          /* H1(W) */
          element_t H1_W;
          FILE *fptr;
          std::string peks_str = "";
          std::string str = "";
          int len;

      public:
           entryList* trapdoor_opt(std::string *uri, std::unique_ptr <peksOpt> &p_opt, pbc_param_t *param);
           std::string peks(std::string *uri, std::unique_ptr <peksOpt> &p_opt, pbc_param_t param);
           std::string getComponent(std::string *uri, size_t iComponentStart, size_t iComponentEnd);
           std::string getEntry(entryList* e_list);
           void key_gen(std::unique_ptr <peksOpt> &p_opt);
           void h1_w(const char *W1, std::unique_ptr <peksOpt> &p_opt);
           void retriveKey(std::string *uri, std::unique_ptr <peksOpt> &p_opt);
           entryList* createPeksList(std::string *uri);
           void encode(element_t* in_data);
           void encode_B(std::unique_ptr <peksOpt> &p_opt, unsigned int nlogP);
           element_t* get_H1_W();
           void set_H1_W(element_t *tmp);
           void init_pbc_param_pairing(std::unique_ptr <peksOpt> &p_opt);

};

#endif
