/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/dia/test_data/attribute_sequence.hpp"
#include "dogen/dia/test_data/diagram_data_sequence.hpp"

namespace dogen {
namespace dia {
namespace test_data {
namespace detail {

diagram_data_generator::value_type
diagram_data_generator::next_term(const unsigned int position) {
    std::vector<dogen::dia::attribute> attributes;
    simple_attribute_sequence sequence;

    if (position == 0) {
        attributes.push_back(sequence());
        return dogen::dia::diagram_data(attributes);
    } else if (position == 1) {
        sequence();
        attributes.push_back(sequence());
        return dogen::dia::diagram_data(attributes);
    }
    sequence();
    sequence();
    attributes.push_back(sequence());
    return dogen::dia::diagram_data(attributes);
}

} } } }
