//
#include "trie_node.hh"

#include <algorithm>
#include <iostream>
#include "trie_node.hh"
#include <iostream>
#include <fstream>

#include <cstring>



long get_current_offset(long nodeSize) {
    static long offset = 0;
    offset += nodeSize;
    return offset;
}

void TrieNode::compute_offset_head() {
    for (auto &e : *this->sons_) {
        e.compute_offset();
    }
}

void TrieNode::compute_offset() {
    offset_ = get_current_offset(prefix_.size() + 1 + 1 + sizeof(long) * 2)
              - (prefix_.size() + 1 + 1 + sizeof(long) * 2);
    if (this->sons_->empty())
        get_current_offset(1);
    else
        for (auto &e : *this->sons_) {
            e.compute_offset();
        }
}




void TrieNode::write_string(std::ofstream &of, TrieNode &son) const {
    // write size of string before, it's better than doing a strlen in App

//    if (son.prefix_.length() > 128)
//        std::cerr << "wtf";
    char size = (unsigned char) son.prefix_.size();
    of.write(&size, 1);
    of.write((char *) son.prefix_.c_str(), son.prefix_.size() + 1); // TODO: remove this + 1
}

void TrieNode::writeToBinaryFile(std::ofstream &of) {
    if (this->sons_->empty()) {
        of.write("\0", 1);
        return;
    }
    for (int i = 0; i < this->sons_->size() - 1; ++i) {
        TrieNode &son = (*this->sons_)[i];
        TrieNode &next_son = (*this->sons_)[i + 1];
        write_string(of, son);
        of.write((char *) &son.freq_, sizeof(long));
        of.write((char *) &next_son.offset_, sizeof(long));

        son.writeToBinaryFile(of);
    }
    // Last node in line, no next
    TrieNode &son = (*this->sons_)[this->sons_->size() - 1];
    write_string(of, son);
    of.write((char *) &son.freq_, sizeof(long));
    long tmp = 0;
    of.write((char *) &tmp, sizeof(long));

    son.writeToBinaryFile(of);
}

void TrieNode::insert(std::string word, int freq) {
//    std::cerr << "Insert |" << word << "| to node |" << prefix_ << "|" << std::endl;
    if (!word.length()) {
//        std::cerr << "> Word end |" << prefix_ << "|" << std::endl;
        freq_ = freq;
//        std::cerr << "> Word end |" << prefix_ << "|" <<  freq_ << std::endl;

        this->isWordEnd_ = 1;
        return;
    }

    for (TrieNode &son : *(this->sons_)) {
        for (int i = 0; i < word.length(); i++) { // FIXME changer le sens de la boucle?
            std::string cutWord = word.substr(0, word.length() - i);  //word "abcd", cutWord "abc"
            if (cutWord.find(son.prefix_) == 0) { // ie: cutWord is "abc" and son is "ab"
//                std::cerr << "> Going inside son |" << son.prefix_ << "| with cutWord |" << cutWord << "|" << std::endl;
                son.insert(word.substr(son.prefix_.length()), freq);
                return;
            }
            if (son.prefix_.find(cutWord) == 0) { // ie: son is "abce" and cutWord is "abc"
//                std::cerr << "> Splitting son |" << son.prefix_ << "| with cutWord |" << cutWord << "|" << std::endl;
                TrieNode n = TrieNode(cutWord, 0, 0);
                n.sons_->push_back(son.removeFromPrefix(cutWord.length()));
                this->sons_->erase(std::remove(this->sons_->begin(), this->sons_->end(), son), this->sons_->end());
                n.insert(word.substr(cutWord.length()), freq);
                this->sons_->push_back(n);
//                std::cerr << "> Word end2 |" << n.prefix_ << "|" <<  n.freq_ << std::endl;

                return;
            }
        }
    }
//    std::cerr << "> New node |" << word << "| |" << prefix_ << "|" << std::endl;
    this->sons_->emplace_back(word, 1, freq);
}

static int id_builder() {
    static int id = 0;
    return ++id;
}

void TrieNode::draw(std::ofstream &file, int id) {
    for (TrieNode &son : *(this->sons_)) {
        int id_next = id_builder();
        file << "node" << id << " [label=\"" << prefix_ << " (" << freq_ << ")" << "\", style=\"filled\", color=\"" <<
        (isWordEnd_ ? "cadetblue" : "blue") << "\"]; node"
        << id_next << " [label=\"" << son.prefix_ << " (" << son.freq_ << ")" << " \", style=\"filled\", color=\"" <<
        (son.isWordEnd_ ? "cadetblue" : "blue")
        << "\"]; node" << id << "-> node" << id_next << "\n";
        son.draw(file, id_next);
    }
}






