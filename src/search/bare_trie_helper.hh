//
// Created by hugo on 29/07/17.
//

#ifndef NLP_CORRECTOR_BARE_TRIE_HELPER_HH
#define NLP_CORRECTOR_BARE_TRIE_HELPER_HH


/**
 * \brief Mmap the trie in the memory from its file
 * \param path The path to the trie
 * \return A pointer at the begining of the mmap'ed zone
 */
void *map_file(char *path);

/**
 * \brief Get the frequency of a word in the trie
 * \param ptr The start of the node
 * \param len The len of the word of the node
 */
long get_freq(const char *ptr, size_t len);

#endif //NLP_CORRECTOR_BARE_TRIE_HELPER_HH
