//
// Created by hugo on 23/07/17.
//

#include <algorithm>
#include <iostream>
#include "trie_node.hh"
#include <fstream>

void TrieNode::insert(std::string word, int freq) {
//    std::cerr << "Insert |" << word << "| to node |" << prefix_ << "|" << std::endl;
    if (!word.length()) {
//        std::cerr << "> Word end |" << word << "|" << std::endl;
        this->setWordEnd();
        return;
    }

    for (TrieNode& son : *(this->sons_)) {
        for(int i = 0; i < word.length(); i++) { // FIXME changer le sens de la boucle ?
            std::string cutWord = word.substr(0, word.length() - i);  //word "abcd", cutWord "abc"
            if (cutWord.find(son.get_prefix()) == 0) { // ie: cutWord is "abc" and son is "ab"
//                std::cerr << "> Going inside son |" << son.get_prefix() << "| with cutWord |" << cutWord << "|" << std::endl;
                son.insert(word.substr(son.get_prefix().length()), freq);
                return;
            }
            if (son.get_prefix().find(cutWord) == 0) { // ie: son is "abce" and cutWord is "abc"
//                std::cerr << ">>>> Splitting son |" << son.get_prefix() << "| with cutWord |" << cutWord << "|" << std::endl;
                TrieNode n = TrieNode(cutWord, 0, freq);
                n.sons_->push_back(son.removeFromPrefix(cutWord.length()));
                this->sons_->erase(std::remove(this->sons_->begin(), this->sons_->end(), son), this->sons_->end());
                this->sons_->push_back(n);
                n.insert(word.substr(cutWord.length()), freq);
                return;
            }
        }
//        if (cutWord.find(son.get_prefix()) == 0) { // ie: word is "abc" and son is "ab"
//            std::cerr << "> Going inside son " << son.get_prefix() << "with cutWord " << cutWord << std::endl;
//            son.insert(word.substr(son.get_prefix().length()), freq);
//            return;
//        }
//        if (son.get_prefix().find(cutWord) == 0) { // ie: son is "abc" and word is "ab"
//            std::cerr << "> Splitting son" << son.get_prefix() << "with cutWord " << cutWord  << std::endl;
//            TrieNode n = TrieNode(word, 1, freq);
//            n.sons_.push_back(son.removeFromPrefix(word.length()));
//            this->sons_.erase(std::remove(this->sons_.begin(), this->sons_.end(), son), this->sons_.end());
//            this->sons_.push_back(n);
//            return;
//        }
    }
//    std::cerr << "> New node |" << word << "| |" << prefix_ << "| sons size:" << sons_->size() << std::endl;
    this->sons_->emplace_back(word, 1, freq);
//    std::cerr << "> New node |" << word << "| |" << prefix_ << "| sons size:" << sons_->size() << std::endl;


}

static int id_builder() {
    static int id = 0;
    return ++id;
}

void TrieNode::draw(std::ofstream& file, int id) {
    for (TrieNode& son : *(this->sons_)) {
        int id_next = id_builder();
        std::cerr << "Draw " << son.prefix_  << " " << son.sons_->size() << std::endl;
        file << "node" << id << " [label=\"" << prefix_ << "\", style=\"filled\", color=\"" <<
                (isWordEnd_ ? "cadetblue" : "blue") << "\"]; node"
        << id_next << " [label=\"" << son.prefix_  << " \", style=\"filled\", color=\"" <<
                (son.isWordEnd_ ? "cadetblue" : "blue")
        <<"\"]; node" << id << "-> node" << id_next << "\n";
        son.draw(file, id_next);
    }
}
