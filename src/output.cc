//
// Created by tilon on 23/07/17.
//

#include <iostream>
#include "output_element.hh"
#include "output.hh"

void Output::insert(const OutputElement& elt) {
    this->data_.insert(elt);
}

void Output::insert(const OutputElement&& elt) {
    this->data_.insert(elt);
}

static void print_elt(OutputElement elt) {
    std::cout << "{\"word\":\"" << elt.elt_ << "\",\"freq\":" << elt.freq_ << ",\"distance\":" << elt.dist_ << "}";
}

void Output::print_json() {
    std::cout << "[";
    std::set<OutputElement>::iterator it = this->data_.begin();
    if (it != this->data_.end()) {
        print_elt(*it);
        while (++it != this->data_.end()) {
            std::cout << ",";
            print_elt(*it);
        }
    }
    std::cout << "]";
}

