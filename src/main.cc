#include <iostream>
#include <fstream>
#include "utils.hh"
#include "output.hh"
#include "trie_node.hh"

int main(int argc, char** argv) {

    TrieNode root = TrieNode("", 0);
    root.insert("test");
    root.insert("te");

    root.insert("toast");

    root.insert("tester");
    root.insert("coucou");

    std::ofstream myfile;
    myfile.open ("trie.dot");
    myfile << "digraph trie {\n";
    root.draw(myfile, 0);
    myfile << "}\n";
    myfile.close();
    return 0;

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

    std::cout << std::endl;
}