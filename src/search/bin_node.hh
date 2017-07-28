//
// Created by hugo on 29/07/17.
//

#ifndef NLP_CORRECTOR_BINNODE_HH
#define NLP_CORRECTOR_BINNODE_HH


#include <string>
#include "output.hh"


const char *get_brother(const char *start, const char *ptr, size_t i);

const char *get_son(const char *ptr, size_t len);

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


#endif //NLP_CORRECTOR_BINNODE_HH
