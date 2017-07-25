//
// Created by hugo on 23/07/17.
//

#ifndef NLP_CORRECTOR_TRIENODE_HH
#define NLP_CORRECTOR_TRIENODE_HH


#include <string>
#include <vector>
#include <memory>

// node struct that can be mapped in the binary file
struct node {
    std::string name; // \0 is no more data
    long freq; // 0 if not a word
    long next; // 0 if node is a leaf, else position in file
    // next should be next son of the father, and next element sequentially should be the first son, 0 if no more
};
void map_file(char *path);

class TrieNode {
public:
    std::string prefix_;
    std::vector<TrieNode>* sons_;
    int isWordEnd_;
    int freq_;

//    TrieNode(const TrieNode& n) :
//        prefix_(n.prefix_),
//                sons_(n.sons_),
//                isWordEnd_(n.isWordEnd_),
//                freq_(n.freq_)
//    {}

    TrieNode(std::string prefix, int freq) :
            prefix_(prefix),
            sons_(new std::vector<TrieNode>()),
            isWordEnd_(0),
            freq_(freq)
    {}

    TrieNode(std::string prefix, int wordEnd, int freq) :
            prefix_(prefix),
            sons_(new std::vector<TrieNode>()),
            isWordEnd_(wordEnd),
            freq_(freq)
    {}

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
