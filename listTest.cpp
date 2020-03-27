#include <iostream>
#include <string>
#include <list>

#include "entry_list.hpp"
#include "main_list.hpp"
#include "operation.hpp"


int main(int argc, char **argv){
	if (argc != 2) {
                std::cout << "Usage: %s is e.g., /a/b/c\n" << argv[0] << std::endl;
                return 1;
         }

         mainList *m;
         m = new mainList();
         operation *opt;
         std::string uri = *(++argv);
         std::cout << "input string is: " << uri << std::endl;
         std::list<int>::iterator outer_it;
         outer_it = m.begin();
         opt->run(m, &uri, outer_it);
         ++outer_it;

}
