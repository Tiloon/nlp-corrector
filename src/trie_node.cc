//
// Created by hugo on 23/07/17.
//

#include <algorithm>
#include <iostream>
#include "trie_node.hh"
#include <fstream>

void TrieNode::insert(std::string word, int freq) {
    std::cerr << "Insert: " << word << std::endl;
    if (!word.length()) {
        std::cerr << "> Word end!" << std::endl;

        this->setWordEnd();
        return;
    }

    for (TrieNode& son : this->sons_) {
        if (word.find(son.get_prefix()) == 0) { // ie: word is "abc" and son is "ab"
            std::cerr << "> Going inside son " << son.get_prefix() << std::endl;
            son.insert(word.substr(son.get_prefix().length()), freq);
            return;
        }
        if (son.get_prefix().find(word) == 0) { // ie: son is "abc" and word is "ab"
            std::cerr << "> Splitting son" << son.get_prefix() << std::endl;
            TrieNode n = TrieNode(word, 1, freq);
            n.sons_.push_back(son.removeFromPrefix(word.length()));
            this->sons_.erase(std::remove(this->sons_.begin(), this->sons_.end(), son), this->sons_.end());
            this->sons_.push_back(n);
            return;
        }
    }
    std::cerr << "> New node!" << std::endl;

    this->sons_.emplace_back(word, 1, freq);

}

static int id_builder() {
    static int id = 0;
    return ++id;
}

void TrieNode::draw(std::ofstream& file, int id) {
    for (TrieNode& son : this->sons_) {
        int id_next = id_builder();
        file << "node" << id << " [label=\"" << prefix_ << "\", style=\"filled\", color=\"" <<
                (isWordEnd_ ? "cadetblue" : "blue") << "\"]; node"
        << id_next << " [label=\"" << son.prefix_  << " \", style=\"filled\", color=\"" <<
                (son.isWordEnd_ ? "cadetblue" : "blue")
        <<"\"]; node" << id << "-> node" << id_next << "\n";
        son.draw(file, id_next);
    }
}
