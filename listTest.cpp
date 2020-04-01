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


         FILE *file_ptr;
         pairing_t pairing;
         pbc_param_t param;

         element_t H1_W2;
         std::unique_ptr <peksOpt> p_opt (new peksOpt());

         file_ptr = fopen("pairing", "w");
         if (file_ptr == NULL)
         {
             std::cout << "Error!" << std::endl;
             exit(1);
         }

         std::cout << "finished file open" << std::endl;
         /* Initialize pairing */
         p_opt->init_pbc_param_pairing(param, pairing);
         std::cout << "finished initialize pointer" << std::endl;
         /* Save Parameters */
         pbc_param_out_str(file_ptr, param);
         std::cout << "finished writing to file" << std::endl;
         fclose(file_ptr);
         std::cout << "finished close file" << std::endl;
         /* Get the order of G1 */
         double P = mpz_get_d(pairing->r);
         int nlogP = log2(P);
         std::cout << std::setprecision(9) << std::showpoint << std::fixed;
         std::cout << "finished p " << P << std::endl;
         p_opt->KeyGen(param, pairing);
         std::cout << "finished key gen" << std::endl;

         char A[] = "hi";
         std::string str_test = "Hello";
         char *W2 = &A[0];
         const char *W1 = str_test.c_str();
         int lenW2 = (int)strlen(W2);
         //std::pair<element_t, char*> peks;


         char *hashedW2 = (char*)malloc(sizeof(char)*SHA512_DIGEST_LENGTH*2+1);
	     p_opt->sha512(W2, lenW2, hashedW2);
	     element_init_G1(H1_W2, pairing);
	     element_from_hash(H1_W2, hashedW2, strlen(hashedW2));
         element_printf("H1_W2 %B\n", H1_W2);

	     /* PEKS(key_pub, W2) */
	     p_opt->set_B((char*)malloc(sizeof(char)*(nlogP)));
         p_opt->PEKS(p_opt->getPubg(), p_opt->getPubh(), &pairing, &H1_W2, nlogP);
         element_t* peks;
         char* B;
         peks = p_opt->getPEKS();
         element_printf("A %B\n", *peks);
         B = p_opt->getB();
         p_opt->key_printf();
         element_t* tw;
         element_t H1_W1;
         /* H1(W) */
	     char *hashedW = (char*)malloc(sizeof(char)*SHA512_DIGEST_LENGTH*2+1);
	     p_opt->sha512(W1, (int)strlen(W1), hashedW);
	     element_init_G1(H1_W1, pairing);
	     element_from_hash(H1_W1, hashedW, (int)strlen(hashedW));
	     p_opt->Trapdoor(&pairing, p_opt->getPriKey(), &H1_W1);
	     tw = p_opt->getTw();
	     int match = p_opt->Test(p_opt->getPubg(), p_opt->getPubh(), peks, B, tw, pairing);
	     std::cout << "Match is " << match << std::endl;
	     if(match)
		    printf("Equal\n");
	     else
		    printf("Not equal\n");
         //opt->key_gen();
         for(std::list<std::string>::iterator it = str_list.begin(); it != str_list.end(); ++it)
         {
            uri = *it;
            //entry_ptr = opt->trapdoor_opt(&uri);
            m->push_back(entry_ptr);
            ++outer_it;
         }

         time(&end);

         double read_time = double(end - start);
         f_write << "Time taken for file reading including " << i << " lines is " << read_time << std::endl;
         time(&start_ret);

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
         double reterive_time = double(end - start_ret);
         double total_time = double(end - start);
         f_write << "Time taken for file reteriving including " << i << " lines is " << reterive_time << std::endl;
         f_write << "Time taken for file in total including " << i << " lines is " << total_time << std::endl;
         f_write.close();


         return 0;
}
