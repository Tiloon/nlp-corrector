#include <iostream>
#include "trieNode.hh"

using namespace std;

int main() {
    TrieNode root = TrieNode("", 1);
    root.insert("test");
    root.insert("coucou");
    cout << "Hello, World!" << endl;
    return 0;
}