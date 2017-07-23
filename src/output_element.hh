//
// Created by tilon on 23/07/17.
//

#ifndef NLP_CORRECTOR_OUTPUT_ELEMENT_HH
#define NLP_CORRECTOR_OUTPUT_ELEMENT_HH

#include <string>

class output_element {
public:
    const std::string elt_;
    int freq_;
    int dist_;

    output_element(const std::string &elt, int freq, int dist) : elt_(elt), freq_(freq), dist_(dist) { }

    bool operator<(const output_element& other) const
    {
        if (dist_ != other.dist_)
            return dist_ < other.dist_;
        else if (freq_ != other.freq_)
            return freq_ > other.freq_;
        else
            return elt_.compare(other.elt_) < 0;
    }
};


#endif //NLP_CORRECTOR_OUTPUT_ELEMENT_HH
