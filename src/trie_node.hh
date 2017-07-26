//
// Created by hugo on 23/07/17.
//

#ifndef NLP_CORRECTOR_TRIENODE_HH
#define NLP_CORRECTOR_TRIENODE_HH


#include <string>
#include <vector>
#include <memory>
#include <cstring>
#include "output.hh"

void * map_file(char *path);
const char *get_brother(const char *start, const char *ptr, size_t i);
const char *get_son(const char *ptr, size_t len);
long get_freq(const char* ptr, size_t len);
void resolve(char* ptr, std::string word, int approx);
long get_current_offset(long nodeSize);

static char* word = (char *) calloc(500, 1);

class MyString {
public:
    size_t index;
    MyString() {
        index = 0;
    }
    MyString(size_t index) : index(index) { }
    inline char* get_string() {
        word[index] = '\0';
        return word;
    }
    inline void append(const char* str, size_t len) {
        memcpy(word + index, str, len);
    }
};

class BinNode {
    char* start;
public:
    int approx;
    int max;
    std::string wanted_word;
    Output& out;

    BinNode(char *start, int max, int approx, std::string wanted_word, Output& output)
            : start(start), max(max), approx(approx),
              wanted_word(wanted_word), out(output) { }
    const char *g_son(const char *ptr, size_t len);
    const char *g_brother(const char *ptr, size_t i);
};

class TrieNode {
public:
    std::string prefix_;
    std::vector<TrieNode>* sons_;
    int isWordEnd_;
    long freq_;
    long offset_;

    TrieNode(std::string prefix, int freq) :
            prefix_(prefix),
            sons_(new std::vector<TrieNode>()),
            isWordEnd_(0),
            freq_(freq),
            offset_(0)
    {}

    TrieNode(std::string prefix, int wordEnd, int freq) :
            prefix_(prefix),
            sons_(new std::vector<TrieNode>()),
            isWordEnd_(wordEnd),
            freq_(freq),
            offset_(0)
    {}

    void compute_offset();
    void compute_offset_head();
    void insert(std::string word, int freq);
    std::string& get_prefix() { return prefix_; }
    void setWordEnd() { isWordEnd_ = 1; }
    TrieNode& removeFromPrefix(int nbChar) {
        prefix_ = prefix_.substr(nbChar);
        return *this;
    }

    bool operator==(const TrieNode& other) const
    {
        return this == &other;
    }

    void draw(std::ofstream& file, int id);

    void writeToBinaryFile(std::ofstream& of);
};


#endif //NLP_CORRECTOR_TRIENODE_HH
