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
#include "utils.hh"
#include "output.hh"
// 00 => 10

static long get_current_offset(long nodeSize) {
    static long  offset = 0;
    offset += nodeSize;
    return offset;
}

void TrieNode::compute_offset_head() {
    for (auto& e : *this->sons_) {
        e.compute_offset();
    }
}

void TrieNode::compute_offset() {
    offset_ = get_current_offset(prefix_.size() + 1 + sizeof (long) * 2) - (prefix_.size() + 1 + sizeof (long) * 2);
    if (this->sons_->empty())
//        return;
        get_current_offset(1);
    else
        for (auto& e : *this->sons_) {
            e.compute_offset();
        }
}

//static std::vector<struct node>* outputVect = new std::vector<struct node>();

char* get_son(char* ptr) {
    std::string name = ptr;
    return ptr + name.size() + 1 + sizeof (long) * 2;
}

char* get_brother(char* start, char* ptr) {
    std::string name = ptr;
    long* next = (long*)(ptr + name.size() + 1 + sizeof (long));
    if (*next == 0)
        return "\0";
    return start + *next;
}

long get_freq(char* ptr) {
    std::string name = ptr;
    long* freq = (long*)(ptr + name.size() + 1);
    return *freq;
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

void* map_file(char *path) {
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
    return ptr;
//    process_file((char*) ptr, (char*) ptr);
}

void TrieNode::writeToBinaryFile(std::ofstream &of) {
    if (this->sons_->empty()) {
        of.write("\0", 1);
        return;
    }
    for (int i = 0; i < this->sons_->size() - 1; ++i) {
        TrieNode& son = (*this->sons_)[i];
        TrieNode& next_son = (*this->sons_)[i + 1];
        of.write((char*)son.prefix_.c_str(), son.prefix_.size() + 1);
        of.write((char*)&son.freq_, sizeof(long));
        of.write((char*)&next_son.offset_, sizeof(long));

        son.writeToBinaryFile(of);
    }
    // Last node in line, no next
    TrieNode& son = (*this->sons_)[this->sons_->size() - 1];
    of.write((char*)son.prefix_.c_str(), son.prefix_.size() + 1);
    of.write((char*)&son.freq_, sizeof(long));
    long tmp = 0;
    of.write((char*)&tmp, sizeof(long));

    son.writeToBinaryFile(of);
}

void TrieNode::insert(std::string word, int freq) {
//    std::cerr << "Insert |" << word << "| to node |" << prefix_ << "|" << std::endl;
    if (!word.length()) {
//        std::cerr << "> Word end |" << prefix_ << "|" << std::endl;
        freq_ = freq;
//        std::cerr << "> Word end |" << prefix_ << "|" <<  freq_ << std::endl;

        this->setWordEnd();
        return;
    }

    for (TrieNode& son : *(this->sons_)) {
        for(int i = 0; i < word.length(); i++) { // FIXME changer le sens de la boucle?
            std::string cutWord = word.substr(0, word.length() - i);  //word "abcd", cutWord "abc"
            if (cutWord.find(son.get_prefix()) == 0) { // ie: cutWord is "abc" and son is "ab"
//                std::cerr << "> Going inside son |" << son.get_prefix() << "| with cutWord |" << cutWord << "|" << std::endl;
                son.insert(word.substr(son.get_prefix().length()), freq);
                return;
            }
            if (son.get_prefix().find(cutWord) == 0) { // ie: son is "abce" and cutWord is "abc"
//                std::cerr << "> Splitting son |" << son.get_prefix() << "| with cutWord |" << cutWord << "|" << std::endl;
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

void TrieNode::draw(std::ofstream& file, int id) {
    for (TrieNode& son : *(this->sons_)) {
        int id_next = id_builder();
        file << "node" << id << " [label=\"" << prefix_ << " (" << freq_ << ")" << "\", style=\"filled\", color=\"" <<
                (isWordEnd_ ? "cadetblue" : "blue") << "\"]; node"
        << id_next << " [label=\"" << son.prefix_  << " (" << son.freq_ << ")" << " \", style=\"filled\", color=\"" <<
                (son.isWordEnd_ ? "cadetblue" : "blue")
        <<"\"]; node" << id << "-> node" << id_next << "\n";
        son.draw(file, id_next);
    }
}


char *BinNode::g_son(char *ptr) {
    return get_son(ptr);
}

char *BinNode::g_brother(char *ptr) {
    return get_brother(this->start, ptr);
}

void resolveRec(std::string& currWord, char* curr, BinNode& myNode) {
    while (*curr != '\0') {
        int freq = get_freq(curr);
        if (freq != 0) {
            int dist = lev_tmp(std::string(currWord).append(curr), myNode.wanted_word);
            if (dist <= myNode.approx)
                myNode.out.insert(OutputElement(std::string(currWord).append(curr), freq, dist));
        }
        else if (currWord.size() > myNode.wanted_word.size() + myNode.approx)
            return;
        char* first_son = get_son(curr);
        resolveRec(std::string(currWord).append(curr), first_son, myNode);
        curr = myNode.g_brother(curr);
    }
}

void resolve(char* ptr, std::string word, int approx) {
    int max = (int) (word.size() + approx);
    auto myOutput = Output();
    BinNode myNode = BinNode(ptr, max, approx, word, myOutput);
    std::string currWord = "";
    resolveRec(currWord, ptr, myNode);
    myOutput.print_json();
}
