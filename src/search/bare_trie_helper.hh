#ifndef NLP_CORRECTOR_BARE_TRIE_HELPER_HH
#define NLP_CORRECTOR_BARE_TRIE_HELPER_HH

/**
 * \file bare_trie_helper.hh
 * \brief Contains functions used to map the binary file
 */

/**
 * \brief Mmap the trie in the memory from its file
 * \param path The path to the trie
 * \return A pointer at the begining of the mmap'ed zone
 */
void *map_file(char *path);

#endif //NLP_CORRECTOR_BARE_TRIE_HELPER_HH
