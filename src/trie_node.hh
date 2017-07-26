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

// node struct that can be mapped in the binary file
struct node {
    std::string name; // \0 is no more data
    long freq; // 0 if not a word
    long next; // 0 if node is a leaf, else position in file
    // next should be next son of the father, and next element sequentially should be the first son, 0 if no more
};
void * map_file(char *path);
char *get_brother(char *start, char *ptr, size_t i);
char *get_son(char *ptr, size_t len);
long get_freq(char* ptr, size_t len);
void resolve(char* ptr, std::string word, int approx);

class MyString {
public:
    char* word;
    size_t index;
    MyString() {
        word = (char *) calloc(500, 1);
        index = 0;
    }
    MyString(char *word, size_t index) : word(word), index(index) { }
    char* get_string() {
        word[index] = '\0';
        return word;
    }
    void append(char* str, size_t len) {
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
    char *g_son(char *ptr, size_t len);
    char *g_brother(char *ptr, size_t i);
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
