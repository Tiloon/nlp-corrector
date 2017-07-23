//
// Created by hugo on 23/07/17.
//

#include <algorithm>
#include "trieNode.hh"

void TrieNode::insert(std::string word) {
    if (!word.length()) {
        this->setWordEnd();
        return;
    }

    for (TrieNode son : this->sons_) {
        if (word.find(son.get_prefix()) == 0) { // ie: word is "abc" and son is "ab"
            son.insert(word.substr(son.get_prefix().length()));
            return;
        }
        if (son.get_prefix().find(word) == 0) { // ie: son is "abc" and word is "ab"
            TrieNode n = TrieNode(word, 1);
            n.addSon(son.removeFromPrefix(word.length()));
            this->addSon(n);
            std::remove(sons_.begin(), sons_.end(), son);
            return;
        }
    }
    addSon(TrieNode(word, 1));

}


void TrieNode::addSon(TrieNode n) {
    this->sons_.push_back(n);
}