#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>

#include "base64.hpp"
#include "new_peks.hpp"
#include "utils.hpp"
#include "b64.h"
#include <pbc/pbc_test.h>
using namespace std;

void stringToUnsignedChar(std::string in_str, unsigned char* converted)
{
    vector<unsigned char> uchars;
    vector<char> chars{ begin(in_str), end(in_str) };
    transform(begin(in_str), end(in_str), back_inserter(in_str),
     [](unsigned char c) { return reinterpret_cast<unsigned char>(c); });
    for(auto i: uchars)
    {
       converted[i] = uchars[i];
    }
}

std::string unsignedCharToString(unsigned char* in_data, unsigned int len)
{
    std::stringstream ss;
    //std::cout << "in_data is " << endl;
    for(int i = 0; i < sizeof(in_data); ++i)
    {
       ss << std::hex << (int)in_data[i];
       //printf("%x", in_data[i]);
    }
    //std::cout << std::endl;
    std::string out_str = ss.str();

    return out_str;
}

int main()
{
   peksOpt p_opt;
   pairing_t pairing;
   pbc_param_t param;
   int len;

   element_t H1_W2;
   p_opt.init_pbc_param_pairing(param, pairing);
   double P = mpz_get_d(pairing->r);
   int nlogP = log2(P);
   p_opt.KeyGen(param, pairing);

   char A[] = "hi";
   std::string str_test = "hi";
   char *W2 = &A[0];
   const char *W1 = str_test.c_str();
   int lenW2 = (int)strlen(W2);

   //std::cout << "\n before peks generation " << std::endl;

   //std::pair<element_t, char*> peks;
   char *hashedW2 = (char*)malloc(sizeof(char)*SHA512_DIGEST_LENGTH*2+1);
   //std::cout << "\n after hashedW2 " << std::endl;
   p_opt.sha512(W2, lenW2, hashedW2);
   //std::cout << "\n after  p_opt.sha512(W2, lenW2, hashedW2); " << std::endl;
   element_init_G1(H1_W2, pairing);
   //std::cout << "\n after element_init_G1(H1_W2, pairing); " << std::endl;
   element_from_hash(H1_W2, hashedW2, strlen(hashedW2));
   //element_printf("H1_W2 %B\n", H1_W2);


   //char* tmp = malloc(sizeof(char)*(nlogP));
   /* PEKS(key_pub, W2) */
   char *B = (char*)malloc(sizeof(char)*(nlogP));
   p_opt.set_B(B);
   p_opt.PEKS(*p_opt.getPubg(), *p_opt.getPubh(), pairing, H1_W2, nlogP);

   //std::cout << "\n finished peks generation " << std::endl;

   //free(hashedW2); hashedW2 = NULL;

   //get peks and B from object
   //p_opt.key_printf();
   //std::cout << "the original B value is >>>> " << std::endl << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
   //for(int i = 0; i < nlogP; i++)
   //   printf("%c", B[i]);
   //printf("\n");
   //std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";


   element_t* tw;
   element_t H1_W1;
   /* H1(W) */
   char *hashedW = (char*)malloc(sizeof(char)*SHA512_DIGEST_LENGTH*2+1);
   p_opt.sha512(W1, (int)strlen(W1), hashedW);
   element_init_G1(H1_W1, pairing);
   element_from_hash(H1_W1, hashedW, (int)strlen(hashedW));
   p_opt.Trapdoor(pairing, *p_opt.getPriKey(), H1_W1);
   tw = p_opt.getTw();

   //free(hashedW); hashedW = NULL;
   //pbc_param_clear(param);


   int match = p_opt.Test(*p_opt.getPubg(), *p_opt.getPubh(), *p_opt.getPEKS(), p_opt.getB(), *tw, pairing);
   //if(match)
   //  printf("Equal\n");
   //else
   //  printf("Not equal\n");

   FILE *fptr;
   fptr = fopen("g", "w");
   if (fptr == NULL)
    {
      std::cout << "Error!" << std::endl;
      exit(1);
    }

   element_out_str(fptr, 32, *p_opt.getPubg());
   //encode and decode pub g
   len = element_length_in_bytes_compressed(*p_opt.getPubg());
   unsigned char *g_data = (unsigned char*)malloc(sizeof(char)*len);
   unsigned int g_len = element_to_bytes_compressed(g_data, *p_opt.getPubg());
   std::string g_string = unsignedCharToString(g_data, len);
//   std::cout << std::endl << "g_string " << g_string << std::endl;
   unsigned char* g_converted = (unsigned char*)malloc(g_len);
   stringToUnsignedChar(g_string, g_converted);
   char* g_test = (char*)malloc(sizeof(char)*len);

   element_t new_g;
   element_init_G1(new_g, pairing);
   element_from_bytes_compressed(new_g, g_converted);
  // std::cout << std::endl << "expect result " << element_cmp(new_g, *p_opt.getPubg()) << std::endl;
   //EXPECT(!element_cmp(new_g, *p_opt.getPubg()));
   //encode and decode pub h
   len = element_length_in_bytes_compressed(*p_opt.getPubh());
   unsigned char *h_data = (unsigned char*)malloc(sizeof(char)*len);
   unsigned int h_len = element_to_bytes_compressed(h_data, *p_opt.getPubh());
   std::string h_string = unsignedCharToString(h_data, len);
   //std::cout << std::endl << "h_string " << h_string << std::endl;

   unsigned char* h_converted = (unsigned char*)malloc(h_len);
   stringToUnsignedChar(h_string, h_converted);

   element_t new_h;
   element_init_G1(new_h, pairing);
   element_from_bytes_compressed(new_h, h_converted);

   //if(!element_cmp(new_g, *p_opt.getPubg()))
   //  cout << "success" << endl;

   p_opt.setPubKey(new_g, new_h);
   match = p_opt.Test(new_g, new_g, *p_opt.getPEKS(), p_opt.getB(), *tw, pairing);
   if(match)
     printf("Equal after key exchange\n");
   else
     printf("Not equal after key exchange\n");

   //p_opt.key_printf();
   //encode and decode peks
   len = element_length_in_bytes_compressed(*p_opt.getPEKS());
   unsigned char *peks_data = (unsigned char*)malloc(sizeof(unsigned)*len);
   unsigned int peks_len = element_to_bytes_compressed(peks_data, *p_opt.getPEKS());
   std::string peks_string = unsignedCharToString(peks_data, len);
   //cout << endl << "peks string " << peks_string << endl;
   unsigned char* peks_converted = (unsigned char*)malloc(peks_len);
   stringToUnsignedChar(peks_string, peks_converted);

   element_t new_peks;
   element_init_G1(new_peks, pairing);
   element_from_bytes_compressed(new_peks, peks_data);
   //if(!element_cmp(new_peks, *p_opt.getPEKS()))
    // cout << "peks success" << endl;
   //std::cout << std::endl << "expect result " << element_cmp(new_peks, *p_opt.getPEKS()) << std::endl;
   //EXPECT(!element_cmp(new_peks, *p_opt.getPEKS()));
   //std::cout << std::endl << "element_item_count " << element_item_count(*p_opt.getPEKS());
   //std::cout << std::endl << "element_item_count " << element_item_count(new_peks) << std::endl;
   p_opt.set_peks(new_peks);
   //p_opt.peks_printf();
   match = p_opt.Test(new_g, new_h, new_peks, p_opt.getB(), *tw, pairing);
   if(match)
     printf("Equal after peks exchange\n");
   else
     printf("Not equal after peks exchange\n");

   element_clear(new_g);
   element_clear(new_h);
   element_clear(new_peks);
   free(g_data); g_data = NULL;
   free(g_converted); g_converted = NULL;
   free(h_data); h_data = NULL;
   free(h_converted); h_converted = NULL;
   free(peks_data); peks_data = NULL;
   free(peks_converted); peks_converted = NULL;
   free(B); B = NULL;

   return 0;

}
