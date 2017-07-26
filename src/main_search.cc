#include <iostream>
#include <fstream>
#include <sstream>
#include "output.hh"
#include "trie_node.hh"
#include "utils.hh"


void print_spaces(int depth) {
    for (int i = 0; i < depth * 2; ++i)
        std::cerr << " ";
}

void print_all(char *ptr, char *curr, int depth) {
    if (*curr != '\0') {
        print_spaces(depth);
        std::cerr << curr << " " << get_freq(curr) << std::endl;
        print_all(ptr, get_son(curr), depth + 1);
        print_all(ptr, get_brother(ptr, curr), depth);
//        print_spaces(depth);
//        print_spaces(depth);
//        std::cerr << "Visiting son" << std::endl;
//        std::cerr << "Finished visiting son" << std::endl;
//        print_spaces(depth);
//        std::cerr << "Visiting brother" << std::endl;
//        print_spaces(depth);
//        std::cerr << "Finished visiting brother" << std::endl;
    }
}


void search(char* ptr, std::string word, int dist) {
    std::cerr << "Search: |" << word << "| Dist=" << dist << std::endl;
    resolve(ptr, word, dist);
}


int main(int argc, char** argv) {
    std::cerr << "Load Trie" << std::endl;
    char* ptr = (char*) map_file(argv[1]);

    for (std::string line; std::getline(std::cin, line);) {
        std::string approx;
        std::string precision;
        std::string word;
        std::istringstream iss(line);

        std::getline(iss, approx, ' ');
        std::getline(iss, precision, ' ');
        std::getline(iss, word, ' ');
        std::cerr << approx << " " << precision << " " << word << std::endl;

        if (approx.compare("approx")) {
            std::cerr << "Approx expected" << std::endl;
            continue;
        }

        search(ptr, word, stoi(precision));

    }

//    search(ptr, "test", 1);
    return 0;

}