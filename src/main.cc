#include <iostream>
#include <fstream>
#include <sstream>
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

void print_spaces(int depth) {
    for (int i = 0; i < depth * 4; ++i)
        std::cerr << " ";
}

void print_all(char *ptr, char *curr, int depth) {
    if (*curr != '\0') {
        print_spaces(depth);
        std::cerr << curr << " " << get_freq(curr) << std::endl;
        print_all(ptr, get_son(curr), depth + 1);
        print_all(ptr, get_brother(ptr, curr), depth + 1);
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

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " /path/to/word/freq.txt /path/to/output/dict.bin" << std::endl;
        return 139;
    }
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

    TrieNode root = TrieNode("", 0, 0);

    std::string line;
    while(std::getline(in_file, line)) {
        std::string word;
        std::string freqs;
        std::istringstream iss(line);
        std::getline(iss, word, '\t');
        std::getline(iss, freqs, '\t');
        int freq = std::stoi(freqs);
        root.insert(word, freq);
    }
//    root = (*root.sons_)[0];
    (*root.sons_)[0].computeOffset();
    root.writeToBinaryFile(out_file);
    dump_trie(root);
    out_file.close();
    char* ptr = (char*) map_file(argv[2]);
    char* curr = ptr;

    print_all(ptr, curr, 0);
//    char* son = get_son(ptr);
//    char* ptr_brother = get_brother(ptr, ptr);
//    char* son_brother = get_brother(ptr, son);
//    std::cerr << ptr << " " << get_freq(ptr) << std::endl;
//    std::cerr << son << " " << get_freq(son) << std::endl;
//    std::cerr << son_brother << " " << get_freq(son_brother) << std::endl;
//    if (ptr_brother != NULL)
//        std::cerr << ptr_brother << " " << get_freq(ptr_brother) << std::endl;
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