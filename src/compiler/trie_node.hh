//
// Created by hugo on 23/07/17.
//

#ifndef NLP_CORRECTOR_TRIENODE_HH
#define NLP_CORRECTOR_TRIENODE_HH


#include <string>
#include <vector>
#include <memory>
#include <cstring>
#include "../search/output.hh"




long get_current_offset(long nodeSize);





/**
 * \class TrieNode
 * \brief Represent a trie node in the compiler
 */
class TrieNode {
public:
    std::string prefix_;
    /*!< The prefix on the edge leading to the node */
    std::vector<TrieNode> *sons_;
    /*!< The node sons */
    int isWordEnd_;
    /*!< 1 if the node is a word end */
    long freq_;
    /*!< The frequency associated to the word ending on the node */
    long offset_;  /*!< The offset of the node to link it to his brother in the compilation */

    /*!
     * \brief Constructor for node that do not end words
     */
    TrieNode(std::string prefix, int freq) :
            prefix_(prefix),
            sons_(new std::vector<TrieNode>()),
            isWordEnd_(0),
            freq_(freq),
            offset_(0) { }

    /*!
     * \brief Constructor for node that might end words
     */
    TrieNode(std::string prefix, int wordEnd, int freq) :
            prefix_(prefix),
            sons_(new std::vector<TrieNode>()),
            isWordEnd_(wordEnd),
            freq_(freq),
            offset_(0) { }

    /*!
     * \brief Compute the offset of the node
     */
    void compute_offset();

    /*!
     * \brief Compute the head of the offset
     */
    void compute_offset_head();

    /*!
     * \brief Insert a new word to the trie
     * \param word The word to add
     * \param freq The word frequency
     */
    void insert(std::string word, int freq);

    /*!
     * \brief Remove the first characters of the prefix of the node
     * \param nbChar The amount of char to remove
     */
    TrieNode &removeFromPrefix(int nbChar) {
        prefix_ = prefix_.substr(nbChar);
        return *this;
    }

    /*!
     * \brief Compare two nodes
     */
    bool operator==(const TrieNode &other) const {
        return this == &other;
    }

    /*!
     * \brief Draw the trie node to the Dot format
     * \param file The output file
     * \param id The uid of the node
     */
    void draw(std::ofstream &file, int id);

    /*!
     * \brief Save the node in the file
     * \param of The output file
     */
    void writeToBinaryFile(std::ofstream &of);

    /*!
     * \brief Save the node prefix into the file
     * \param of The output file
     * \param son
     */
    void write_string(std::ofstream &of, TrieNode &son) const;
};


#endif //NLP_CORRECTOR_TRIENODE_HH
