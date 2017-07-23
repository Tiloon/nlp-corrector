#include <iostream>
#include "utils.hh"
#include "output.hh"
#include "trie_node.hh"

int main(int argc, char** argv) {
//    if (argc != 3)
//        return 1;
//    std::cout << lev(argv[1], argv[2]) << "\n";
//    print_json("toto", 1, 2);
    auto myOutput = output();
    myOutput.insert(output_element("toto", 13, 1));
    myOutput.insert(output_element("tata", 12, 0));
    myOutput.insert(output_element("toto", 12, 1));
    myOutput.insert(output_element("toto", 12, 0));
    myOutput.print_json();


    TrieNode root = TrieNode("", 1);
    root.insert("test");
    root.insert("coucou");
}