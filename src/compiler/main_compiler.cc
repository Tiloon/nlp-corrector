#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "../search/output.hh"
#include "trie_node.hh"

/**
 * \brief Dump the trie in the file in the dot format
 * \param n The root of the trie
 */
static void dump_trie(TrieNode& n) {
    std::ofstream myfile;

    myfile.open("trie.dot");
    myfile << "digraph trie {\n";
    n.draw(myfile, 0);
    myfile << "}\n";
    myfile.close();
}

void write_bin(char *const *argv) {
    std::ifstream in_file;
    std::ofstream out_file;

    try {
        in_file.open(argv[1]);
    }
    catch(...) {
        std::cerr << "File not found:" << argv[1] << std::endl;
    }

    try {
        out_file.open(argv[2]);
    }
    catch(...) {
        std::cerr << "File cannot be written:" << argv[2] << std::endl;
    }

    std::ifstream &in_file1 = in_file;
    std::ofstream &out_file1 = out_file;
    std::cerr << "Building graph" << std::endl;
    TrieNode root = TrieNode("", 0, 0);

    std::string line;
    while(getline(in_file1, line)) {
        std::string word;
        std::string freqs;
        std::istringstream iss(line);
        getline(iss, word, '\t');
        getline(iss, freqs, '\t');
        int freq = stoi(freqs);
        root.insert(word, freq);
    }
    std::cerr << "Writing graph" << std::endl;
    out_file1.write("\0", 1);
    get_current_offset(1);
    root.compute_offset_head();
    root.writeToBinaryFile(out_file1);

    //Uncomment this to dump the trie in a dot format:
//    dump_trie(root);
    out_file1.close();
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " /path/to/word/freq.txt /path/to/output/dict.bin" << std::endl;
        return 139;
    }
    write_bin(argv);
    return 0;
}
