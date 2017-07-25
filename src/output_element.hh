//
// Created by tilon on 23/07/17.
//

#ifndef NLP_CORRECTOR_OUTPUT_ELEMENT_HH
#define NLP_CORRECTOR_OUTPUT_ELEMENT_HH

#include <string>

class OutputElement {
public:
    const std::string elt_;
    long freq_;
    int dist_;

    OutputElement(const std::string &elt, long freq, int dist) : elt_(elt), freq_(freq), dist_(dist) { }

    bool operator<(const OutputElement& other) const
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
