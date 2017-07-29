#ifndef NLP_CORRECTOR_OUTPUT_ELEMENT_HH
#define NLP_CORRECTOR_OUTPUT_ELEMENT_HH

/**
 * \file output_element.hh
 * \brief Contains the class of a single printed element
 */

#include <string>


/**
 * \class OutputElement
 * \brief Represent a object to print
 */
class OutputElement {
public:
    const std::string elt_; /*!< The word */
    long freq_; /*!< The word frequency */
    int dist_; /*!< The word distance with the searched word */

    /**
     * \brief Constructor
     * \param elt The word
     * \param freq The word frequency
     * \param dist The word distance with the searched word
     */
    OutputElement(const std::string &elt, long freq, int dist) : elt_(elt), freq_(freq), dist_(dist) { }

    /**
     * Comparaison used to sort tge OutputElement before printing them
     */
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
