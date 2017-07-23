//
// Created by tilon on 23/07/17.
//

#ifndef NLP_CORRECTOR_OUTPUT_HH
#define NLP_CORRECTOR_OUTPUT_HH

#include <set>
#include <memory>
#include "output_element.hh"

class output {
public:
    std::set<output_element> data_;
    output() : data_(std::set<output_element>()) { }
    void insert(const output_element& elt);
    void insert(const output_element&& elt);
    void print_json();
};


#endif //NLP_CORRECTOR_OUTPUT_HH
