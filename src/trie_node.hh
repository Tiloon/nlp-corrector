//
// Created by hugo on 23/07/17.
//

#ifndef NLP_CORRECTOR_TRIENODE_HH
#define NLP_CORRECTOR_TRIENODE_HH


#include <string>
#include <vector>

class TrieNode {
public:
    std::string prefix_;
    std::vector<TrieNode> sons_;
    int isWordEnd_;
    int freq_;

    TrieNode(std::string prefix, int freq) :
            prefix_(prefix),
            sons_(),
            isWordEnd_(0),
            freq_(freq)
    {}

    TrieNode(std::string prefix, int wordEnd, int freq) :
            prefix_(prefix),
            sons_(),
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
};


#endif //NLP_CORRECTOR_TRIENODE_HH
