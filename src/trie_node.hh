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

#define WORD_MAX_SIZE 512

void *map_file(char *path);

const char *get_brother(const char *start, const char *ptr, size_t i);

const char *get_son(const char *ptr, size_t len);

long get_freq(const char *ptr, size_t len);

void resolve(char *ptr, std::string word, int approx);

long get_current_offset(long nodeSize);

static char *word = (char *) calloc(WORD_MAX_SIZE, 1); // TODO: can't this just be word[500] ?

class MyString {
public:
    size_t index;
    int computed_index;

    MyString() {
        index = 0;
        computed_index = 1;
    }

    MyString(size_t index, int computed_index) : index(index), computed_index(computed_index) { }

    inline char *get_string() {
        word[index] = '\0';
        return word;
    }

    inline void append(const char *str, size_t len) {
//        std::cerr << str << std::endl;
        memcpy(word + index, str, len);
    }
};

class BinNode {
    char *start;
public:
    int approx;
    int max;
    std::string wanted_word;
    Output &out;

    BinNode(char *start, int max, int approx, std::string wanted_word, Output &output)
            : start(start), max(max), approx(approx),
              wanted_word(wanted_word), out(output) { }

    const char *g_son(const char *ptr, size_t len);

    const char *g_brother(const char *ptr, size_t i);

    const char *go_to(size_t len);
};

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
