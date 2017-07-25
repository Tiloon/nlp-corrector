#include <iostream>
#include <fstream>
#include <sstream>
#include "utils.hh"
#include "output.hh"
#include "trie_node.hh"

static void dump_trie(TrieNode& n) {
    std::ofstream myfile;

    myfile.open("trie.dot");
    myfile << "digraph trie {\n";
    n.draw(myfile, 0);
    myfile << "}\n";
    myfile.close();
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " /path/to/word/freq.txt /path/to/output/dict.bin" << std::endl;
        return 139;
    }
    std::ifstream inFile;
    std::ofstream outFile;

    try {
        inFile.open(argv[1]);
    }
    catch(...) {
        std::cerr << "File not found:" << argv[1] << std::endl;
    }

    try {
        outFile.open(argv[2]);
    }
    catch(...) {
        std::cerr << "File cannot be written:" << argv[2] << std::endl;
    }

    TrieNode root = TrieNode("", 0, 0);

    std::string line;
    while(std::getline(inFile, line)) {
        std::string word;
        std::string freqs;
        std::istringstream iss(line);
        std::getline(iss, word, '\t');
        std::getline(iss, freqs, '\t');
        int freq = std::stoi(freqs);
        root.insert(word, freq);
    }
//    dump_trie(root);
    return 0;

/*int main(int argc, char** argv) {

    TrieNode root = TrieNode("", 1);
    root.insert("test");
    root.insert("tester");
    root.insert("coucou");

    char* file_name = (char *) "graph.bin";
    std::ofstream myfile;
    myfile.open(file_name, std::ios::out | std::ios::binary);
    root.writeToBinaryFile(myfile);
//    myfile << "digraph trie {\n";
//    root.draw(myfile, 0);
//    myfile << "}\n";
    myfile.close();
    std::cerr << "Starting processing of file" << std::endl;
    map_file(file_name);*/

}

static TrieNode& test_trie() {
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
    auto myOutput = output();
    myOutput.insert(output_element("toto", 13, 1));
    myOutput.insert(output_element("tata", 12, 0));
    myOutput.insert(output_element("toto", 12, 1));
    myOutput.insert(output_element("toto", 12, 0));
    myOutput.print_json();

    std::cout << std::endl;
}