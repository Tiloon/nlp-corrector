#pragma once
#include <string>
#include "MyString.hh"

/**
 * \file lev.hh
 * \brief Contains everything related to Damerau-Levenshtein distance
 */

/**
 * \fn int lev_max(MyString& new_word, const char* s1, size_t len1, const std::string& s2, int maxDist)
 * \brief Compute the new lines for Damerau-Levenshtein distance
 *
 * \param new_word The current node word
 * \param s1 A pointer to the start to the char array of the node word
 * \param len1 The length of the node word
 * \param s2 The searched word
 * \param maxDist The maximum distance allowed for the search
 *
 * \return The Damerau-Levenshtein distance, or -1 if it is superior to maxDist
 */
int lev_max(MyString& new_word, const char* s1, size_t len1, const std::string& s2, int maxDist);

/**
 * \fn int lev_zero(MyString& new_word, const char* s1, size_t len1, const std::string& s2)
 * \brief Compute the Damerau-Levenshtein distance for the "maxDist = 0" case. Its more or less a better strcmp.
 *
 * \param new_word The current node word
 * \param s1 A pointer to the start to the char array of the node word
 * \param len1 The length of the node word
 * \param s2 The searched word
 *
 * \return The Damerau-Levenshtein distance, or -1 if it is superior to maxDist
 */
int lev_zero(MyString& new_word, const char* s1, size_t len1, const std::string& s2);

/**
 * \fn void init_dist()
 * \brief Create the matrix to store the Damerau-Levenshtein distance computations.
 */
void init_dist();
