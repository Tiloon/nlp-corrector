#ifndef NLP_CORRECTOR_BINNODE_HH
#define NLP_CORRECTOR_BINNODE_HH


#include <string>
#include "output.hh"

/**
 * \file bin_node.hh
 * \brief Contains data related to the maped binary file and the query
 */


/**
 * \brief Get the frequency of a word in the trie
 * \param ptr The start of the node
 * \param len The len of the word of the node
 */
long get_freq(const char *ptr, size_t len);

/**
 * \fn const char *get_brother(const char *start, const char *ptr, size_t len);
 * \brief Compute the position of the brother of the given node
 *
 * \param start The pointer to the start of the maped binary filed
 * \param ptr The pointer to the current node
 * \param len The length of the word of the current node
 *
 * \return Return a pointer to the position of the brother of the given node
 */
const char *get_brother(const char *start, const char *ptr, size_t len);

/**
 * \fn const char *get_son(const char *ptr, size_t len);
 * \brief Compute the position of the son of the given node
 *
 * \param ptr The pointer to the current node
 * \param len The length of the word of the current node
 *
 * \return Return a pointer to the position of the son of the given node
 */
const char *get_son(const char *ptr, size_t len);


/**
 * \class BinNode
 * \brief Contains data on the tree and wanted word
 */
class BinNode {
    char *start; /*!< The pointer to the start of the maped binary file */
public:
    int approx; /*!< The approximation of the query */
    int max; /*!< The maximum size of an answer */
    std::string wanted_word; /*!< The word we want an approximation of */
    Output &out; /*!< Contains the output class used to print the answer */

    /**
     * \brief Constructor
     * \param start The pointer to the maped binary file
     * \param max The maximum size of an answer
     * \param approx The approximation of the request
     * \param wanted_word The word we want an approximation of
     * \param output The output class used to print the answer
     */
    BinNode(char *start, int max, int approx, std::string wanted_word, Output &output)
            : start(start), max(max), approx(approx),
              wanted_word(wanted_word), out(output) { }

    const char *g_son(const char *ptr, size_t len);

    const char *g_brother(const char *ptr, size_t i);

    const char *go_to(size_t len);
};


#endif //NLP_CORRECTOR_BINNODE_HH
