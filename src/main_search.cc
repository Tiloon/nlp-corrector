#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "output.hh"
#include "trie_node.hh"
#include "lev.hh"



void search(char* ptr, std::string word, int dist) {
    std::cerr << "Search: |" << word << "| Dist=" << dist << std::endl;
    resolve(ptr, word, dist);
}


int main(int argc, char** argv) {
    std::cerr << "Load Trie" << std::endl;
    char* ptr = (char*) map_file(argv[1]);
    init_dist();

#if 1
    for (std::string line; std::getline(std::cin, line);) {
        std::string approx;
        std::string precision;
        std::string word;
        std::istringstream iss(line);

        std::getline(iss, approx, ' ');
        std::getline(iss, precision, ' ');
        std::getline(iss, word, ' ');
        std::cerr << approx << " " << precision << " " << word << std::endl;

//        if (approx.compare("approx")) {
//            std::cerr << "Approx expected" << std::endl;
//            continue;
//        }

        search(ptr, word, stoi(precision));
    }
#else
    std::string precision = argv[2];
    std::string word = argv[3];

    search(ptr, word, stoi(precision));
#endif

    return 0;

}