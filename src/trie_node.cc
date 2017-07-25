//

#include <algorithm>
#include <iostream>
#include "trie_node.hh"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <err.h>
#include <cstring>
#include "trie_node.hh"
// 00 => 10

static std::vector<struct node>* outputVect = new std::vector<struct node>();

char* get_son(char* start, char* ptr) {
    std::string name = ptr;
    long* next = (long*)(ptr + name.size() + 2 + sizeof (long));
    return start + *next;
}

char* get_brother(char* start, char* ptr) {
    std::string name = ptr;
    return ptr + name.size() + 2 + sizeof (long) * 2;
}
void process_file(char* start, char *ptr) {
    while (true) {
//        struct node *n = (struct node *) ptr;
        std::string name = ptr;
        if (name.empty()) {
            break;
        }
        long* freq = (long*)(ptr + name.size() + 1);
        long* next = (long*)(ptr + name.size() + 1 + sizeof (long));
        std::cerr << name << std::endl;
        std::cerr << *freq << std::endl;
        std::cerr << *next << std::endl;
//        if (*next != 0)
//            process_file(start, start + *next); // iterate on this son
        ptr = ptr + name.size() + 2 + sizeof (long) * 2;
    }
}

void map_file(char *path) {
    int fd;
    struct stat stat;
    void* ptr;

    if ((fd = open(path, O_RDONLY)) < 0)
        err(EXIT_FAILURE, "%s", path);

    if (fstat(fd, &stat) != 0)
        err(EXIT_FAILURE, "%s", path);

    if ((ptr = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
        err(EXIT_FAILURE, "%s", path);

    std::cerr << ptr << std::endl;
    process_file((char*) ptr, (char*) ptr);
}

//
// Created by hugo on 23/07/17.
void TrieNode::writeToBinaryFile(std::ofstream &of) {
    for (int i = 0; i < this->sons_->size(); ++i) {
        TrieNode& son = (*this->sons_)[i];
        long freq = 10; // son.freq_
        outputVect->push_back({son.prefix_, freq, 0l});
//        of.write((char*)son.prefix_.c_str(), son.prefix_.size() + 1);
//        if (son.prefix_.size() + 1 % 2)
//            of.write("\0", 1);
//        of.write((char*)&freq, sizeof(long)); // freq
        long offset = 0l;
        son.writeToBinaryFile(of);
        offset = of.tellp();
        if (i == this->sons_->size() - 1) {
            long tmp = 0;
            of.write((char *) &tmp, sizeof(long)); // next
        }
        else
            of.write((char*)&offset, sizeof(long)); // next
    }
//    long tmp = -1;
//    of.write((char*)&tmp, sizeof(long));
}

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
