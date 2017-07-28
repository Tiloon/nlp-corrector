#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "output.hh"
#include "trie_node.hh"
#include "lev.hh"

static void dump_trie(TrieNode& n) {
    std::ofstream myfile;

    myfile.open("trie.dot");
    myfile << "digraph trie {\n";
    n.draw(myfile, 0);
    myfile << "}\n";
    myfile.close();
}

void print_spaces(int depth) {
    for (int i = 0; i < depth * 2; ++i)
        std::cerr << " ";
}

/*void print_all(char *ptr, char *curr, int depth) {
    if (*curr != '\0') {
        print_spaces(depth);
        std::cerr << curr << " " << get_freq(curr, strlen(curr)) << std::endl;
        print_all(ptr, get_son(curr, strlen(curr)), depth + 1);
        print_all(ptr, get_brother(ptr, curr, strlen(curr)), depth);
    }
}*/

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
//    root = (*root.sons_)[0];
    std::cerr << "Writing graph" << std::endl;
    out_file1.write("\0", 1);
    get_current_offset(1);
    root.compute_offset_head();
    root.writeToBinaryFile(out_file1);
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

static TrieNode test_trie() {
    TrieNode root = TrieNode("", 0, 0);
    root.insert("test", 1);
    root.insert("tech", 1);

    root.insert("toast", 1);

    root.insert("tester", 1);
    root.insert("coucou", 1);
    root.insert("tom", 1);
    root.insert("te", 1);

    return root;

}

static void test_output() {
    auto myOutput = Output();
    myOutput.insert(OutputElement("toto", 13, 1));
    myOutput.insert(OutputElement("tata", 12, 0));
    myOutput.insert(OutputElement("toto", 12, 1));
    myOutput.insert(OutputElement("toto", 12, 0));
    myOutput.print_json();

    std::cout << std::endl;
}