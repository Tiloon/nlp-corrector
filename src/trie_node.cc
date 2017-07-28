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

long get_current_offset(long nodeSize) {
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
    offset_ = get_current_offset(prefix_.size() + 1 + 1 + sizeof (long) * 2)
              - (prefix_.size() + 1 + 1 + sizeof (long) * 2);
    if (this->sons_->empty())
        get_current_offset(1);
    else
        for (auto& e : *this->sons_) {
            e.compute_offset();
        }
}

inline const char *get_son(const char *ptr, size_t len) {
    return ptr + len + 1 + sizeof (long) * 2;
}

inline const char *get_brother(const char *start, const char *ptr, size_t len) {
    return start + *(long*)(ptr + len + 1 + sizeof (long));
}

long get_freq(const char* ptr, size_t len) {
    return *(long*)(ptr + len + 1);
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

//    std::cerr << ptr << std::endl;
    return ptr;
}

void TrieNode::write_string(std::ofstream &of, TrieNode &son) const {
    // write size of string before, it's better than doing a strlen in App

//    if (son.prefix_.length() > 128)
//        std::cerr << "wtf";
    char size = (unsigned char) son.prefix_.size();
    of.write(&size, 1);
    of.write((char*)son.prefix_.c_str(), son.prefix_.size() + 1); // TODO: remove this + 1
}

void TrieNode::writeToBinaryFile(std::ofstream &of) {
    if (this->sons_->empty()) {
        of.write("\0", 1);
        return;
    }
    for (int i = 0; i < this->sons_->size() - 1; ++i) {
        TrieNode& son = (*this->sons_)[i];
        TrieNode& next_son = (*this->sons_)[i + 1];
        write_string(of, son);
        of.write((char*)&son.freq_, sizeof(long));
        of.write((char*)&next_son.offset_, sizeof(long));

        son.writeToBinaryFile(of);
    }
    // Last node in line, no next
    TrieNode& son = (*this->sons_)[this->sons_->size() - 1];
    write_string(of, son);
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


inline const char *BinNode::g_son(const char *ptr, size_t len) {
    return get_son(ptr, len);
}

inline const char *BinNode::g_brother(const char *ptr, size_t len) {
    return get_brother(this->start, ptr, len);
}

inline const char *BinNode::go_to(size_t len) {
    return start + len;
}


void resolveRec(MyString currWord, const char* curr, BinNode& myNode) {
    while (true) {
        size_t len = (size_t) (unsigned char) *curr; // (int) (unsigned char) (curr) = 133
        curr = curr + 1;
        currWord.append(curr, len);
        MyString new_word = MyString(currWord.index + len, currWord.computed_index);
        if (new_word.index <= myNode.wanted_word.length() + myNode.approx) {
            if (new_word.index >= myNode.wanted_word.length() - myNode.approx) { // call lev earlier and kill tree if too bad
                long freq = get_freq(curr, len);
                if (freq != 0) {
                    int dist = lev_max(new_word, new_word.get_string(), new_word.index, myNode.wanted_word, myNode.approx);
                    if (dist == -1)
                        goto after_son;
                    if (dist <= myNode.approx) {
                        myNode.out.insert(OutputElement(new_word.get_string(), freq, dist));
                    }
                }
            }
            const char *first_son = myNode.g_son(curr, len);
            if (*first_son != '\0')
                resolveRec(new_word, first_son, myNode);
        }
        after_son:
        long next_pos = *(long*)(curr + len + 1 + sizeof (long));
        if (next_pos == 0l)
            return;
        curr = myNode.go_to(next_pos);
    }
}

void resolveRecZero(MyString currWord, const char* curr, BinNode& myNode) {
    while (true) {
        size_t len = (size_t) (unsigned char) *curr; // (int) (unsigned char) (curr) = 133
        curr = curr + 1;
        currWord.append(curr, len);
        MyString new_word = MyString(currWord.index + len, currWord.computed_index);
        if (new_word.index <= myNode.wanted_word.length() + myNode.approx) {
            if (new_word.index >= myNode.wanted_word.length() - myNode.approx) { // call lev earlier and kill tree if too bad
                long freq = get_freq(curr, len);
                if (freq != 0) {
                    int dist = lev_zero(new_word, new_word.get_string(), new_word.index, myNode.wanted_word);
                    if (dist == 1) {
                        myNode.out.insert(OutputElement(new_word.get_string(), freq, 0));
                        return;
                    }
                    if (dist == -1)
                        goto after_son;
                }
            }
            const char *first_son = myNode.g_son(curr, len);
            if (*first_son != '\0')
                resolveRec(new_word, first_son, myNode);
        }
        after_son:
        long next_pos = *(long*)(curr + len + 1 + sizeof (long));
        if (next_pos == 0l)
            return;
        curr = myNode.go_to(next_pos);
    }
}

void resolve(char* ptr, std::string word, int approx) {
    int max = (int) (word.size() + approx);
    auto myOutput = Output();
    BinNode myNode = BinNode(ptr, max, approx, word, myOutput);
    MyString currWord = MyString();
    if (approx == 0)
        resolveRecZero(currWord, ptr + 1, myNode);
    else
        resolveRec(currWord, ptr + 1, myNode); // ptr + 1 because of first empty char
    myOutput.print_json();
}

