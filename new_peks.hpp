#ifndef PEKS_NEW_HPP
#define PEKS_NEW_HPP

#include <gmp.h>
#include <pbc/pbc.h>
#include <openssl/sha.h>
#include <fstream>
#include <math.h>
//#include <stdlib.h>
//#include <assert.h>
//#include <stdio.h>
#include <string.h>

class peksOpt
{
    public:
        peksOpt();
        ~peksOpt();
        void sha512(const char *word, int word_size, char hashed_word[SHA512_DIGEST_LENGTH*2+1]);

        void get_n_bits(char* src, char* out, int bitswanted);

        bool is_empty(std::ifstream& pFile);


    private:
         element_t g;
         element_t h;
         element_t priv;
         element_t peks;
         element_t Tw;
         char* B;


    public:
        void key_printf();

        void peks_printf();

        void init_pbc_param_pairing(pbc_param_t param, pairing_t pairing);

        void KeyGen(pbc_param_t param, pairing_t pairing);

        std::pair<element_t*, char*>* PEKS(element_t *g, element_t *h, pairing_t *pairing, element_t *H1_W, int bitswanted);

        element_t* Trapdoor(pairing_t *pairing, element_t *alpha, element_t *H1_W);

        void set_B(char* addr_B);

        char *getB();

        int Test(element_t* g, element_t* h, std::pair<element_t*, char*>* peks, element_t* Tw, pairing_t pairing);

        int peks_scheme(char* W1, char *W2);

        element_t* getPubg();

        element_t* getPubh();

        element_t* getPriKey();

};

#endif // PEKS_NEW_HPP
