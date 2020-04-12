#include <fstream>
#include <string>

#include "operation.hpp"
#include "entry_list.hpp"

#include "main_list.hpp"
#include "new_peks.hpp"
#include "encode_decode.hpp"


operation::operation(){}
operation::~operation(){}

entryList* operation::trapdoor_opt(std::string *uri, std::unique_ptr <peksOpt> &p_opt, pbc_param_t *param)
{
     entryList* entry_list_outer = new entryList();
     p_opt->init_pbc_param_pairing(*param, &pairing);
     //size_t iComponentStart = 0;
     //size_t iComponentEnd = 0;
     //std::string str = "";
     //std::list<entryList*>::iterator inner_it;
     //int i = 0;
     std::cout << "start trapdoor creation " << std::endl;
     iComponentEnd = uri->find("/", iComponentStart + 1);
     std::cout << "find first / " << std::endl;
     while (iComponentStart < uri->size()) {
           iComponentEnd = uri->find("/", iComponentStart + 1);
           std::cout << "find second / inside loop" << std::endl;
           if (iComponentEnd == std::string::npos)
              iComponentEnd = uri->size();
           str = getComponent(uri, iComponentStart + 1, iComponentEnd);
           std::cout << "get component" << std::endl;
           iComponentStart = iComponentEnd;
           const char *W1 = str.c_str();
           std::cout << "str.c_str()" << std::endl;
           h1_w(W1, p_opt);
           std::cout << "h1_w inside loop" << std::endl;
           p_opt->Trapdoor(pairing, *p_opt->getPriKey(), H1_W);
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
      std::cout << "finished trapdoor creation " << std::endl;
     return entry_list_outer;
}


std::string operation::peks(std::string *uri, std::unique_ptr <peksOpt> &p_opt, pbc_param_t param)
{
     p_opt->init_pbc_param_pairing(param, &pairing);
     iComponentEnd = uri->find("/", iComponentStart + 1);
     while (iComponentStart < uri->size()) {
           iComponentEnd = uri->find("/", iComponentStart + 1);
           if (iComponentEnd == std::string::npos)
              iComponentEnd = uri->size();
           str = getComponent(uri, iComponentStart + 1, iComponentEnd);
           P = mpz_get_d(pairing->r);
           unsigned int nlogP = log2(P);
           iComponentStart = iComponentEnd;
           const char *W1 = str.c_str();
           h1_w(W1, p_opt);
           p_opt->PEKS(*p_opt->getPubg(), *p_opt->getPubh(), pairing, H1_W, nlogP);
           //Encode PEKS
           peks_str += "/";
           //Encode g
           encode(p_opt->getPEKS());
           peks_str += "/";
           //Encode h
           encode_B(p_opt, nlogP);
      }
     return peks_str;
}

void operation::retriveKey(std::string *uri, std::unique_ptr <peksOpt> &p_opt)
{
     //#TODO: check if this operation works for retrieving pubKey, Trapdoor and Public Parameters
     iComponentEnd = uri->find("/", iComponentStart + 1);
     while (iComponentStart < uri->size()) {
           iComponentEnd = uri->find("/", iComponentStart + 1);
           if (iComponentEnd == std::string::npos)
              iComponentEnd = uri->size();
           str = getComponent(uri, iComponentStart + 1, iComponentEnd);

}
}

entryList* operation::createPeksList(std::string *uri)
{
     iComponentEnd = uri->find("/", iComponentStart + 1);
     while (iComponentStart < uri->size()) {
           iComponentEnd = uri->find("/", iComponentStart + 1);
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

void operation::init_pbc_param_pairing(std::unique_ptr <peksOpt> &p_opt)
{
    p_opt->init_pbc_param_pairing(param, &pairing);
    fptr = fopen("pairing", "w");
    if (fptr == NULL)
    {
      std::cout << "Error!" << std::endl;
      exit(1);
    }
    //Save Parameters
    pbc_param_out_str(fptr, param);
    fclose(fptr);
    //KeyGen
}

void operation::key_gen(std::unique_ptr <peksOpt> &p_opt)
{
    /* Apriv = α and Apub = [g, h=g^α]*/
    //key key;
    p_opt->init_pbc_param_pairing(param, &pairing);

    p_opt->KeyGen(param, pairing);
}


void operation::h1_w(const char *W1, std::unique_ptr <peksOpt> &p_opt)
{
    /* H1(W) */
    element_t tmp;
    char *hashedW = (char*)malloc(sizeof(char)*SHA512_DIGEST_LENGTH*2+1);
    std::cout << "h1_w hashedW" << std::endl;
    p_opt->sha512(W1, (int)strlen(W1), hashedW);
    std::cout << "p_opt->sha512" << std::endl;
    //p_opt->init_pbc_param_pairing(param, *pairing);
    element_init_G1(tmp, pairing);
    std::cout << "element_init_G1" << std::endl;
    element_from_hash(tmp, hashedW, (int)strlen(hashedW));
    std::cout << "element_from_hash" << std::endl;
    free(hashedW); hashedW = NULL;
    std::cout << "free hashedW" << std::endl;
    set_H1_W(&tmp);
    std::cout << "set H1_W" << std::endl;
    element_clear(tmp);
}


void operation::encode(element_t* in_data)
{
    unsigned int len = element_length_in_bytes_compressed(*in_data);
    unsigned char *opt_data = (unsigned char*)malloc(sizeof(unsigned)*len);
    unsigned int opt_len = element_to_bytes_compressed(opt_data, *in_data);
    peks_str = peks_str + unsignedCharToString(opt_data, opt_len);
    free(opt_data); opt_data = NULL;
}

void operation::encode_B(std::unique_ptr <peksOpt> &p_opt, unsigned int nlogP)
{
    peks_str = peks_str + charToString(p_opt->getB(), nlogP);
}

element_t* operation::get_H1_W()
{
    return &H1_W;
}

void operation::set_H1_W(element_t *tmp)
{
    element_set(*tmp, H1_W);
}
