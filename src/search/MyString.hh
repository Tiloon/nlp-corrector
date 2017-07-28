//
// Created by hugo on 29/07/17.
//

#ifndef NLP_CORRECTOR_MYSTRING_HH
#define NLP_CORRECTOR_MYSTRING_HH

#include <cstring>
#define WORD_MAX_SIZE 512


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


#endif //NLP_CORRECTOR_MYSTRING_HH
