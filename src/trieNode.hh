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

    TrieNode(std::string prefix) :
            prefix_(prefix),
            sons_(),
            isWordEnd_(0)
    {}

    TrieNode(std::string prefix, int wordEnd) :
            prefix_(prefix),
            sons_(),
            isWordEnd_(wordEnd)
    {}

    void insert(std::string word);
    std::string& get_prefix() { return prefix_; }
    void setWordEnd() { isWordEnd_ = 1; }
    void addSon(TrieNode n);
    TrieNode& removeFromPrefix(int nbChar) {
        prefix_ = prefix_.substr(nbChar);
        return *this;
    }

};


#endif //NLP_CORRECTOR_TRIENODE_HH
