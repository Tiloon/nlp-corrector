//
// Created by tilon on 23/07/17.
//

#ifndef NLP_CORRECTOR_OUTPUT_HH
#define NLP_CORRECTOR_OUTPUT_HH

#include <set>
#include <memory>
#include "output_element.hh"

/**
 * \class Output
 * \brief Manage the final print of the result
 */
class Output {
public:
    std::set<OutputElement> data_; /*!< The ordered set containing all the element to print */

    /**
     * \brief Constructor
     */
    Output() : data_(std::set<OutputElement>()) { }

    void insert(const OutputElement& elt);

    /**
     * \brief Add an OutputElement to the set
     * \param elt The element to add
     */
    void insert(const OutputElement&& elt);

    /**
     * \brief Print all the element in the json format
     */
    void print_json();
};


#endif //NLP_CORRECTOR_OUTPUT_HH
