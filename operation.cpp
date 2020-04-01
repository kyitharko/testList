#include <fstream>
#include <string>

#include "operation.hpp"
#include "entry_list.hpp"

#include "main_list.hpp"
//#include "peks.hpp"

operation::operation(){}
operation::~operation(){}

entryList* operation::trapdoor_opt(std::string *uri)
{
     entryList* entry_list_outer = new entryList();
     size_t iComponentStart = 0;
     size_t iComponentEnd = 0;
     std::string str;
     std::list<entryList*>::iterator inner_it;
     int i = 0;
     iComponentEnd = uri->find("/", iComponentStart + 1);
     while (iComponentStart < uri->size()) {
           iComponentEnd = uri->find("/", iComponentStart + 1);
           if (iComponentEnd == std::string::npos)
              iComponentEnd = uri->size();
           str = getComponent(uri, iComponentStart + 1, iComponentEnd);
           iComponentStart = iComponentEnd;
           //Trapdoor(Tw, pairing, key.priv, &H1_W1);
           int len = element_length_in_bytes(Tw);
           unsigned char buffer[len];
           //element_to_bytes(&buffer, Tw);
          // std::string encoded_str = base64_encode(buffer, len);
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


entryList* operation::peks(std::string *uri)
{
     iComponentEnd = uri->find("/", iComponentStart + 1);
     while (iComponentStart < uri->size()) {
           iComponentEnd = uri->find("/", iComponentStart + 1);
           if (iComponentEnd == std::string::npos)
              iComponentEnd = uri->size();
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


std::string operation::getComponent(std::string *uri, size_t iComponentStart, size_t iComponentEnd)
{
     return uri->substr(iComponentStart, iComponentEnd - iComponentStart);
}


std::string operation::getEntry(entryList *e_list)
{
     std::list<entryList*>::iterator inner_it;
     for(inner_it=e_list->begin(); inner_it != e_list->end(); ++inner_it)
     {
         entryList* entry_tmp = *inner_it;
     }
}

/*
key_t* operation::key_gen()
{
    /* Apriv = α and Apub = [g, h=g^α]
    //key key;
    fptr = fopen("pairing", "w");
    if (fptr == NULL)
    {
      std::cout << "Error!" << std::endl;
      exit(1);
    }

    //Initialize pairing
    init_pbc_param_pairing(param, pairing);
    Save Parameters
    pbc_param_out_str(fptr, param);
    fclose(fptr);
    Get the order of G1
    P = mpz_get_d(pairing->r);
    //KeyGen
    KeyGen(&key, param, pairing);
}
*/


char operation::h1_w(element_t *H1_W1, char *W1)
{
    /* H1(W) */
    char *hashedW = (char*)malloc(sizeof(char)*SHA512_DIGEST_LENGTH*2+1);
    //sha512(W1, (int)strlen(W1), hashedW);
    element_init_G1(*H1_W1, pairing);
    element_from_hash(*H1_W1, hashedW, (int)strlen(hashedW));
}
