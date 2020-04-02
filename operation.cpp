#include <fstream>
#include <string>

#include "operation.hpp"
#include "entry_list.hpp"

#include "main_list.hpp"
#include "new_peks.hpp"
#include "base64.hpp"


operation::operation(){}
operation::~operation(){}

entryList* operation::trapdoor_opt(std::string *uri, std::unique_ptr <peksOpt> &p_opt)
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
           const char *W1 = str.c_str();
           h1_w(W1, p_opt);
           p_opt->Trapdoor(&pairing, p_opt->getPriKey(), &H1_W);
           //int len = element_length_in_bytes(Tw);
           //unsigned char buffer[len];
           //element_to_bytes(&buffer, Tw);
          // std::string encoded_str = base64_encode(buffer, len);
           entryList *e_list;
           e_list = new entryList();
           e_list->setEntryList(i, Tw);

           i++;
           entry_list_outer->push_back(e_list);
           inner_it = e_list->begin();
           ++inner_it;
           //delete e_list;
      }
     return entry_list_outer;
}


std::string operation::peks(std::string *uri, std::unique_ptr <peksOpt> &p_opt)
{
     iComponentEnd = uri->find("/", iComponentStart + 1);
     while (iComponentStart < uri->size()) {
           iComponentEnd = uri->find("/", iComponentStart + 1);
           if (iComponentEnd == std::string::npos)
              iComponentEnd = uri->size();
           str = getComponent(uri, iComponentStart + 1, iComponentEnd);
           P = mpz_get_d(pairing->r);
           int nlogP = log2(P);
           iComponentStart = iComponentEnd;
           const char *W1 = str.c_str();
           h1_w(W1, p_opt);
           p_opt->set_B((char*)malloc(sizeof(char)*(nlogP)));
           p_opt->PEKS(p_opt->getPubg(), p_opt->getPubh(), &pairing, &H1_W, nlogP);
           //Encode PEKS
           peks_str += "/g/";
           // Encode g
           len = element_length_in_bytes(*p_opt->getPubg());
           unsigned char g_data [len];
           element_to_bytes(g_data, *p_opt->getPubg());
           peks_str += base64_encode(g_data, len);
           // Encode h
           peks_str += "/h/";
           len = element_length_in_bytes(*p_opt->getPubh());
           unsigned char h_data [len];
           element_to_bytes(h_data, *p_opt->getPubh());
           peks_str += base64_encode(h_data, len);
      }
     return peks_str;
}

entryList* operation::createPeksList(std::string *uri)
{
     iComponentEnd = uri->find("/g/", iComponentStart + 1);
     while (iComponentStart < uri->size()) {
           iComponentEnd = uri->find("/h/", iComponentStart + 1);
           if (iComponentEnd == std::string::npos)
              iComponentEnd = uri->size();
           str = getComponent(uri, iComponentStart + 1, iComponentEnd);

}
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



void operation::key_gen(std::unique_ptr <peksOpt> &p_opt)
{
    /* Apriv = α and Apub = [g, h=g^α]*/
    //key key;
    fptr = fopen("pairing", "w");
    if (fptr == NULL)
    {
      std::cout << "Error!" << std::endl;
      exit(1);
    }

    //Initialize pairing
    p_opt->init_pbc_param_pairing(param, pairing);
    //Save Parameters
    pbc_param_out_str(fptr, param);
    fclose(fptr);
    //Get the order of G1
    P = mpz_get_d(pairing->r);
    //KeyGen
    p_opt->KeyGen(param, pairing);
}


void operation::h1_w(const char *W1, std::unique_ptr <peksOpt> &p_opt)
{
    /* H1(W) */
    char *hashedW = (char*)malloc(sizeof(char)*SHA512_DIGEST_LENGTH*2+1);
    p_opt->sha512(W1, (int)strlen(W1), hashedW);
    element_init_G1(H1_W, pairing);
    element_from_hash(H1_W, hashedW, (int)strlen(hashedW));
}
