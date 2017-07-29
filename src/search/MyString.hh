#ifndef NLP_CORRECTOR_MYSTRING_HH
#define NLP_CORRECTOR_MYSTRING_HH

/**
 * \file MyString.hh
 * \brief Contains the class used to handle strings in the trie
 */

#include <cstring>
#define WORD_MAX_SIZE 512


static char *word = (char *) calloc(WORD_MAX_SIZE, 1); // TODO: can't this just be word[500] ?


/**
 * \class MyString
 * \brief String wrapper with an optimize strcpy & strlen for our use case. The char array is shared by all the instance.
 */
class MyString {
public:
    size_t index; /*!< The size of the string */
    int computed_index; /*!< The last char of the string which have been processed in the Levenshtein table */

    /**
     * \brief Constructor
     */
    MyString() {
        index = 0;
        computed_index = 1;
    }

    /**
     * \brief Constructor
     * \param index The maximum size to read of the string
     * \param compute_index The last char of the string which have been processed in the Levenshtein table
     */
    MyString(size_t index, int computed_index) : index(index), computed_index(computed_index) { }

    /**
     * \brief Build a C-string which contains our string
     * \return The begining of the string
     */
    inline char *get_string() {
        word[index] = '\0';
        return word;
    }

    /**
     * \brief Append to the end of the string another string
     * \param str The string to append
     * \param len The number of char, from the string to append, to append to our string
     */
    inline void append(const char *str, size_t len) {
        memcpy(word + index, str, len);
    }
};


#endif //NLP_CORRECTOR_MYSTRING_HH
