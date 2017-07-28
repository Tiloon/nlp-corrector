//
// Created by tilon on 23/07/17.
//

#ifndef NLP_CORRECTOR_OUTPUT_HH
#define NLP_CORRECTOR_OUTPUT_HH

#include <set>
#include <memory>
#include "output_element.hh"

class Output {
public:
    std::set<OutputElement> data_;
    Output() : data_(std::set<OutputElement>()) { }
    void insert(const OutputElement& elt);
    void insert(const OutputElement&& elt);
    void print_json();
};


#endif //NLP_CORRECTOR_OUTPUT_HH
