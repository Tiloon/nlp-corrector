//
// Created by tilon on 23/07/17.
//

#include <iostream>
#include "output.hh"

void output::insert(const output_element& elt) {
    this->data_.insert(elt);
}

void output::insert(const output_element&& elt) {
    this->data_.insert(elt);
}

static void print_elt(output_element elt) {
    std::cout << "{\"word\":\"" << elt.elt_ << "\",\"freq\":" << elt.freq_ << ",\"distance\":" << elt.dist_ << "}";
}

void output::print_json() {
    std::cout << "[";
    std::set<output_element>::iterator it = this->data_.begin();
    if (it != this->data_.end())
        print_elt(*it);
    while (++it != this->data_.end()) {
        std::cout << ",\n";
        print_elt(*it);
    }
    std::cout << "]";
}

